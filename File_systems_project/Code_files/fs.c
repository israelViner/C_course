#include "fs.h"
#include "disk.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>


static int *bitmap = NULL;


/* Creates a new fiylesystem on the disk.
	Case 1: if the disk isn't present: Sets aside ten percent of the blocks for inodes,
 			clears the inode table, and writes the superblock.
	Case 2: if the disk is present and mounted, return.
	Case 3: if the dist is present but not mounted, clear the disk. */
int fs_format()
{
	/* If the disk is already mounted - return */
	if (bitmap) {
		printf("\n\033[1;31mERROR: The disk is already mounted\n\n\033[0m");
		return 0;
	}

	union fs_block block;
	disk_read(0,block.data);
	int blocks_inodes = block.super.ninodeblocks;
	
	/* If the disk is exsists but not mounted - clear the disk */
	union fs_block temp_block;
	if (block.super.magic == FS_MAGIC) {
		for (int i = 1; i <= blocks_inodes; ++i) {
			disk_read(i,temp_block.data);
			for (int j = 0; j < INODES_PER_BLOCK; ++j) {
				if (temp_block.inode[j].isvalid) {
					temp_block.inode[j].isvalid = 0;
					for (int c = 0; c < POINTERS_PER_INODE; ++c)
						if(temp_block.inode[j].direct[c])
							temp_block.inode[j].direct[c] = 0;
					if (temp_block.inode[j].indirect) {
						temp_block.inode[j].indirect = 0;
						disk_read(temp_block.inode[j].indirect ,block.data);
						for (int c = 0; c < POINTERS_PER_BLOCK; ++c) {
							if(block.pointers[c]) 
								block.pointers[c] = 0;
						}
					}
				}
				disk_write(i, temp_block.data);
			}
		}
	}
	
	/* If the disk isn't exsists - create new disk (i.e. new superblock) */
	else {
		int size = disk_size();
		block.super.magic = FS_MAGIC;
		block.super.nblocks = size;
		block.super.ninodeblocks = size/10 + 1;
		block.super.ninodes = block.super.ninodeblocks * 128;
		for (int i = 0; i < 4; ++i)
			disk_write(0, block.data);
	}	
	return 1;
}


/* Scan a mounted filesystem and report on how the inodes and blocks are organized */
void fs_debug()
{
	if(!bitmap) {
		printf("\n\033[1;31mERROR: The disk isn't mounted\n\n\033[0m");
		return;
	}	
	
	union fs_block block;
	disk_read(0,block.data);

	/* Print the superblock details */
	printf("\n\033[1;31msuperblock:\n\033[0m");
	printf("    %d \033[1;31mblocks\n\033[0m",block.super.nblocks);
	printf("    %d \033[1;31minode blocks\n\033[0m",block.super.ninodeblocks);
	printf("    %d \033[1;31minodes\n\033[0m",block.super.ninodes);

	/* Print the valid indexes in the bitmap (that is, the occupied blocks in the disk) */
	int system_files = block.super.ninodeblocks;
	int data_files = 0;
	printf("\n\033[1;34mThe occupied blocks are: \033[0m");
	for (int j = block.super.ninodeblocks + 1; j < block.super.nblocks; ++j)
		if (bitmap[j]) {
			++data_files;
			printf("%d, ", j);
		}
	printf("\n");
	
	/* Print the snupshot of the system (the amount of the free/used memory ) */
	printf("\n\033[1;31mSnupshot:\n\033[0m");
	printf("    \033[1;31mMemory in use: \033[0m %d from %d blocks\n", system_files + data_files ,block.super.nblocks);
	printf("    \033[1;31mSystem files: \033[0m %d blocks\n", system_files);
	printf("    \033[1;31mFree memory: \033[0m %d blocks\n\n",block.super.nblocks - (system_files + data_files));

	
	/* Print the valid inodes details */
	union fs_block block_1;	
	for (int i = 1; i <= block.super.ninodeblocks; ++i) {
		disk_read(i,block_1.data);
		for (int j = 0; j < INODES_PER_BLOCK; ++j) {
			if (block_1.inode[j].isvalid) {
				printf("\033[1;34minode\033[0m %d \n", j);
				print_inode(block_1.inode[j]);
			}
		}
	}
}


/* Examine the disk for a filesystem - read the superblock, 
build a free block bitmap, and fill the bitmap in order to prepare the filesystem for use. */
int fs_mount()
{
	/* If the disk is already mounted - return error */
	if(bitmap) {
		printf("\n\033[1;31mERROR: The disk is already mounted\n\n\033[0m");
		return 0;
	}

	/* Initialize an empty bitmap in the size of blocks of the disk */
	union fs_block block;
	disk_read(0,block.data);
	int size_disk = block.super.nblocks;
	int n_blocks_inodes = block.super.ninodeblocks;
	bitmap = (int *)calloc(size_disk, sizeof(int));
	
	/* Fill the bitmap in the occupied blocks indexses */	
	union fs_block temp_block;
	for (int i = 1; i <= n_blocks_inodes; ++i) {
		disk_read(i,temp_block.data);
		for (int j = 0; j < INODES_PER_BLOCK; ++j) {
			if (temp_block.inode[j].isvalid) {
				if (temp_block.inode[j].size > 0) {
					color_bitmap(temp_block.inode[j], 1);
				}
			}
		}
	}
	return 1;
}				


/* Create a new inode of zero length. On success, return the inumber. On failure, return negative one. */
int fs_create()
{
	union fs_block block;
	disk_read(0, block.data);
	int n_blocks_inodes = block.super.ninodeblocks;

	/* Create an inode and fill his fields */
	struct fs_inode inode;
	inode.isvalid = 1;
	inode.size = 0;
	inode.indirect = 0;
	for (int i = 0; i < POINTERS_PER_INODE; ++i) {
		inode.direct[i] = 0;
	}

	/* Find free place in the inodes table and insert the new inode into it */
	for (int i = 1; i <= n_blocks_inodes; ++i) {
		disk_read(i,block.data);
		for (int j = 0; j < INODES_PER_BLOCK; ++j) {
			if (!block.inode[j].isvalid) {
				block.inode[j] = inode;
				disk_write(i, block.data);
				return (i - 1)*INODES_PER_BLOCK+j;
			}
		}
	}
	/* If the inodes table is full - return error */
	printf("\n\033[1;31mERROR: The inodes table is full\n\n\033[0m");
	return -1;
}


/* Delete the inode indicated by the inumber.
 Release all data and indirect blocks assigned to this inode 
 and return them to the free block map. */
int fs_delete( int inumber )
{
	/* If the inode isn't exsists in the inodes table - return error */
	struct fs_inode inode;
	if (!inode_load(inumber, &inode)) {
		printf("\n\033[1;31mERROR: This inode isn't exsists\n\n\033[0m");
		return 0;
	}

	int n_block = inumber/INODES_PER_BLOCK+1, i_inode = inumber%INODES_PER_BLOCK;
	union fs_block block;
	disk_read(n_block,block.data);

	/* If the inode isn't created - return error */
	if (!block.inode[i_inode].isvalid) {	
		printf("\n\033[1;31mERROR: This inode isn't created\n\n\033[0m");
		return 0;
	}

	/* Free the place in the inode table */
	block.inode[i_inode].isvalid = 0;
	disk_write(n_block, block.data);
	
	/* Free the connected indices in the bitmap (including the inderctives) */
	if (block.inode[i_inode].size > 0) {
		color_bitmap(block.inode[i_inode], 0);		
	}
	return 1;
}


/* Return the logical size of the given inode, in bytes. */
int fs_getsize( int inumber )
{
	int n_block = inumber / INODES_PER_BLOCK + 1;
	int inode_ptr = inumber % INODES_PER_BLOCK;
	union fs_block block;
	disk_read(n_block, block.data);

	/* If the inode isn't exsists in the inodes table - return error */
	struct fs_inode inode;
	if (!inode_load(inumber, &inode)) {
		printf("\n\033[1;31mERROR: This inode isn't exsists\n\n\033[0m");
		return -1;
	}

	/* If the inode isn't created - return error */
	if (!(block.inode[inode_ptr].isvalid)) {
		printf("\n\033[1;31mERROR: This inode isn't created\n\n\033[0m");
		return -1;
	}
	
	return block.inode[inode_ptr].size;	
}


/* Read data from a valid inode. 
Copy "length" bytes from the inode into the "data" pointer, starting at "offset" in the inode. 
Return the total number of bytes read. */
int fs_read( int inumber, char *data, int length, int offset )
{
	union fs_block block;
	struct fs_inode inode;
	
	/* If the inode isn't exsists in the inodes table - return error */
	if (!inode_load(inumber, &inode)) {
		printf("\n\033[1;31mERROR: This inode isn't exsists\n\n\033[0m");
		return 0;
	}
		
	/* If the inode isn't exsist - return error */
	if (!inode.isvalid) {	
		printf("\n\033[1;31mERROR: This inode isn't exsists\n\n\033[0m");
		return 0;
	}
	
	/* Check the anount of the characters that available to copy */
	int len = length; 
	if (inode.size <= length + offset)
		len = inode.size - offset;
	
	/* Read all the data starting from point j in block n (the variable j is resets after the first loop) */
	int i = offset / DISK_BLOCK_SIZE;
	int start_byte = offset % DISK_BLOCK_SIZE;
	int left = len;
	int edge = 0;
	while (left > 0) {
		
		/* Provide the spesific wanted block in order to write the data from it */
		provide_block(inode, &block, i++);
		
		/* Read into the the string the data from the block */
		for (int index = start_byte; index < DISK_BLOCK_SIZE && index < left + start_byte; ++index) {
			data[edge + index - start_byte] = block.data[index];
		}
		edge += DISK_BLOCK_SIZE - start_byte;
		left -= (DISK_BLOCK_SIZE - start_byte);
		start_byte = 0;

	}
	return len;
}	
		
	
/* Write data to a valid inode. 
Copy "length" bytes from the pointer "data" into the inode starting at "offset" bytes. 
Allocate any necessary direct and indirect blocks in the process. 
Return the number of bytes actually written. */
int fs_write( int inumber, const char *data, int length, int offset )
{	
	/* If the disk isn't mounted - return */
	if (!bitmap) {
		printf("\n\033[1;31mERROR: The disk isn't mounted\n\n\033[0m");
		return 0;
	}
	
	union fs_block block;
	struct fs_inode inode;	
	
	/* If the inode isn't exsists in the inodes table - return error */
	if (!inode_load(inumber, &inode)) {
		printf("\n\033[1;31mERROR: This inode isn't exsists\n\n\033[0m");
		return 0;
	}

	/* If the inode isn't exsist - return error */
	if (!inode.isvalid) {	
		printf("\n\033[1;31mERROR: This inode isn't exsists\n\n\033[0m");
		return 0;
	}


	/* Write all the data into the inode 
	starting from point j in block n */
	int i = offset / DISK_BLOCK_SIZE, start_byte = offset % DISK_BLOCK_SIZE;
	int left = length , edge = 0, new_block = -1, copied = 0;
	while (left > 0) {
		
		/* Find a block to write into it (new one if a connected block isn't exsist) */
		new_block = find_block(inumber, i++);
		inode_load(inumber, &inode);

		/* If the disk is full - return error */
		if (new_block == -1) {
			inode.size += copied;
			inode_save(inumber, inode);
			printf("\033[1;31mERROR: The disk is full\n\033[0m");
			return copied;
		}

		/* Read the block in order to write into it */
		disk_read(new_block, block.data);
		
		int index = start_byte;
		for (; index < DISK_BLOCK_SIZE && index < left; ++index) {
			 block.data[index] = data[edge + index - start_byte];
		}
		disk_write(new_block, block.data);
	
		/* Update the variables */
		copied += index - start_byte;
		edge += index - start_byte;
		left -= (index - start_byte);		
		start_byte = 0;		
	}

	/* Save the updated inode into the inode table */
	if (offset + length > inode.size) {
		inode.size = offset + length;
	}
	inode_save(inumber, inode);
	
	return length;
}
		

/* Scaning the bitmap in order to find a free block (return -1 if the disk is full) */
int find_free_block() 
{
	union fs_block block;
	disk_read(0, block.data);
	int inodes = block.super.ninodeblocks, size = block.super.nblocks;
	for (int i = 1 + inodes; i < size; ++i) {
		if (bitmap[i] == 0) {
			return i;
		}
 	}
	return -1;
}


/* Find the connected block for a specific place in a inode.
if there isn't connectet block - find free block and connected it into
this place (if the disk is full return 0). */
int find_block(int inumber, int inode_ptr) 
{
	struct fs_inode inode;
	inode_load(inumber, &inode);
	
	/* If the inode isn't valit return 0 */
	if (!inode.isvalid) {
		return 0;
	}
	
	/* If the block intented for the directives */
	if (inode_ptr < POINTERS_PER_INODE) {
		
		/* If a connected block is exsist - return it */
		if (inode.direct[inode_ptr] != 0) {
			return inode.direct[inode_ptr];
		}
		
		/* If a connected block isn't exsist - connect new block to the inode and return it 
		(return -1 if the disk is full) */
		else {
			int free_block = find_free_block();
			if (free_block == -1) {
				return -1;
			}
			else {
				bitmap[free_block] = 1;
				inode.direct[inode_ptr] = free_block;
				inode_save(inumber, inode);	
				return free_block;			
			}
		}
	}

	/* If the block intented for the indirectives */
	else {
		
		inode_ptr -= 5;
		union fs_block inblock;
		int indirect = inode.indirect, oldindirect = 0, *olddirect = &(inode.indirect);
		
		while (inode_ptr > POINTERS_PER_BLOCK - 2) {
			disk_read(indirect, inblock.data);
			oldindirect = indirect;
			olddirect = &(inblock.pointers[POINTERS_PER_BLOCK - 1]);
			indirect = inblock.pointers[POINTERS_PER_BLOCK - 1];
			inode_ptr -= POINTERS_PER_BLOCK - 1;
		}		
		
		/* Allocate new block for the indirect if necessary - including the following indirect blocks
		(return -1 if the disk is full) */
		if (indirect == 0) {
			int free_block = find_free_block();
			if (free_block == -1) {
					return -1;	
			}
			bitmap[free_block] = 1;
			union fs_block temp_block;
			for (int i = 0; i < POINTERS_PER_BLOCK; ++i) {
				temp_block.pointers[i] = 0;			
			}
			disk_write(free_block, temp_block.data);
			*olddirect = free_block;
			if(oldindirect) {
				disk_write(oldindirect, inblock.data);
			}
			indirect = free_block;
			inode_save(inumber, inode);
		}
		
		disk_read(indirect, inblock.data);
			
		/* Check if a connected block is exsist and allocate now block if not */
		if (inblock.pointers[inode_ptr] != 0) {
			return inblock.pointers[inode_ptr];
		}
		else {
			int free_block1 = 0;
			free_block1 = find_free_block();
			if (free_block1 == -1) {
				return -1;
			}
			bitmap[free_block1] = 1;
			inblock.pointers[inode_ptr] = free_block1;
			disk_write(indirect, inblock.data);
			return free_block1;
		}
	}
}


/* Load an inode from the inodes table of the disk */
int inode_load(int inumber, struct fs_inode *inode)
{	
	int n_block = (inumber/INODES_PER_BLOCK) +1 , inode_ptr = inumber % INODES_PER_BLOCK;
	union fs_block block;
	disk_read(0,block.data);
	if (inumber > block.super.ninodes - 1) 
		return 0;
	disk_read(n_block,block.data);
	*inode = block.inode[inode_ptr];
	return 1;
}


/* Save an inode into the inodes table of the disk */
void inode_save(int inumber, struct fs_inode inode)
{
	int n_block = (inumber/INODES_PER_BLOCK) + 1, inode_ptr = inumber % INODES_PER_BLOCK;
	union fs_block block;
	disk_read(n_block, block.data);
	block.inode[inode_ptr] = inode;
	disk_write(n_block, block.data);
}


/* Provide the spesific wanted block in order to write the data from it */
void provide_block(struct fs_inode inode, union fs_block *block, int block_ptr) 
{
	/* Read into block.data the data from the block that connected 
	 to the directive or to the indirective of the inode */
	union fs_block indirect_block;
	if (inode.indirect)
		disk_read(inode.indirect ,indirect_block.data);
	
	/* If the block is connect to one of the directives */
	if (block_ptr < POINTERS_PER_INODE)		
		disk_read(inode.direct[block_ptr], block->data);

	/* If the block is connect to the first indirective */
	else if (block_ptr < POINTERS_PER_INODE + POINTERS_PER_BLOCK - 1)
		disk_read(indirect_block.pointers[block_ptr - 5] , block->data);		
	
	/* If the block is connect to one of the following indirectives */
	else {
		int temp_indirect = block_ptr - POINTERS_PER_INODE;
		while (temp_indirect > 1022) {
			disk_read(indirect_block.pointers[POINTERS_PER_BLOCK - 1], indirect_block.data);
			temp_indirect = temp_indirect - POINTERS_PER_BLOCK - 1;
		}
		disk_read(indirect_block.pointers[temp_indirect] , block->data);	
	}
	return;
}


/* Print the details of a specific inode */
void print_inode(struct fs_inode inode) 
{
	union fs_block block;
	printf("\033[1;32m\tsize\033[0m %d \033[1;32mbytes\n\033[0m", inode.size);
	printf("\033[1;32m\tdirect blocks: \033[0m");
	for (int i = 0; i < POINTERS_PER_INODE; ++i) {
		if(inode.direct[i]) {
			printf("%d, ", inode.direct[i]);
		}
	}
	printf("\033[1;32m\n\tindirect blocks: \033[0m%d\n", inode.indirect);
	if (inode.indirect) {
		printf("\033[1;32m\tindirect data blocks: \033[0m");
		disk_read(inode.indirect ,block.data);
		for (int i = 0; i < POINTERS_PER_BLOCK; ++i) {
			if(block.pointers[i]) {
				printf("%d, ", block.pointers[i]);
			}
		}
	}
	printf("\n");
}


/* Color all the connected blocks of a specific inode in 'color' 0/1 */
void color_bitmap(struct fs_inode inode, int color) 
{
	int i_pointer = 0;
	for (; i_pointer < POINTERS_PER_INODE; ++i_pointer) {
		if (inode.direct[i_pointer])
			bitmap[inode.direct[i_pointer]] = color;
		else 
			break;
	}

	if (inode.indirect) {
		bitmap[inode.indirect] = color;
		union fs_block inblock;
		int indirect = inode.indirect;
		do {
			disk_read(indirect, inblock.data);
			for (i_pointer = 0; i_pointer < POINTERS_PER_BLOCK; ++i_pointer) {
				if (inblock.pointers[i_pointer])
					bitmap[inblock.pointers[i_pointer]] = color;
				else 
					break;
			}
			indirect = inblock.pointers[POINTERS_PER_BLOCK - 1];
		} while (indirect);
	}
}


/* Init a file system in the disk */
int fs_init( const char *filename, int n ) 
{
	if (!disk_init(filename, n)) {
		return 0;
	}
	return 1;
}


/* Get the size of the disk */
int fs_size()
{
	return disk_size();
}


/* Close the disk */
void fs_close()
{
	free(bitmap);
	disk_close();
}



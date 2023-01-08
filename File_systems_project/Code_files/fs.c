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

	union fs_block block, temp_block;
	disk_read(0,block.data);
	int blocks_inodes = block.super.ninodeblocks;
	
	/* If the disk is exsists but not mounted - clear the disk */
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
	union fs_block block;

	disk_read(0,block.data);

	/* Print the superblock details */
	printf("\033[1;31msuperblock:\n\033[0m");
	printf("    %d \033[1;31mblocks\n\033[0m",block.super.nblocks);
	printf("    %d \033[1;31minode blocks\n\033[0m",block.super.ninodeblocks);
	printf("    %d \033[1;31minodes\n\033[0m",block.super.ninodes);
	
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

	/* Print the valid indexes in the bitmap (that is, the occupied blocks in the disk) */
	if(!bitmap) {
		printf("\n\033[1;31mERROR: The disk isn't mounted\n\n\033[0m");
		return;
	}
	printf("\nThe occupied blocks are:\n");
	for (int j = 1; j < block.super.nblocks; ++j)
		if (bitmap[j])
			printf("\033[1;36mblock\033[0m %d, ", j);
	printf("\n");		
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
	union fs_block block, temp_block;
	disk_read(0,block.data);
	int size = block.super.nblocks;
	int n_inodes = block.super.ninodeblocks;
	bitmap = (int *)calloc(size, sizeof(int));
	
	/* Fill the bitmap in the occupied blocks indexses */
	for (int i = 1; i <= n_inodes; ++i) {
		disk_read(i,temp_block.data);
		for (int j = 0; j < INODES_PER_BLOCK; ++j) {
			if (temp_block.inode[j].isvalid) {
				if (temp_block.inode[j].size > 0) {
					int b = 0;
					for (; b < POINTERS_PER_INODE; ++b) {
						if (temp_block.inode[j].direct[b])
							bitmap[temp_block.inode[j].direct[b]] = 1;
						else 
							break;
					}
					if (temp_block.inode[j].indirect) {
						bitmap[temp_block.inode[j].indirect] = 1;
						union fs_block inblock;
						int indirect = temp_block.inode[j].indirect;
						do {
							disk_read(indirect, inblock.data);
							for (b = 0; b < POINTERS_PER_BLOCK; ++b) {
								if (inblock.pointers[b])
									bitmap[inblock.pointers[b]] = 1;
								else 
									break;
							}
							indirect = inblock.pointers[POINTERS_PER_BLOCK - 1];
						} while (indirect);
					}
				}
			}
		}
	}
	return 1;
}				
				
				
				/*int c = 0;
				if ((a.inode[j].size/DISK_BLOCK_SIZE) + 1 < 6) {
					while (c < a.inode[j].size/DISK_BLOCK_SIZE + 1) {
						printf("diract c: %d\n", a.inode[j].direct[c]);
						bitmap[a.inode[j].direct[c++]] = 1;
					}
				}
				else {
					while (c < POINTERS_PER_INODE) 
						bitmap[a.inode[j].direct[c++]] = 1;
					disk_read(a.inode[j].indirect,block.data);
					while (c < a.inode[j].size/DISK_BLOCK_SIZE) {
						bitmap[block.pointers[c-POINTERS_PER_INODE]] = 1;
						++c;
					}
				}*/


/* Create a new inode of zero length. On success, return the inumber. On failure, return negative one. */
int fs_create()
{
	union fs_block block;
	disk_read(0, block.data);
	int ninodes = block.super.ninodeblocks;

	/* Create an inode and fill his fields */
	struct fs_inode inode;
	inode.isvalid = 1;
	inode.size = 0;
	inode.indirect = 0;
	for (int i = 0; i < POINTERS_PER_INODE; ++i)
		inode.direct[i] = 0;

	/* Find free place in the inodes table and insert the new inode into it */
	for (int i = 1; i <= ninodes; ++i) {
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
	int n = inumber/INODES_PER_BLOCK+1, j = inumber%INODES_PER_BLOCK;
	union fs_block block, temp_block;
	disk_read(n,block.data);
	
	/* If the inode isn't exsist - return error */
	if (!block.inode[j].isvalid) {	
		printf("\n\033[1;31mERROR: This inode isn't exsists\n\n\033[0m");
		return 0;
	}

	/* Free the place in the inode table */
	block.inode[j].isvalid = 0;
	disk_write(n, block.data);
	
	/* Free the connected indices in the bitmap (including the inderctives) */
	int i = 0, size = block.inode[j].size/DISK_BLOCK_SIZE + 1;
	if (block.inode[j].indirect)
		disk_read(block.inode[j].indirect,temp_block.data);
	while (i < size) 
		if (i < POINTERS_PER_INODE)
			bitmap[block.inode[j].direct[i++]] = 0;
		else {
			if((i - POINTERS_PER_INODE)%(POINTERS_PER_BLOCK - 1) == 0) {
				disk_read(temp_block.pointers[(i - POINTERS_PER_BLOCK)%(POINTERS_PER_BLOCK - 1)],temp_block.data);
				bitmap[temp_block.pointers[(i - POINTERS_PER_BLOCK)%(POINTERS_PER_BLOCK - 1)]] = 0; 
			}
			bitmap[temp_block.pointers[(i - POINTERS_PER_INODE)%(POINTERS_PER_BLOCK - 1)]] = 0;
			++i;
		}
	return 1;
}


/* Return the logical size of the given inode, in bytes. */
int fs_getsize( int inumber )
{
	int n = inumber/INODES_PER_BLOCK+1, j = inumber%INODES_PER_BLOCK;
	union fs_block block;
	disk_read(n,block.data);
	if (block.inode[j].isvalid)	
		return block.inode[j].size;
	
	/* If the inode isn't exsist - return error */
	printf("\n\033[1;31mERROR: This inode isn't exsists\n\n\033[0m");
	return -1;
}


/* Read data from a valid inode. 
Copy "length" bytes from the inode into the "data" pointer, starting at "offset" in the inode. 
Return the total number of bytes read. */
int fs_read( int inumber, char *data, int length, int offset )
{
	union fs_block block;
	struct fs_inode inode;
	inode_load(inumber, &inode);
		
	/* If the inode isn't exsist - return error */
	if (!inode.isvalid) {	
		printf("\n\033[1;31mERROR: This inode isn't exsists\n\n\033[0m");
		return 0;
	}

	int n = offset/DISK_BLOCK_SIZE, j = offset%DISK_BLOCK_SIZE, len = length, edge = 0;
	
	/* Check the anount of the characters that available to copy */
	if (inode.size <= length + offset)
		len = inode.size - offset;
	
	/* Read all the data starting from point j in block n (the variable j is resets after the first loop) */
	int left = len, i = n;
	
	while (left > 0) {
		
		/* Provide the spesific wanted block in order to write the data from it */
		provide_block(inode, &block, i++);
		
		/* Read into the the string the data from the block */
		for (int index = j; index < DISK_BLOCK_SIZE && index < left + j; ++index) 
			data[edge + index - j] = block.data[index];
		edge += DISK_BLOCK_SIZE - j;
		left -= (DISK_BLOCK_SIZE - j);
		j = 0;

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
	inode_load(inumber, &inode);

	/* If the inode isn't exsist - return error */
	if (!inode.isvalid) {	
		printf("\n\033[1;31mERROR: This inode isn't exsists\n\n\033[0m");
		return 0;
	}

	int n = offset/DISK_BLOCK_SIZE, j = offset%DISK_BLOCK_SIZE;
	int left = length , edge = 0, new_block = -1, i = n, copied = 0;
		
	/* Write all the data into the inode 
	starting from point j in block n */
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
		
		int index = j;
		for (; index < DISK_BLOCK_SIZE && index < left; ++index) {
			 block.data[index] = data[edge + index - j];
		}
		disk_write(new_block, block.data);
	
		/* Update the variables */
		copied += index - j;
		edge += index - j;
		left -= (index - j);		
		j = 0;		
	}

	/* Save the updated inode into the inode table */
	if (offset + length > inode.size)
		inode.size = offset + length;
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
int find_block(int inumber, int i) 
{
	struct fs_inode inode;
	inode_load(inumber, &inode);
	
	/* If the inode isn't valit return 0 */
	if (!inode.isvalid)
		return 0;
	
	/* If the block intented for the directives */
	if (i < POINTERS_PER_INODE) {
		
		/* If a connected block is exsist - return it */
		if (inode.direct[i] != 0) 
			return inode.direct[i];
		
		/* If a connected block isn't exsist - connect new block to the inode and return it 
		(return -1 if the disk is full) */
		else {
			int free_block = find_free_block();
			if (free_block == -1)
				return -1;
			else {
				bitmap[free_block] = 1;
				inode.direct[i] = free_block;
				inode_save(inumber, inode);	
				return free_block;			
			}
		}
	}

	/* If the block intented for the indirectives */
	else {
		
		i -= 5;
		union fs_block inblock;
		int indirect = inode.indirect, oldindirect = 0, *olddirect = &(inode.indirect);
		
		while (i > POINTERS_PER_BLOCK - 2) {
			disk_read(indirect, inblock.data);
			oldindirect = indirect;
			olddirect = &(inblock.pointers[POINTERS_PER_BLOCK - 1]);
			indirect = inblock.pointers[POINTERS_PER_BLOCK - 1];
			i -= POINTERS_PER_BLOCK - 1;
		}		
		
		/* Allocate new block for the indirect if necessary - including the following indirect blocks
		(return -1 if the disk is full) */
		if (indirect == 0) {
			int free_block = find_free_block();
			if (free_block == -1)
					return -1;	
			bitmap[free_block] = 1;
			union fs_block temp_block;
			for (int i = 0; i < POINTERS_PER_BLOCK; ++i)
				temp_block.pointers[i] = 0;			
			disk_write(free_block, temp_block.data);
			*olddirect = free_block;
			if(oldindirect)
				disk_write(oldindirect, inblock.data);
			indirect = free_block;
			inode_save(inumber, inode);
		}
		
		disk_read(indirect, inblock.data);
			
		/* Check if a connected block is exsist and allocate now block if not */
		if (inblock.pointers[i] != 0)
			return inblock.pointers[i];
		else {
			int free_block1 = 0;
			free_block1 = find_free_block();
			if (free_block1 == -1)
				return -1;
			bitmap[free_block1] = 1;
			inblock.pointers[i] = free_block1;
			disk_write(indirect, inblock.data);
			return free_block1;
		}
	}
}


/* Load an inode from the inodes table of the disk */
void inode_load(int inumber, struct fs_inode *inode)
{
	int n = (inumber/INODES_PER_BLOCK)+1, j = inumber%INODES_PER_BLOCK;
	union fs_block block;
	disk_read(n,block.data);
	*inode = block.inode[j];
}


/* Save an inode into the inodes table of the disk */
void inode_save(int inumber, struct fs_inode inode)
{
	int n = (inumber/INODES_PER_BLOCK)+1, j = inumber%INODES_PER_BLOCK;
	union fs_block block;
	disk_read(n, block.data);
	block.inode[j] = inode;
	disk_write(n,block.data);
}


/* Provide the spesific wanted block in order to write the data from it */
void provide_block(struct fs_inode inode, union fs_block *block, int i) 
{
	/* Read into block.data the data from the block that connected 
	 to the directive or to the indirective of the inode */
	
	union fs_block indirect_block;
	if (inode.indirect)
		disk_read(inode.indirect ,indirect_block.data);
	
	/* If the block is connect to one of the directives */
	if (i < POINTERS_PER_INODE)		
		disk_read(inode.direct[i], block->data);

	/* If the block is connect to the first indirective */
	else if (i < POINTERS_PER_INODE + POINTERS_PER_BLOCK - 1)
		disk_read(indirect_block.pointers[i - 5] , block->data);		
	
	/* If the block is connect to one of the following indirectives */
	else {
		int temp_indirect = i - POINTERS_PER_INODE;
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
	for (int c = 0; c < POINTERS_PER_INODE; ++c)
	if(inode.direct[c])
		printf("%d, ", inode.direct[c]);
	printf("\033[1;32m\n\tindirect blocks: \033[0m%d\n", inode.indirect);
	if (inode.indirect) {
		printf("\033[1;32m\tindirect data blocks: \033[0m");
		disk_read(inode.indirect ,block.data);
		for (int c = 0; c < POINTERS_PER_BLOCK; ++c) {
			if(block.pointers[c]) 
				printf("%d, ", block.pointers[c]);
		}
	}
	printf("\n");
}
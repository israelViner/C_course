
#ifndef FS_H
#define FS_H

#define FS_MAGIC           0xf0f03410
#define INODES_PER_BLOCK   128
#define POINTERS_PER_INODE 5
#define POINTERS_PER_BLOCK 1024


struct fs_inode {
	int isvalid;
	int size;
	int direct[POINTERS_PER_INODE];
	int indirect;
};

struct fs_superblock {
	int magic;
	int nblocks;
	int ninodeblocks;
	int ninodes;
};

union fs_block {
	struct fs_superblock super;
	struct fs_inode inode[INODES_PER_BLOCK];
	int pointers[POINTERS_PER_BLOCK];
	char data[4096];
};

/* Main functions */
void fs_debug();
int  fs_format();
int  fs_mount();
int  fs_create();
int  fs_delete(int inumber);
int  fs_getsize(int inumber);
int  fs_read( int inumber, char *data, int length, int offset );
int  fs_write( int inumber, const char *data, int length, int offset );

/* Auxiliary functions */
int inode_load(int inumber, struct fs_inode *inode);
void inode_save(int inumber, struct fs_inode inode);
void print_inode(struct fs_inode inode);
int find_free_block();
int find_block(int inumber, int inode_ptr);
void provide_block(struct fs_inode inode, union fs_block *block, int block_ptr);
void color_bitmap(struct fs_inode inode, int color);

#endif
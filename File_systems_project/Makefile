GCC=/usr/bin/gcc

simplefs: Code_files/shell.o Code_files/fs.o Code_files/disk.o
	$(GCC) Code_files/shell.o Code_files/fs.o Code_files/disk.o -o simplefs

Code_files/shell.o: Code_files/shell.c
	$(GCC) -Wall Code_files/shell.c -c -o Code_files/shell.o -g

Code_files/fs.o: Code_files/fs.c Code_files/fs.h
	$(GCC) -Wall Code_files/fs.c -c -o Code_files/fs.o -g

Code_files/disk.o: Code_files/disk.c Code_files/disk.h
	$(GCC) -Wall Code_files/disk.c -c -o Code_files/disk.o -g

clean:
	rm simplefs Code_files/disk.o Code_files/fs.o Code_files/shell.o

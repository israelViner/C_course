#include <stdio.h>
#include <stdlib.h>


/* The main function - the process of the move the disks from the source tower to the target tower*/
void move(int n, char source, char target, char auxiliary)
{
   if (n == 0) {
    return;
   }
    else
    {
        /* Move n - 1 disks from source to auxiliary, so they are out of the way */
        move(n - 1, source, auxiliary, target);

         /* Move the n'th disk from source to target */
        printf("Move the disk from %c to %c\n", source, target);
   
        /* Move the n - 1 disks that we left on auxiliary onto target */
        move(n - 1, auxiliary, target, source);
    }
}
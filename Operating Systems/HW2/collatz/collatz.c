// Phong Nguyenho - ph094398
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <fcntl.h>

/* the size (in bytes) of shared memory object */
const int SIZE = 4096;

/* name of the shared memory object */
const char *name = "OS";

const int bytes = 12;

int counter = 0;

int main(int argc, char **argv)
{
    int collatz = atoi(argv[1]);
    int num = collatz;

    while (num > 1)
    {
        counter++;            

        if (num % 2 == 0)
            num = num / 2;
        else
            num = num * 3 + 1;
    }

    /* shared memory file descriptor */
    int shm_fd;

    /* pointer to shared memory obect */
    void *ptr;

    pid_t pid;

    /* fork a child process */
    pid = fork();

    if (pid < 0) 
    { 
    	/* error occurred */
    	fprintf(stderr, "Fork Failed\n");
    	return 1;
    }
    else if (pid == 0)
    {
        printf("Child Executing\n");

        /* create the shared memory object */
        shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);

        /* configure the size of the shared memory object */
        ftruncate(shm_fd, SIZE);

        /* memory map the shared memory object */
        ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
        
        while (collatz > 1)
        {
            /* write to the shared memory object */
            sprintf(ptr,"%d", collatz);
            ptr += bytes;            

            if (collatz % 2 == 0)
                collatz = collatz / 2;
            else
                collatz = collatz * 3 + 1;
        }
    }
    else 
    { 
	    /* parent process */
	    /* parent will wait for the child to complete */
	    wait(NULL);
        printf("Child Complete\n");
        printf("Parent Executing\n");

        /* open the shared memory object */
        shm_fd = shm_open(name, O_RDONLY, 0666);

        /* memory map the shared memory object */
        ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
        
        while (counter > 0)
        {
            counter--;

            /* read from the shared memory object */
            printf("%s\n",(char *)ptr);
            ptr += bytes;
        }
        printf("1\n");

        /* remove the shared memory object */
        shm_unlink(name);

        printf("Parent Complete\n");
    }
    return 0;
}
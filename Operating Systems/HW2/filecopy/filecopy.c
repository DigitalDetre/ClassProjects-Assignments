// Phong Nguyenho - ph094398
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define BUFFER 128

int main(int argc, char **argv)
{
	int fd[2];
	int counter = 0;
	char child[BUFFER];
	char parent[BUFFER];
	pid_t pid;
	ssize_t bytes;
	
	pipe(fd);

	int source = open(argv[1], O_RDONLY);
	int destination = open(argv[2], O_CREAT | O_WRONLY);

	if (source == -1)
	{
		printf("Source file failed to open, exiting...\n");
		return -1;
	}
	else if (destination == -1)
	{
		printf("Destination file exists, file will not overwrite exiting...\n");
		return -1;
	}

	pid = fork();

	if (pid < 0)
	{
		fprintf(stderr, "Fork Failed\n");
		return 1;
	}
	else if (pid == 0)
	{
		close(fd[1]);
		bytes = read(fd[0], child, sizeof(child));
		printf("Receiving string: %s\n", child);
		write(destination, child, bytes);
	}
	else
	{
		close(fd[0]);
		bytes = read(source, parent, sizeof(parent));
		write(fd[1], parent, bytes);
		close(fd[1]);
	}

	return 0;
}
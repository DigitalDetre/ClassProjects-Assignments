// Phong Nguyenho - ph094398
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include <time.h>
#include <signal.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define MAX_LINE 80 /* The maximum length command */
#define HISTORY_SIZE 11 /* The maximum history size */
char *commandHistory[HISTORY_SIZE];
int countHistory = 0, num = 0;

// Does the command, this is where the real magic happens
static void doCommand(char *inputline)
{
	char *command = strdup(inputline);
	char *args[10];
	int status, argc = 0, process = 0;
	int fd[2];
	pid_t pid;
	args[argc++] = strtok(command, " ");

	while (args[argc - 1] != NULL)
		args[argc++] = strtok(NULL, " ");
	argc--;

	if (strcmp(args[argc - 1], "&") == 0) 
	{
		process = 1;
		args[--argc] = NULL;
	}

	while (argc >= 3)
	{
		if (strcmp(args[argc - 2], ">") == 0)
		{
			fd[1] = open(args[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
			args[argc - 2] = NULL;
			argc -= 2;
		}
		else if (strcmp(args[argc - 2], "<") == 0)
		{
			fd[0] = open(args[argc - 1], O_RDONLY);
			args[argc - 2] = NULL;
			argc -= 2;
		}
		else 
			break;
	}

	pid = fork();

	// Does the forking
	if (pid < 0)
	{
		fprintf(stderr, "Fork Failed\n");
		return;
	}
	else if (pid == 0)
	{
		execvp(args[0], args);
		exit(0);
	}
	else
	{
		close(fd[0]); 
		close(fd[1]);
		if (!process)
			waitpid(pid, &status, 0);
		return;
	}
	free(command);
}

// Adds the command to the list
static void add2list(char *command) 
{
	if (countHistory == (HISTORY_SIZE - 1)) 
	{
		free(commandHistory[0]);

		for (int i = 1; i < countHistory; i++)
			commandHistory[i - 1] = commandHistory[i];

		countHistory--;
	}
	commandHistory[countHistory++] = strdup(command);
	num++;
}

// Does the command from history
static void runHistory(char *command)
{
	int count = 0;
	if (countHistory == 0)
	{
		fprintf(stderr, "No commands in history\n");
		return;
	}

	if (command[1] == '!')
		count = countHistory - 1;
	else 
	{
		count = atoi(&command[1]) - 1;
		if ((count < 0) || (count > countHistory)) 
		{
			fprintf(stderr, "No such command in history.\n");
			return;
		}
	}
	printf("%s\n", command);
	doCommand(commandHistory[count]);
}

// List history of commands
static void list_history()
{
	for (int i = countHistory - 1; i >= 0; i--)
		printf("%i %s\n", num--, commandHistory[i]);
	for (int j = countHistory - 1; j >= 0; j--)
		num++;
}

static void handleSignal(int command)
{
	if (command == SIGTERM)
		;
	else if (command == SIGINT)
		return;
	else if (command == SIGCHLD)
	{
		while (waitpid(-1, NULL, WNOHANG) > 0)
			;
		return;
	}
}

// Runs the trash code
int main(void)
{		
	int flag = 0, should_run = 1;
	size_t line_size = 100;
	struct sigaction new, old;
	new.sa_handler = handleSignal;
	new.sa_flags = 0;
	sigemptyset(&new.sa_mask);

	if ((sigaction(SIGINT, &new, &old) == -1) || (sigaction(SIGCHLD, &new, &old) == -1))
		return -1;

	char *line = malloc(sizeof(char) * line_size);

	if (line == NULL)
		return -1;

	while (should_run)
	{
		if (!flag)
			printf("osh> ");
		fflush(stdout);

		if (getline(&line, &line_size, stdin) == -1)
		{
			if (errno == EINTR)
			{
				clearerr(stdin);
				flag = 1;
				continue;
			}
			break;
		}

		flag = 0;
		int line_len = strlen(line);

		if (line_len == 1)
			continue;

		line[line_len - 1] = '\0';

		if (strcmp(line, "exit") == 0)
			break;
		else if (strcmp(line, "history") == 0) 
			list_history();
		else if (line[0] == '!')
			runHistory(line);
		else
		{
			add2list(line);
			doCommand(line);
		}
	}

	free(line);
	return 0;
}
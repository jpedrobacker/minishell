#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

typedef struct cmd
{
	char **cmds;
	int fd_in;
	int fd_out;
	struct cmd *next;
} cmd;


cmd *make_linked(char **cmds)
{
	cmd *node = (cmd *)malloc(sizeof(cmd));
	node->cmds = cmds;
	node->fd_in = STDIN_FILENO;
	node->fd_out = STDOUT_FILENO;
	node->next = NULL;
	return node;
}

void add_node(cmd **head, char **cmds)
{
	cmd *newNode = make_linked(cmds);
	if (*head == NULL)
	{
		*head = newNode;
	}
	else
	{
		cmd *temp = *head;
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = newNode;
	}
}

void preparePipes(cmd *head)
{
	cmd *current = head;
	while (current != NULL && current->next != NULL)
	{
		int pipefd[2];
		if (pipe(pipefd) == -1)
		{
			perror("pipe");
			exit(1);
		}
		current->fd_out = pipefd[1];
		current->next->fd_in = pipefd[0];
		printf("fd_in: %d, fd_out: %d\n", current->fd_in, current->next->fd_out);
		current = current->next;
	}
}

void exec(cmd *head)
{
	cmd *current = head;
	pid_t pid;

	while (current != NULL)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(1);
		}
		else if (pid == 0)
		{
			printf("CMD: %s, FD_IN: %d, FD_OUT: %d\n", current->cmds[0], current->fd_in, current->fd_out);
			if (current->fd_in != STDIN_FILENO)
				dup2(current->fd_in, 0);
			if (current->fd_out != STDOUT_FILENO)
				dup2(current->fd_out, 1);
			cmd *temp = head;
			while (temp != NULL)
			{
				if (temp->fd_in != STDIN_FILENO)
					close(temp->fd_in);
				if (temp->fd_out != STDOUT_FILENO)
					close(temp->fd_out);
				temp = temp->next;
			}
			execve(current->cmds[0], current->cmds, NULL);
			perror("execve");
			exit(1);
		}

		current = current->next;
	}

	cmd *temp = head;
	while (temp != NULL)
	{
		if (temp->fd_in != STDIN_FILENO)
			close(temp->fd_in);
		if (temp->fd_out != STDOUT_FILENO)
			close(temp->fd_out);
		temp = temp->next;
	}

	current = head;
	while (current != NULL)
	{
		wait(NULL);
		current = current->next;
	}
}

int main()
{
/*	cmd *head = NULL;
	char *ls[] = {"/bin/ls", NULL};
	char *wc[] = {"/usr/bin/wc", "-l", NULL};

	add_node(&head, ls);
	add_node(&head, wc);

	preparePipes(head);
	exec(head);*/
	printf("%d, %d\n", STDIN_FILENO, STDOUT_FILENO);

	return 0;
}

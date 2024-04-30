#include "inc/minishell.h"

int	cd(char *arg)
{
	char	curdir[100];
	printf("%s\n", getcwd(curdir, 100));
	if (chdir(arg) == -1)
	{
		printf("Error! No dir!\n");
	}
	printf("%s\n", getcwd(curdir,100));
	return (0);
}

int main(int ac, char **av, char **envp)
{
	cd("src");
	return (0);
}

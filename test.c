#include "inc/minishell.h"

int main(void)
{
	char *s = getenv("PATH");

	printf("PATH: %s\n", s);
	return (0);
}

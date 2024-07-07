/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:29:24 by jbergfel          #+#    #+#             */
/*   Updated: 2024/07/07 05:28:32 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_status;

void	sig_int_handle(int sig)
{
	extern int	g_status;

	if (sig == SIGINT)
	{
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
	g_status = 130;
}

void	sigs_handle(void)
{
	struct sigaction	sig;

	signal(SIGQUIT, SIG_IGN);
	ft_memset(&sig, 0, sizeof(sig));
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		exit(EXIT_FAILURE);
	sig.sa_handler = sig_int_handle;
	if (sigemptyset(&sig.sa_mask) < 0 || sigaddset(&sig.sa_mask, SIGINT) < 0)
		exit(EXIT_FAILURE);
	if (sigaction(SIGINT, &sig, NULL) < 0)
		exit(EXIT_FAILURE);
}

char	*make_prompt(void)
{
	char	curdir[PATH_MAX];
	char	*prompt;

	prompt = getcwd(curdir, sizeof(curdir));
	prompt = ft_strjoin(prompt, "$>>> ");
	return (prompt);
}

int	validate_prompt(char *usr_input, t_main *main)
{
	(void) main;
	if (!usr_input)
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		exit(EXIT_SUCCESS);
	}
	if (!validate_input(usr_input, main) || !deal_redirects(main))
		return (add_history(usr_input), 0);
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	t_main		bag;

	(void) ac;
	(void) av;
	g_status = 0;
	bag.envs = make_envp_list(envp);
	sigs_handle();
	while (1)
	{
		rl_replace_line("", 0);
		bag.usr_input = readline(make_prompt());
		if (!validate_prompt(bag.usr_input, &bag))
		{
			free(bag.usr_input);
			continue ;
		}
		start_execution(bag.usr_input, &bag);
		//ft_printf("g_status: %d\n", g_status);
		add_history(bag.usr_input);
		free(bag.usr_input);
	}
	return (0);
}

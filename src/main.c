/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:29:24 by jbergfel          #+#    #+#             */
/*   Updated: 2024/06/12 17:47:37 by jbergfel         ###   ########.fr       */
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
}

void	sigs_handle(void)
{
	struct sigaction	sig;

	signal(SIGQUIT, SIG_IGN);
	sig.sa_handler = sig_int_handle;
	sigemptyset(&sig.sa_mask);
	sigaddset(&sig.sa_mask, SIGINT);
	sig.sa_flags = 0;
	sigaction(SIGINT, &sig, NULL);
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
	if (!ft_strlen(usr_input) || !usr_input)
		return (-1);
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	char		*usr_input;
	t_main		bag;
	extern int	g_status;

	(void) ac;
	(void) av;
	bag.envs = make_envp_list(envp);
	sigs_handle();
	while (1)
	{
		usr_input = readline(make_prompt());
		if (!validate_prompt(usr_input, &bag))
		{
			free(usr_input);
			continue ;
		}
		if (!validate_input(usr_input, &bag))
		{
			add_history(usr_input);
			continue ;
		}
		if (!deal_redirects(&bag))
		{
			add_history(usr_input);
			continue ;
		}
		bag.new_input = rev_split(bag.splited_input);
		start_execution(usr_input, &bag);
		ft_printf("g_status: %d\n", g_status);
		add_history(usr_input);
		free(usr_input);
	}
	return (0);
}

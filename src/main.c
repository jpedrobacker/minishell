/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:29:24 by jbergfel          #+#    #+#             */
/*   Updated: 2024/07/08 16:58:47 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_status;

void	make_prompt(t_main *main)
{
	char	curdir[PATH_MAX];
	char	*prompt;

	prompt = getcwd(curdir, sizeof(curdir));
	main->usr_input = ft_strjoin(prompt, "$>>> ");
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
		return (0);
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	t_main	bag;

	(void) ac;
	(void) av;
	g_status = 0;
	bag.envs = make_envp_list(envp);
	sigs_handle();
	while (1)
	{
		rl_replace_line("", 0);
		kill(getpid(), SIGUSR1);
		make_prompt(&bag);
		bag.usr_input = readline(bag.usr_input);
		update_gstatus(bag.envs);
		if (!validate_prompt(bag.usr_input, &bag))
		{
			free(bag.usr_input);
			continue ;
		}
		start_execution(bag.usr_input, &bag);
		add_history(bag.usr_input);
		free(bag.usr_input);
	}
	return (0);
}

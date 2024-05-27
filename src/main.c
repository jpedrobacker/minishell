/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:29:24 by jbergfel          #+#    #+#             */
/*   Updated: 2024/05/27 12:54:40 by aprado           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int ac, char **av, char **envp)
{
	char	*usr_input;
	char	*minshell;
	char	curdir[PATH_MAX];
	char	**splited_input;
	t_varenv	envp_lst;
	t_token		token;

	(void) ac;
	(void) av;
	signal(SIGQUIT, SIG_IGN);
	envp_lst = make_envp_list(envp);
	while (1)
	{
		minshell = ft_strjoin(getcwd(curdir, sizeof(curdir)), "$ ");
		minshell = ft_strnstr(minshell, "home", ft_strlen(minshell));
		usr_input = readline(minshell);
		if (!usr_input)
		{
			ft_printf("Apertei cntrlD");
			exit(EXIT_SUCCESS);
		}
		change_input(usr_input);
		splited_input = split_in_tokens(usr_input, "\"'$ \v", &envp_lst);

		int i = 0;
		while (splited_input[i])
		{
			ft_printf("depois :%s:\n", splited_input[i]);
			i++;
		}
		ft_printf("depois :%s:\n", splited_input[i]);

		token = create_list(usr_input, &envp_lst);
		call_cmd(&token, &envp_lst);
		add_history(usr_input);
		free(usr_input);
	}
	return (0);
}

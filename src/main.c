/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:29:24 by jbergfel          #+#    #+#             */
/*   Updated: 2024/06/03 15:45:47 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_status;

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

char	*make_prompt(void)
{
	char	curdir[PATH_MAX];
	char	*prompt;

	prompt = getcwd(curdir, sizeof(curdir));
	prompt = ft_strjoin(prompt, "$>>> ");
	return (prompt);
}

int	main(int ac, char **av, char **envp)
{
	char	*usr_input;
	//char	**splited_input;
	t_token	token;

	(void) ac, (void) av;
	token.envs_lst = make_envp_list(envp);
	while (1)
	{
		usr_input = readline(make_prompt());
		if (ft_strncmp(usr_input, "", ft_strlen(usr_input)) == 0)
			continue ;
		change_input(usr_input);
		//splited_input = split_in_tokens(usr_input, "\"'$ \v");
		token = create_list(usr_input, token.envs_lst);
		call_cmd(&token);
		add_history(usr_input);
		free(usr_input);
	}
	//(void) usr_input;
	return (0);
}

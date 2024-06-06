/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:29:24 by jbergfel          #+#    #+#             */
/*   Updated: 2024/06/06 10:22:24 by jbergfel         ###   ########.fr       */
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

int	main(int ac, char **av, char **envp)
{
	char		*usr_input;
	t_main		bag;

	(void) ac;
	(void) av;
	bag.envs = make_envp_list(envp);
	sigs_handle();
	while (1)
	{
		usr_input = readline(make_prompt());
		if (!ft_strlen(usr_input) || !usr_input)
		{
			free(usr_input);
			continue ;
		}
		bag.dup_usr_input = ft_strdup(usr_input);
		change_input(bag.dup_usr_input);
		bag.splited_input = split_in_tokens(bag.dup_usr_input, "\"'$ \v", bag.envs);
		bag.new_input = rev_split(bag.splited_input);
		tokenize(&bag);
		//token = create_list(usr_input, envp_lst);
		//free_splits(bag.splited_input);
		call_cmd(&bag);
		add_history(usr_input);
		free(usr_input);
	}
	return (0);
}

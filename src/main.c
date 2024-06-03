/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:29:24 by jbergfel          #+#    #+#             */
/*   Updated: 2024/06/03 16:34:39 by aprado           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_status;

void	sig_int_handle(int sig)
{
	extern int	g_status;

	if (sig == SIGINT)
	{
		if (RL_ISSTATE(RL_STATE_READCMD))
			ioctl(STDIN_FILENO, TIOCSTI, "\n");
		else
			write(STDIN_FILENO, "\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
	}
	return ;
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

int	main(int ac, char **av, char **envp)
{
	char		*usr_input;
	char		curdir[PATH_MAX];
	t_main		bag;

	(void) ac;
	(void) av;
	bag.envs = make_envp_list(envp);
	sigs_handle();
	while (1)
	{
		usr_input = readline(ft_strjoin(getcwd(curdir, sizeof(curdir)), "$ "));
		if (!usr_input)
			return (0);
		bag.dup_usr_input = ft_strdup(usr_input);
		change_input(bag.dup_usr_input); //ACHO que o erro do valgrind vem pela readline+join...
		bag.splited_input = split_in_tokens(bag.dup_usr_input, "\"'$ \v", bag.envs);
		bag.new_input = rev_split(bag.splited_input);
		tokenize(&bag);
		//token = create_list(usr_input, envp_lst);
		//free_splits(bag.splited_input);
		//call_cmd(bag.cmds, bag.envs);
		//ARRUMAR o call cmd...
		add_history(usr_input);
		free(usr_input);
	}
	return (0);
}


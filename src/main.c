/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:29:24 by jbergfel          #+#    #+#             */
/*   Updated: 2024/05/28 13:31:59 by jbergfel         ###   ########.fr       */
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

void	expand_env(t_token *head)
{
	t_token		*aux;
	t_varenv	*temp;
	char		*old;

	aux = head;
	temp = aux->envs_lst;
	if (aux->flag_expand)
	{
		while (temp)
		{
			if (!ft_strncmp(temp->key, aux->env, ft_strlen(temp->key)))
				break ;
			temp = temp->next;
		}
		if (aux->arr_cmd_input[1])
		{
			old = aux->arr_cmd_input[1];
			aux->arr_cmd_input[1] = ft_strdup(temp->var);
			free(old);
		}
	}
}

int	main(int ac, char **av, char **envp)
{
	char		*usr_input;
	char		curdir[PATH_MAX];
	t_varenv	*envp_lst;
	t_token		*token;

	(void) ac;
	(void) av;
	envp_lst = make_envp_list(envp);
	sigs_handle();
	while (1)
	{
		usr_input = readline(ft_strjoin(getcwd(curdir, sizeof(curdir)), "$ "));
		change_input(usr_input);
		token = create_list(usr_input, envp, envp_lst);
		//expand_env(&token);
		call_cmd(token, envp_lst);
		add_history(usr_input);
		free(usr_input);
	}
	return (0);
}

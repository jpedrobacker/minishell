/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:26:30 by jbergfel          #+#    #+#             */
/*   Updated: 2024/07/14 11:17:44 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	change_status_var(t_varenv *env, char *new_var)
{
	t_varenv	*aux_env;

	aux_env = env;
	while (aux_env)
	{
		if (ft_strcmp(aux_env->key, "?") == 0)
		{
			aux_env->var = new_var;
			return (0);
		}
		aux_env = aux_env->next;
	}
	return (1);
}

void	update_gstatus(t_varenv *env)
{
	char		*g_status_char;
	char		*status;
	t_varenv	*aux_env;
	t_varenv	*temp;

	temp = env;
	while (temp)
	{
		if (ft_strcmp("?", temp->key) == 0)
			free(temp->var);
		temp = temp->next;
	}
	aux_env = env;
	g_status_char = ft_itoa(g_status);
	status = ft_strdup(g_status_char);
	change_status_var(aux_env, status);
	free(g_status_char);
}

void	main_exec(t_main *main)
{
	t_token		*token;

	token = main->cmds;
	while (token)
	{
		if (pre_execute(token))
		{
			if (main->cmds->next != NULL)
				exec_cmds_pipe(main, token);
			else
				call_cmd(main, token);
		}
		close_all(token);
		token = token->next;
	}
}

void	wait_all(t_token *token)
{
	t_token	*aux;
	int		status;

	status = 0;
	if (!token)
		return ;
	aux = token;
	while (token)
	{
		if (token->pid != 0 && !our_builtins(token->cmd))
			waitpid(token->pid, &status, 0);
		token = token->next;
	}
	token = aux;
	while (token)
	{
		if (status >= 0 && !our_builtins(token->cmd) && test_exec(token) == 1)
			g_status = WEXITSTATUS(status);
		token = token->next;
	}
	return ;
}

void	start_execution(char *usr_input, t_main *main)
{
	(void) usr_input;
	main->new_input = rev_split(main->splited_input);
	tokenize(main);
	if (!make_pipe(main))
		ft_putstr_fd("Pipe Error.\n", 2);
	ordering_fds(main);
	main_exec(main);
	wait_all(main->cmds);
	free_all(main);
	token_free(&main->cmds);
}

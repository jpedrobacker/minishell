/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 11:21:24 by jbergfel          #+#    #+#             */
/*   Updated: 2024/07/07 05:00:34 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_builtins(t_main *main, t_token *token)
{
	int	status;

	status = 0;
	if (ft_strcmp("cd", token->cmd) == 0)
		status = built_cd(main, token);
	if (ft_strcmp("echo", token->cmd) == 0)
		status = built_echo(main, token, echo_flag(token->args));
	if (ft_strcmp("env", token->cmd) == 0)
		status = built_env(main, token);
	if (ft_strcmp("pwd", token->cmd) == 0)
		status = built_pwd();
	if (ft_strcmp("export", token->cmd) == 0)
		status = built_export(main->envs, token);
	if (ft_strcmp("unset", token->cmd) == 0)
		status = built_unset(main, token);
	if (ft_strcmp("clear", token->cmd) == 0)
		status = built_clear(token);
	if (ft_strcmp("exit", token->cmd) == 0)
		built_exit(main);
	g_status = status;
	return (status);
}

void	check_builtins_pipes(t_main *main, t_token *token)
{
	if (ft_strcmp("cd", token->cmd) == 0)
		exit(built_cd(main, token));
	if (ft_strcmp("echo", token->cmd) == 0)
		exit(built_echo(main, token, echo_flag(token->args)));
	if (ft_strcmp("env", token->cmd) == 0)
		exit(built_env(main, token));
	if (ft_strcmp("pwd", token->cmd) == 0)
		exit(built_pwd());
	if (ft_strcmp("export", token->cmd) == 0)
		exit(built_export(main->envs, token));
	if (ft_strcmp("unset", token->cmd) == 0)
		exit(built_unset(main, token));
	if (ft_strcmp("clear", token->cmd) == 0)
		exit(built_clear(token));
	if (ft_strcmp("exit", token->cmd) == 0)
		built_exit(main);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 11:21:24 by jbergfel          #+#    #+#             */
/*   Updated: 2024/07/01 09:55:47 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_builtins(t_main *main)
{
	int	status;

	status = 0;
	if (ft_strcmp("cd", main->cmds->cmd) == 0)
		status = built_cd(main);
	if (ft_strcmp("echo", main->cmds->cmd) == 0)
		status = built_echo(main, echo_flag(main->cmds->args));
	if (ft_strcmp("env", main->cmds->cmd) == 0)
		status = built_env(main);
	if (ft_strcmp("pwd", main->cmds->cmd) == 0)
		status = built_pwd();
	if (ft_strcmp("export", main->cmds->cmd) == 0)
		status = built_export(main);
	if (ft_strcmp("unset", main->cmds->cmd) == 0)
		status = built_unset(main);
	if (ft_strcmp("clear", main->cmds->cmd) == 0)
		status = built_clear();
	if (ft_strcmp("exit", main->cmds->cmd) == 0)
		built_exit(main);
	//post_builtins(main);
	return (status);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buitlincall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 13:00:52 by jbergfel          #+#    #+#             */
/*   Updated: 2024/06/11 14:51:41 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	call_cmd(t_main *main)
{
	int	status;

	status = 0;
	if (ft_strcmp("cd", main->cmds->arr[0]) == 0)
		status = built_cd(&main);
	if (ft_strcmp("echo", main->cmds->arr[0]) == 0)
		status = built_echo(&main, echo_flag(main->cmds->arr));
	if (ft_strcmp("env", main->cmds->arr[0]) == 0)
		status = built_env(&main);
	if (ft_strcmp("exit", main->cmds->arr[0]) == 0)
		built_exit(main);
	if (ft_strcmp("pwd", main->cmds->arr[0]) == 0)
		status = built_pwd();
	if (ft_strcmp("export", main->cmds->arr[0]) == 0)
		status = built_export(&main);
	if (ft_strcmp("unset", main->cmds->arr[0]) == 0)
		status = built_unset(main);
	if (ft_strcmp("clear", main->cmds->arr[0]) == 0)
		status = built_clear();
	return (status);
}

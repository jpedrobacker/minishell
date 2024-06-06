/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buitlincall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 13:00:52 by jbergfel          #+#    #+#             */
/*   Updated: 2024/06/06 11:52:23 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	call_cmd(t_main *main)
{
	if (ft_strcmp("cd", main->cmds->arr[0]) == 0)
		built_cd(&main);
	if (ft_strcmp("echo", main->cmds->arr[0]) == 0)
		built_echo(&main, echo_flag(main->cmds->arr));
	if (ft_strcmp("env", main->cmds->arr[0]) == 0)
		built_env(&main);
	if (ft_strcmp("exit", main->cmds->arr[0]) == 0)
		built_exit(main);
	if (ft_strcmp("pwd", main->cmds->arr[0]) == 0)
		built_pwd();
	if (ft_strcmp("export", main->cmds->arr[0]) == 0)
		built_export(&main);
	if (ft_strcmp("unset", main->cmds->arr[0]) == 0)
		built_unset(&main);
	if (ft_strcmp("clear", main->cmds->arr[0]) == 0)
		built_clear();
}

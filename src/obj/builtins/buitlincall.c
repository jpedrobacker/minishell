/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buitlincall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 13:00:52 by jbergfel          #+#    #+#             */
/*   Updated: 2024/06/04 11:39:19 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	call_cmd(t_main *main)
{
	if (ft_strncmp("cd", main->cmds->arr[0], ft_strlen(main->cmds->arr[0])) == 0)
		built_cd(&main);
	if (ft_strncmp("echo", main->cmds->arr[0], ft_strlen(main->cmds->arr[0])) == 0)
		built_echo(&main, echo_flag(main->cmds->arr));
	if (ft_strncmp("env", main->cmds->arr[0], ft_strlen(main->cmds->arr[0])) == 0)
		built_env(&main);
	if (ft_strncmp("exit", main->cmds->arr[0], ft_strlen(main->cmds->arr[0])) == 0)
		built_exit(main);
	if (ft_strncmp("pwd", main->cmds->arr[0], ft_strlen(main->cmds->arr[0])) == 0)
		built_pwd();
	if (ft_strncmp("export", main->cmds->arr[0], ft_strlen(main->cmds->arr[0])) == 0)
		built_export(&main);
	if (ft_strncmp("unset", main->cmds->arr[0], ft_strlen(main->cmds->arr[0])) == 0)
		built_unset(&main);
	if (ft_strncmp("clear", main->cmds->arr[0], ft_strlen(main->cmds->arr[0])) == 0)
		built_clear();
}

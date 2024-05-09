/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buitlincall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 13:00:52 by jbergfel          #+#    #+#             */
/*   Updated: 2024/05/09 15:39:28 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	call_cmd(char *cmd, char **envp)
{
	if (ft_strncmp("cd", cmd, ft_strlen(cmd)) == 0)
		built_cd("..");
	if (ft_strncmp("echo", cmd, ft_strlen(cmd)) == 0)
		built_echo("test", "");
	if (ft_strncmp("env", cmd, ft_strlen(cmd)) == 0)
		built_env(envp);
	if (ft_strncmp("exit", cmd, ft_strlen(cmd)) == 0)
		built_exit();
	if (ft_strncmp("pwd", cmd, ft_strlen(cmd)) == 0)
		built_pwd();
	if (ft_strncmp("export", cmd, ft_strlen(cmd)) == 0)
		built_export(envp);
	//if (ft_strncmp("unset", cmd, ft_strlen(cmd)) == 0)
}

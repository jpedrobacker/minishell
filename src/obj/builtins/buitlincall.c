/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buitlincall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 13:00:52 by jbergfel          #+#    #+#             */
/*   Updated: 2024/06/04 13:21:13 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	update_pwd(t_main **main)
{
	t_varenv	*aux_env;
	char		new_pwd[PATH_MAX];
	char		*new_for_real_pwd;

	aux_env = (*main)->envs;
	getcwd(new_pwd, sizeof(new_pwd));
	new_for_real_pwd = ft_strdup(new_pwd);
	while (aux_env != NULL)
	{
		if (ft_strncmp("PWD", aux_env->key, ft_strlen("PWD")) == 0)
		{
			aux_env->var = new_for_real_pwd;
			return (0);
		}
		aux_env = aux_env->next;
	}
	return (1);
}

void	call_cmd(t_main *main)
{
	if (ft_strncmp("cd", main->cmds->arr[0], ft_strlen(main->cmds->arr[0])) == 0)
	{
		built_cd(&main);
		update_pwd(&main);
	}
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

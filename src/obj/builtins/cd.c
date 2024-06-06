/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:38:14 by jbergfel          #+#    #+#             */
/*   Updated: 2024/06/05 11:13:21 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	update_old_pwd(t_varenv **env)
{
	char	*old_pwd;
	t_varenv	*aux_env;

	aux_env = (*(env));
	old_pwd = find_var_key(&aux_env, "PWD");
	while (aux_env)
	{
		if (ft_strncmp("OLDPWD", aux_env->key, ft_strlen("OLDPWD")) == 0)
		{
			aux_env->var = old_pwd;
			return (0);
		}
		aux_env = aux_env->next;
	}
	return (1);
}

int	update_new_pwd(t_main **main)
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

int	built_cd(t_main **main)
{
	t_token		*aux_cmds;
	t_varenv	*aux_env;
	int			args;

	aux_cmds = (*main)->cmds;
	aux_env = (*main)->envs;
	args = count_cmds(aux_cmds->arr);
	if (args > 2)
	{
		errors_mini(QUOTE, "cd");
		return (1);
	}
	if (args == 1)
	{
		chdir(find_var_key(&aux_env, "HOME"));
		return (update_old_pwd(&aux_env));
	}
	if (ft_strncmp(aux_cmds->arr[1], "~", ft_strlen("~")) == 0)
	{
		chdir(find_var_key(&aux_env, "HOME"));
		return (update_old_pwd(&aux_env));
	}
	if (chdir(aux_cmds->arr[1]) != -1)
		return (update_old_pwd(&aux_env));
	errors_mini(NDIR, "cd");
	return (1);
}

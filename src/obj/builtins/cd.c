/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:38:14 by jbergfel          #+#    #+#             */
/*   Updated: 2024/06/04 11:12:02 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
		return (0);
	}
	if (ft_strncmp(aux_cmds->arr[1], "~", ft_strlen("~")) == 0)
	{
		chdir(find_var_key(&aux_env, "HOME"));
		return (0);
	}
	if (chdir(aux_cmds->arr[1]) != -1)
		return (0);
	errors_mini(NDIR, "cd");
	return (1);
}

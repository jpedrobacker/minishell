/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:38:14 by jbergfel          #+#    #+#             */
/*   Updated: 2024/06/04 10:08:31 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	built_cd(t_token **token)
{
	t_token		*aux_token;
	int			args;

	aux_token = (*(token));
	args = count_cmds(aux_token->arr_cmd_input);
	if (args > 2)
	{
		errors_mini(QUOTE, "cd");
		return (1);
	}
	if (args == 1)
	{
		chdir(find_var_key(&aux_token->envs_lst, "HOME"));
		return (0);
	}
	if (ft_strncmp(aux_token->arr_cmd_input[1], "~", ft_strlen("~")) == 0)
	{
		chdir(find_var_key(&aux_token->envs_lst, "HOME"));
		return (0);
	}
	if (chdir(aux_token->arr_cmd_input[1]) != -1)
		return (0);
	errors_mini(NDIR, "cd");
	return (1);
}

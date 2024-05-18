/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:38:14 by jbergfel          #+#    #+#             */
/*   Updated: 2024/05/18 14:36:48 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	built_cd(t_token **token)
{
	t_token	*aux;
	int		args;

	aux = (*(token));
	args = count_cmds(aux->arr_cmd_input);
	if (args != 1)
	{
		errors_mini(QUOTE, "cd");
		return (1);
	}
	if (chdir(aux->arr_cmd_input[1]) != -1)
		return (0);
	errors_mini(NDIR, "cd");
	return (1);
}

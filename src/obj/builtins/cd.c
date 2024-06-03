/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:38:14 by jbergfel          #+#    #+#             */
/*   Updated: 2024/06/03 14:10:13 by aprado           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	built_cd(t_token **token)
{
	t_token	*aux;
	int		args;

	aux = (*(token));
	args = count_cmds(aux->arr);
	if (args != 2)
	{
		errors_mini(QUOTE, "cd");
		return (1);
	}
	if (chdir(aux->arr[1]) != -1)
		return (0);
	errors_mini(NDIR, "cd");
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:36:50 by jbergfel          #+#    #+#             */
/*   Updated: 2024/05/18 10:39:22 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	built_echo(t_token **token, int flag)
{
	t_token	*aux;
	int		args;
	int		i;

	aux = (*(token));
	args = count_cmds(aux->arr_cmd_input);
	if (flag == 0)
		i = 2;
	else
		i = 1;
	while (i < args)
	{
		ft_printf("%s", aux->arr_cmd_input[i]);
		i++;
	}
	if (flag == 0)
		return ;
	ft_printf("\n");
}

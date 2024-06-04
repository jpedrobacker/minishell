/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:36:50 by jbergfel          #+#    #+#             */
/*   Updated: 2024/06/04 11:14:27 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	built_echo(t_main **main, int flag)
{
	t_token	*aux;
	int		args;
	int		i;
	int		j;

	aux = (*main)->cmds;
	args = count_cmds(aux->arr);
	if (flag == 0)
		i = 1;
	else
		i = 0;
	while (++i < args)
	{
		j = -1;
		while (aux->arr[i][++j])
		{
			while (aux->arr[i][j] == ' ' || aux->arr[i][j] == '"' || aux->arr[i][j] == '\'')
				j++;
			if (aux->arr[i][j - 1] == ' ')
				write(1, " ", 1);
			if (aux->arr[i][j] != '\0' )
				write(1, &aux->arr[i][j], 1);
		}
		if (aux->arr[i + 1] != NULL)
			ft_printf(" ");
	}
	if (flag == 0)
		return ;
	ft_printf("\n");
}

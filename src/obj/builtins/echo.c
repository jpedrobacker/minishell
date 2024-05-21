/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:36:50 by jbergfel          #+#    #+#             */
/*   Updated: 2024/05/21 13:16:46 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	built_echo(t_token **token, int flag)
{
	t_token	*aux;
	int		args;
	int		i;
	int		j;

	aux = (*(token));
	args = count_cmds(aux->arr_cmd_input);
	if (flag == 0)
		i = 1;
	else
		i = 0;
	while (++i < args)
	{
		j = -1;
		while (aux->arr_cmd_input[i][++j])
		{
			while (aux->arr_cmd_input[i][j] == ' ' || aux->arr_cmd_input[i][j] == '"' || aux->arr_cmd_input[i][j] == '\'')
				j++;
			if (aux->arr_cmd_input[i][j - 1] == ' ')
				write(1, " ", 1);
			if (aux->arr_cmd_input[i][j] != '\0' )
				write(1, &aux->arr_cmd_input[i][j], 1);
		}
		if (aux->arr_cmd_input[i + 1] != NULL)
			ft_printf(" ");
	}
	if (flag == 0)
		return ;
	ft_printf("\n");
}

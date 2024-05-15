/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:36:50 by jbergfel          #+#    #+#             */
/*   Updated: 2024/05/15 11:25:20 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	built_echo(t_token **token)
{
	t_token	*aux;

	aux = (*(token));
	if (ft_strncmp(aux->arr_cmd_input[1], "-n", ft_strlen("-n")) == 0)
	{
		if (!aux->arr_cmd_input[2])
		{
			errors_mini(NCMD, "echo");
			return (1);
		}
		ft_printf("%s", aux->arr_cmd_input[2]);
		return (0);
	}
	else
	{
		ft_printf("%s\n", aux->arr_cmd_input[1]);
		return (0);
	}
	return (1);
}

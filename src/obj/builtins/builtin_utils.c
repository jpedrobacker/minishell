/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 10:12:36 by jbergfel          #+#    #+#             */
/*   Updated: 2024/05/18 10:30:46 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	echo_flag(t_token **token)
{
	t_token **aux;
	int		i;
	int		flag;

	aux = (*(token));
	i = 0;
	flag = 1;
	while (aux->arr_cmd_input[i])
	{
		if (ft_strncmp(aux->arr_cmd_input[i], "-n", ft_strlen("-n")) == 0)
			flag = 0;
		i++;
	}
	return (flag);
}

int	count_cmds(char **args)
{
	int		i;

	i = 0;
	while (args)
		i++;
	return (i);
}

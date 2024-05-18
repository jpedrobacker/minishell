/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 10:12:36 by jbergfel          #+#    #+#             */
/*   Updated: 2024/05/18 11:21:17 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	echo_flag(char **args)
{
	int		i;
	int		flag;

	i = 0;
	flag = 1;
	while (args[i] != NULL)
	{
		if (ft_strncmp(args[i], "-n", ft_strlen("-n")) == 0)
			return (flag = 0);
		i++;
	}
	return (flag);
}

int	count_cmds(char **args)
{
	int		i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

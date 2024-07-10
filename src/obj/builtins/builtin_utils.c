/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 10:12:36 by jbergfel          #+#    #+#             */
/*   Updated: 2024/07/10 16:39:30 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	echo_flag(char **args)
{
	int		flag;

	flag = 1;
	if (!args[1])
		return (0);
	if (ft_strncmp(args[1], "-n", ft_strlen("-n")) == 0)
		return (flag = 0);
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

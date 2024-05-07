/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:36:50 by jbergfel          #+#    #+#             */
/*   Updated: 2024/05/04 14:30:28 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	built_echo(char *str, char *flag)
{
	if (ft_strncmp(flag, "-n", ft_strlen(flag)) == 0)
	{
		ft_printf("%s", str);
		return (0);
	}
	else
		ft_printf("%s\n", str);
	return (0);
}

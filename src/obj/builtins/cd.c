/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:38:14 by jbergfel          #+#    #+#             */
/*   Updated: 2024/04/30 12:40:20 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	cd(char *arg)
{
	char	curdir[100];
	ft_printf("%s\n", getcwd(curdir, 100));
	chdir(arg);
	ft_printf("%s\n", getcwd(curdir,100));
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:39:02 by jbergfel          #+#    #+#             */
/*   Updated: 2024/07/01 22:55:46 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	built_exit(t_main *main)
{
	free_all(main);
	ft_putendl_fd("exit", STDOUT_FILENO);
	exit(EXIT_SUCCESS);
}

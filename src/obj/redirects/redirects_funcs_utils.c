/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_funcs_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 16:22:56 by aprado            #+#    #+#             */
/*   Updated: 2024/07/12 14:45:56 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	append_func(t_token *node, t_main *bag, int i)
{
	int	fd;

	(void)bag;
	fd = 0;
	if (!node->arr[i + 1])
		return (-1);
	fd = open(node->arr[i + 1], O_CREAT | O_RDWR | O_APPEND, 00777);
	if (fd < 0)
	{
		ft_putstr_fd("Error: ", 2);
		write(2, node->arr[i + 1], ft_strlen(node->arr[i + 1]));
		ft_putstr_fd(": No such file or directory\n", 2);
		return (-1);
	}
	return (fd);
}

int	redirect_in(t_token *node, t_main *bag, int i)
{
	int	fd;

	(void)bag;
	fd = 0;
	if (!node->arr[i + 1])
		return (-1);
	if (!access(node->arr[i + 1], F_OK | R_OK))
		fd = open(node->arr[i + 1], O_RDONLY);
	else
		fd = -1;
	if (fd < 0)
	{
		ft_putstr_fd("Error: ", 2);
		write(2, node->arr[i + 1], ft_strlen(node->arr[i + 1]));
		ft_putstr_fd(": No such file or directory\n", 2);
		return (-1);
	}
	return (fd);
}

int	redirect_out(t_token *node, t_main *bag, int i)
{
	int	fd;

	(void)bag;
	fd = 0;
	if (!node->arr[i + 1])
		return (-1);
	fd = open(node->arr[i + 1], O_CREAT | O_RDWR | O_TRUNC, 00777);
	if (fd < 0)
	{
		ft_putstr_fd("Error: ", 2);
		write(2, node->arr[i + 1], ft_strlen(node->arr[i + 1]));
		ft_putstr_fd(": No such file or directory\n", 2);
		return (-1);
	}
	return (fd);
}

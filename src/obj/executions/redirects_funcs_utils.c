/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_funcs_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprado <aprado@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 16:22:56 by aprado            #+#    #+#             */
/*   Updated: 2024/06/25 17:55:33 by aprado           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//node->fd_in
//node->fd_out
void	heredoc_func(t_token *node, t_main *bag, int i)
{
	(void)bag;
	(void)node;
	(void)i;
	ft_printf("EXECUTING HD\n");
}

void	append_func(t_token *node, t_main *bag, int i)
{
	(void)bag;
	(void)node;
	(void)i;
	ft_printf("EXECUTING AP\n");
}

void	redirect_in(t_token *node, t_main *bag, int i)
{
	(void)bag;
	if (!node->arr[i + 1])
	{
		//FREE NAS PARADA TODA
		return ;
	}
	node->fd_in = open(node->arr[i + 1], O_RDONLY);
	if (node->fd_in < 0)
	{
		//FREE NAS PARADA TODA
		return (ft_putstr_fd("1- No such file or directory\n", 2));
	}
	if (dup2(node->fd_in, 0) == -1)
	{
		//FREE NAS PARADA TODA
		return (ft_putstr_fd("2- No such file or directory\n", 2));
	}
	//close(STDOUT_FILENO);
}

void	redirect_out(t_token *node, t_main *bag, int i)
{
	(void)bag;
	if (!node->arr[i + 1])
	{
		//FREE NAS PARADA TODA
		return ;
	}
	node->fd_out = open(node->arr[i + 1], O_CREAT | O_RDWR | O_TRUNC, 00700);
	if (node->fd_out < 0)
	{
		//FREE NAS PARADA TODA
		return (ft_putstr_fd("No such file or directory", 2));
	}
	if (dup2(node->fd_out, 1) == -1)
	{
		//FREE NAS PARADA TODA
		return (ft_putstr_fd("No such file or directory", 2));
	}
	ft_printf("END REDIR OUT\n");
}

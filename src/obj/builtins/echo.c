/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:36:50 by jbergfel          #+#    #+#             */
/*   Updated: 2024/07/16 13:49:41 by aprado           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	check_quotes(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == 39 || s[i] == 34)
			return (0);
		i++;
	}
	return (1);
}

static void	print_with_quotes(char *s, int fd)
{
	int		i;
	char	c;

	i = -1;
	if (!s)
		return ;
	while (s[++i])
	{
		if (s[i] == 39 || s[i] == 34)
		{
			c = s[i];
			i++;
			while (s[i] && s[i] != c)
			{
				ft_putchar_fd(s[i], fd);
				i++;
			}
			if (!s[i])
				return ;
		}
		else
			ft_putchar_fd(s[i], fd);
	}
}

int	built_echo(t_token *token, int flag)
{
	t_token	*aux;
	int		args;
	int		i;

	aux = token;
	args = count_cmds(aux->args);
	if (args == 1)
		return (ft_putstr_fd("\n", token->fd_out), 0);
	i = 0;
	if (flag == 0)
		i = 1;
	while (++i < args)
	{
		if (!check_quotes(aux->args[i]))
			print_with_quotes(aux->args[i], aux->fd_out);
		else
			ft_putstr_fd(aux->args[i], aux->fd_out);
		if (aux->args[i + 1])
			ft_putchar_fd(' ', token->fd_out);
	}
	if (flag == 0)
		return (0);
	return (ft_putstr_fd("\n", token->fd_out), 0);
}

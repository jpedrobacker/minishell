/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:26:28 by aprado            #+#    #+#             */
/*   Updated: 2024/07/10 12:08:44 by aprado           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	check_special(char c, char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (c == s[i])
			return (0);
		i++;
	}
	return (1);
}

static int	end_with_pipe(char *s)
{
	int	len;

	if (!s)
		return (0);
	len = ft_strlen(s);
	len--;
	while (len >= 0)
	{
		if (s[len] == ' ' || s[len] == '\t')
			len--;
		else
			break ;
	}
	if (!check_special(s[len], "<>|"))
		return (0);
	return (1);
}

static int	start_with_pipe(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == ' ' || s[i] == '\t')
			i++;
		else
			break ;
	}
	if (s[i] == '|')
		return (0);
	return (1);
}

static int	check_wspaces(char *s)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == 32 || s[i] == '\t' || s[i] == '\v')
			i++;
		else
			c++;
		if (c != 0)
			break ;
	}
	if (c != 0)
		return (1);
	return (0);
}

int	validate_input(char *s, t_main *bag)
{
	if (!s)
		return (0);
	if (!check_wspaces(s))
		return (ft_putstr_fd("INVALID INPUT\n", 2), 0);
	if (!end_with_pipe(s) || !start_with_pipe(s))
		return (ft_putstr_fd("INVALID INPUT\n", 2), 0);
	if (!check_invalid_pipe(s))
		return (ft_putstr_fd("INVALID INPUT\n", 2), 0);
	if (!check_invalid_redirects(s))
		return (ft_putstr_fd("INVALID INPUT\n", 2), 0);
	ft_printf("VALIDO!\n");
	bag->dup_usr_input = ft_strdup(s);
	if (!change_input(bag->dup_usr_input))
	{
		free(bag->dup_usr_input);
		ft_putstr_fd("Error quote> \n", 2);
		return (0);
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprado <aprado@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:26:28 by aprado            #+#    #+#             */
/*   Updated: 2024/06/17 13:31:38 by aprado           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_special(char c, char *s)
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

static int	starts_with_pipe(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == ' ' || s[i] == '\t')
			i++;
		else
			break ;
	}
	if (is_appendoc(s, '<', i))
		return (1);
	if (!check_special(s[i], "><|"))
		return (0);
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

static void	deal_with_first(char *s, int *i)
{
	if (!is_appendoc(s, '<', i))
		return (0);
	while (s[*i])
	{
		if (
	}
}

static int	check_input(char *s)
{
	int	i;

	i = 0;
	while (s[i] != ' ' || s[i] != '\t')
		i++;
	while (s[i])
	{
		if (s[i] == '<')
			deal_with_first(s, &i);
		else if (s[i] == '>')
			deal_with_second(s, &i);
		else if (s[i] == '|')
			deal_with_third(s, &i);
		if (s[i])
			i++;
		else
			break ;
	}
}

//echo < | cat kkk
//input invalido...
int	validate_input(char *s, t_main *bag)
{
	if (!s)
		return (0);
	if (!check_wspaces(s))
		return (ft_putstr_fd("Error", 2), 0);
	if (!check_input(s))
		return (ft_putstr_fd("Error", 2), 0);

	/*
	if (!s)
		return (0);
	if (!check_wspaces(s))
		return (ft_putstr_fd("INVALID INPUT\n", 2), 0);
	if (!end_with_pipe(s) || !starts_with_pipe(s))
		return (ft_putstr_fd("INVALID INPUT\n", 2), 0);
	if (!check_invalid_pipe(s))
		return (ft_putstr_fd("INVALID INPUT\n", 2), 0);
	if (!check_invalid_redirects(s))
		return (ft_putstr_fd("INVALID INPUT\n", 2), 0);
	ft_printf("VALIDO!\n");
	*/
	bag->dup_usr_input = ft_strdup(s);
	change_input(bag->dup_usr_input);
	return (1);
}
//dupo a usr_input
//mando o change input

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprado <aprado@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:26:28 by aprado            #+#    #+#             */
/*   Updated: 2024/06/20 13:35:42 by aprado           ###   ########.fr       */
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

/*

//Funcao para dupar uma string mas sem os espacos 
//mando pra change_input()
//faco as validacoes necessarias
//free(duped_sem_space)
//return erro ou certo

int	len_no_space(char *s)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] != ' ')
			len++;
		i++;
	}
	return (len);
}

char	*dup_no_space(char *s, int len)
{
	int		i;
	int		x;
	char	*new;

	if (!s)
		return (NULL);
	i = 0;
	x = 0;
	new = malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	new[len] = '\0';
	while (s[i])
	{
		if (s[i] != ' ')
		{
			new[x] = s[i];
			x++;
		}
		i++;
	}
	return (new);
}

char	*string_no_space(char *s)
{
	int		len;
	char	*temp;
	char	*dup;
	char	**input;

	if (!s)
		return (NULL);
	temp = ft_strdup(s);
	len = len_no_space(s);
	change_input(temp);
	dup = dup_no_space(temp, len);
	free(temp);
	replace_char(dup, '\t', '|');
	replace_char(dup, '\v', ' ');
	replace_char(dup, '\a', '>');
	replace_char(dup, '\n', '<');
	input = split_to_validate(dup, "<>|");
	int i = 0;
	while (input[i])
	{
		ft_printf("-> :%s: \n", input[i]);
		i++;
	}


	return (dup);
}
*/

//echo < | cat kkk
//input invalido...
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

	/*
	char *temp;
	temp = string_no_space(s);
	ft_printf("--> :%s: \n", temp);
	*/

	bag->dup_usr_input = ft_strdup(s);
	change_input(bag->dup_usr_input);
	return (1);
}

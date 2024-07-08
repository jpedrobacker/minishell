/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:36:50 by jbergfel          #+#    #+#             */
/*   Updated: 2024/07/08 12:57:39 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_quotes(char *s)
{
	int	len;

	if (!s)
		return (1);
	len = ft_strlen(s) - 1;
	if ((s[0] == '\"' && s[len] == '\"') || (s[0] == '\'' && s[len] == '\''))
		return (0);
	return (1);
}

void	print_with_no_quotes(t_token *token, char **arr, int i)
{
	int	j;
	int	len;

	if (!arr[i])
		return ;
	j = 1;
	len = ft_strlen(arr[i]);
	while (arr[i][j])
	{
		if (arr[i][j] == '\0' || j == len - 1)
			break ;
		ft_putchar_fd(arr[i][j], token->fd_out);
		j++;
	}
}

int	built_echo(t_main *main, t_token *token, int flag)
{
	t_token	*aux;
	int		args;
	int		i;
	(void) main;

	aux = token;
	args = count_cmds(aux->arr);
	i = 0;
	if (flag == 0)
		i = 1;
	while (++i < args)
	{
		if (ft_strcmp(aux->arr[i], ">") == 0)
			i = i + 2;
		if (check_quotes(aux->arr[i]) == 1 && aux->arr[i] != NULL)
			ft_putstr_fd(aux->arr[i], token->fd_out);
		else if (aux->arr[i] != NULL)
			print_with_no_quotes(token, aux->arr, i);
		if (aux->arr[i + 1])
			ft_putchar_fd(' ', token->fd_out);
	}
	if (flag == 0)
		return (1);
	ft_putstr_fd("\n", token->fd_out);
	return (1);
}

//Return de erros do echo

/*
	Caso passe por exemplo echo (teste) $? = 2
*/

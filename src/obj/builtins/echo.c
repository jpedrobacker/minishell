/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:36:50 by jbergfel          #+#    #+#             */
/*   Updated: 2024/06/14 16:17:42 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_quotes(char *s)
{
	int	len;

	len = ft_strlen(s) - 1;
	if ((s[0] == '"' && s[len] == '"') || (s[0] == '\'' && s[len] == '\''))
		return (0);
	return (1);
}

void	print_with_no_quotes(char **arr, int i)
{
	int	j;

	j = -1;
	while (arr[i][++j])
	{
		while (arr[i][j] == ' ' || arr[i][j] == '"' || arr[i][j] == '\'')
			j++;
		if (arr[i][j - 1] == ' ')
			write(1, " ", 1);
		if (arr[i][j] != '\0' )
			write(1, &arr[i][j], 1);
	}
	if (arr[i + 1] != NULL)
		ft_printf(" ");
}

int	built_echo(t_main **main, int flag)
{
	extern int	g_status;
	t_token	*aux;
	int		args;
	int		i;
	int		j;

	aux = (*main)->cmds;
	args = count_cmds(aux->arr);
	i = 0;
	if (flag == 0)
		i = 1;
	while (++i < args)
	{
		j = -1;
		if (check_quotes(aux->arr[i]) == 0)
		{
			while (aux->arr[i][++j])
				write(1, &aux->arr[i][j], 1);
		}
		else
			print_with_no_quotes(aux->arr, i);
	}
	if (flag == 0)
		return (g_status = 1);
	ft_printf("\n");
	return (g_status = 1);
}

//Return de erros do echo

/*
	Caso passe por exemplo echo (teste) $? = 2
*/

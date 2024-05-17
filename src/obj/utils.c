/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprado <aprado@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:30:13 by aprado            #+#    #+#             */
/*   Updated: 2024/05/17 17:16:31 by aprado           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_there_var(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
			if (s[i + 1] && ft_isalnum(s[i + 1]))
				return (1);
		i++;
	}
	return (0);
}

char	*get_env_name(char *s, int flag)
{
	char	*env;
	int		i;
	int		len;

	if (!flag)
		return (NULL);
	i = 0;
	len = 0;
	while (s[i] && s[i] != '$')
		i++;
	i++;
	while (s[i] && ft_isalnum(s[i]))
	{
		i++;
		len++;
	}
	env = malloc(sizeof(char) * (len + 1));
	if (!env)
		return (NULL);
	env[len] = '\0';
	while (len != -1)
		env[--len] = s[--i];
	return (env);
}

void	expand_func(t_token **node)
{
	t_token *aux;

	aux = *node;
	ft_printf("OPAAA :%i:\n", aux->flag_expand);
}

void	fix_matrix(t_token **head)
{
	t_token	*aux;
	int		i;

	i = 0;
	aux = *head;
	while (aux)
	{
		while (aux->arr_cmd_input[i])
		{
			replace_char(aux->arr_cmd_input[i], '\v', ' ');
			i++;
		}
		i = 0;
		if (aux->flag_expand)
			expand_func(&aux);
		aux = aux->next;
	}
}

void	print_list(t_token **head)
{
	t_token	*aux;
	int		i;

	i = 0;
	aux = *head;
	while (aux)
	{
		//replace_char(aux->cmd_input, '\v', ' ');
		ft_printf("-------------------------------\n");
		ft_printf("command input :%s:\n", aux->cmd_input);
		ft_printf("comand :%s:\n", aux->cmd_name);
		ft_printf("path :%s:\n", aux->real_path);
		ft_printf("env name :%s:\n", aux->env);
		ft_printf("expand flag %i\n", aux->flag_expand);
		while (aux->arr_cmd_input[i])
		{
			ft_printf("matrix: :%s:\n", aux->arr_cmd_input[i]);
			i++;
		}
		i = 0;
		aux = aux->next;
	}
}

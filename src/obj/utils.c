/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprado <aprado@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:30:13 by aprado            #+#    #+#             */
/*   Updated: 2024/05/21 14:31:55 by aprado           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_there_var(char *s)
{
	int	i;
	int	onequote;
	int	check;

	i = 0;
	onequote = 0;
	check = 0;
	while (s[i])
	{
		if (s[i] == 39)
			onequote++;
		else if (s[i] == '$')
		{
			if ((onequote % 2) == 1)
			{
				if (s[i + 1] && ft_isalnum(s[i + 1]))
					check = 0;
			}
			else if (s[i + 1] && ft_isalnum(s[i + 1]))
				check = 1;
		}
		i++;
	}
	if (check)
		return (1);
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
	if (!len)
		return (NULL);
	env = malloc(sizeof(char) * (len + 1));
	if (!env)
		return (NULL);
	env[len] = '\0';
	while (len != -1)
		env[--len] = s[--i];
	return (env);
}

void	change_env(t_token **node, char *env)
{
	t_token	*aux;
	int		i;

	aux = *node;
	i = 0;
	while (aux->arr_cmd_input[i])
	{
		if (is_there_var(aux->arr_cmd_input[i]))
				break ;
		i++;
	}
	ft_printf("string to change -> :%s:\n", aux->arr_cmd_input[i]);
	ft_printf("env expanded -> :%s:\n", env);
}

void	get_env(t_token **node)
{
	//ja estou no node que eu preciso expandir...
	t_varenv	*env_node;
	t_token		*aux;

	env_node = (*node)->envs_lst;
	aux = *node;
	while (env_node)
	{
		if (!ft_strncmp(env_node->key, aux->env, ft_strlen(aux->env)))
		{
			change_env(node, env_node->var);
			//ft_printf("env key :%s:\n", env_node->key);
			//ft_printf("env value :%s:\n", env_node->var);
		}
		env_node = env_node->next;
	}
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
		//if (aux->flag_expand)
		//	get_env(&aux);
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

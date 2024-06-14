/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:30:13 by aprado            #+#    #+#             */
/*   Updated: 2024/06/14 16:31:17 by jbergfel         ###   ########.fr       */
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

/*
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
*/

void	fix_matrix(t_token **head)
{
	t_token	*aux;
	int		i;

	i = 0;
	aux = *head;
	while (aux)
	{
		while (aux->arr[i])
		{
			replace_char(aux->arr[i], '\v', ' ');
			replace_char(aux->arr[i], '\t', '|');
			i++;
		}
		i = 0;
		aux = aux->next;
	}
}

/*
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
}*/

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = -1;
	while (s1[++i] || s2[i])
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	copy_char_pointer(char ***dest, char **src)
{
	int i;

	i = -1;
	while (src[++i])
		(*dest)[i] = ft_strdup(src[i]);
	(*dest)[i] = NULL;
}

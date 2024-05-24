/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_func.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:09:39 by aprado            #+#    #+#             */
/*   Updated: 2024/05/24 12:55:40 by aprado           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	prepare_nodes(t_token **head)
{
	fix_matrix(head);
	print_list(head);
}

/*
//usar a *ft_substr(string base, onde comecar a copiar a string base, quantos caracteres voce quer copiar)
void	expand_var_aux(char **s, char *env_name, int i, t_varenv *envs)
{
	t_varenv	*aux;
	char		*value;
	//char		*temp;
	int			env_len;
	int			s_len;

	//(void)i; //esta na posicao $ da string
	//(void)s;
	aux = envs;
	env_len = ft_strlen(env_name);
	s_len = ft_strlen((*s));
	if (!env_name)
		return ;
	ft_printf("OPPAAA -> %i\n", env_len);
	ft_printf("OPPAAA -> %i\n", s_len);
	ft_printf("OPPAAA -> %i\n", i);
	while (aux)
	{
		if (!ft_strncmp(env_name, aux->key, ft_strlen(aux->key)))
		{
			value = ft_strdup(aux->var);
			//ft_printf("void s %s\n", s);
			//ft_printf("VAR NAME :%s:\n", aux->key);
			//ft_printf("VAR VALUE :%s:\n", value);
		}
		aux = aux->next;
	}
	if (i == 0 && ((env_len + 1) == s_len))
	{
		//temp = s;
		*s = value;
		//free(temp);
	}
}

void	expand_var(char **s, t_varenv *envs)
{
	//t_varenv	*aux;
	char		*aux;
	char		*env_name;
	int			i;

	i = 0;
	aux = *s;
	//aux = envs;
	while (aux[i])
	{
		if (aux[i] == '$')
		{
			env_name = get_env_name(aux + i, 1);
			expand_var_aux(s, env_name, i, envs);
			ft_printf("EXPAND VAR :%s:\n", env_name);
			//if (env_name)
			//	free(env_name);
		}
		i++;
	}
}
*/

void	create_node(char *s, t_token **head, char ***paths, t_varenv *envs)
{
	t_token	*new;
	t_token	*current;

	new = malloc(sizeof(t_token));
	if(!new)
		return (ft_putstr_fd("Error\n", 2));
	//expand_var(&s, envs);
	//fazer funcao para expandir a env
	//vou implementar isso na main mesmo.
	new->cmd_input = s;
	//ft_printf("OPAAA :%s:\n", s);
	//ft_printf("OPAAA :%i:\n", ft_strlen(s));
	new->arr_cmd_input = ft_split(s, ' ');
	new->cmd_name = divide_command_input(s);
	new->real_path = get_real_path(paths, new->cmd_name);
	new->envs_lst = envs;
	new->flag_expand = is_there_var(s);
	new->env = get_env_name(s, new->flag_expand);
	new->next = NULL;
	if (!(*head))
	{
		(*head) = new;
		return ;
	}
	current = (*head);
	while (current->next)
		current = current->next;
	current->next = new;
}


//t_token	create_list(char *usr_input, char **envp, t_varenv *envs, char **splited_input)
t_token	create_list(char *usr_input, char **envp, t_varenv *envs)
{
	t_token	*head;
	char	**splited;
	char	**paths;
	char	*env_path;
	int		i;

	//(void)splited_input;
	i = 0;
	head = NULL;
	splited = ft_split(usr_input, '|');
	env_path = find_env_path(envp);
	paths = ft_split((env_path + 5), ':');
	while (splited[i])
	{
		replace_char(splited[i], '\t', '|');
		create_node(splited[i], &head, &paths, envs);
		replace_char(splited[i], '\v', ' ');
		i++;
	}
	//ft_printf("TAM :%s:\n", head->cmd_input);
	//ft_printf("TAM :%i:\n", ft_strlen(head->cmd_input));
	prepare_nodes(&head);
	//colocar a fix_matrix dentro da prepare nodes!
	//fix_matrix(&head);
	//print_list(&head);
	//to_free_token(&head);
	//free_splits(splited);
	//free_splits(paths);
	return (*head);
}

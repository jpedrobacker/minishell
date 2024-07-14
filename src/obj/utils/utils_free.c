/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 16:00:53 by aprado            #+#    #+#             */
/*   Updated: 2024/07/14 11:13:28 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	to_free_varenv(t_varenv **lst_env)
{
	t_varenv	*begin;
	t_varenv	*temp;

	begin = (*(lst_env));
	free(begin->key);
	temp = begin->next;
	free(begin);
	begin = temp;
	while (begin)
	{
		temp = begin->next;
		free(begin->key);
		free(begin);
		begin = NULL;
		begin = temp;
	}
	*lst_env = NULL;
}

void	free_splits(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
	{
		if (!split[i])
			return ;
		free(split[i]);
		i++;
	}
	free(split);
}

void	envs_free(t_varenv **head)
{
	t_varenv	*aux;
	t_varenv	*temp;

	aux = (*head);
	while (aux)
	{
		temp = aux;
		free(aux->key);
		free(aux->var);
		aux->key = NULL;
		aux->var = NULL;
		aux = aux->next;
		free(temp);
	}
}

void	free_all(t_main *bag)
{
	free(bag->new_input);
	free(bag->dup_usr_input);
	free_splits(bag->splited_input);
	free_splits(bag->splited_pipe);
	free_splits(bag->paths);
	bag->new_input = NULL;
	bag->dup_usr_input = NULL;
	bag->splited_input = NULL;
	bag->splited_pipe = NULL;
	bag->paths = NULL;
}

void	token_free(t_token **head)
{
	t_token		*aux;
	t_token		*temp;

	aux = (*head);
	if (!aux)
		return ;
	temp = NULL;
	while (aux)
	{
		free_splits(aux->arr);
		free_splits(aux->args);
		free(aux->real_path);
		free(aux->cmd);
		aux->cmd = NULL;
		aux->arr = NULL;
		aux->args = NULL;
		aux->real_path = NULL;
		aux = aux->next;
	}
	while (*head)
	{
		temp = (*head);
		(*head) = (*head)->next;
		free(temp);
	}
}

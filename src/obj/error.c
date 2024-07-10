/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 13:58:43 by jbergfel          #+#    #+#             */
/*   Updated: 2024/07/09 10:37:00 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	*errors_mini(int type_err, char *param)
{
	if (type_err == QUOTE)
		ft_putstr_fd("QUOTE error msg: ", 2);
	else if (type_err == NDIR)
		ft_putstr_fd("NDIR error msg: ", 2);
	else if (type_err == NPERM)
		ft_putstr_fd("NPERM error msg: ", 2);
	else if (type_err == NCMD)
		ft_putstr_fd("NCMD error msg: ", 2);
	else if (type_err == DUPERR)
		ft_putstr_fd("DUPERR error msg: ", 2);
	else if (type_err == FORKERR)
		ft_putstr_fd("FORKERR error msg: ", 2);
	else if (type_err == PIPERR)
		ft_putstr_fd("PIPERR error msg: ", 2);
	else if (type_err == PIPENDERR)
		ft_putstr_fd("PIPENDERR error msg: ", 2);
	else if (type_err == MEM)
		ft_putstr_fd("MEM error msg: ", 2);
	else if (type_err == IS_DIR)
		ft_putstr_fd("IS_DIR error msg: ", 2);
	else if (type_err == NO_DIR)
		ft_putstr_fd("NO_DIR error msg: ", 2);
	else if (type_err == ARGS)
		ft_putstr_fd("Too many arguments: ", 2);
	ft_putendl_fd(param, 2);
	return (NULL);
}

/*
void	to_free_varenv(t_varenv **lst_env)
{
	t_varenv	*begin;
	t_varenv	*temp;

	begin = lst_env;
	free(begin->key);
	temp = begin->next;
	free(begin);
	begin = temp;
	while (begin)
	{
		temp = begin->next;
		if (ft_strcmp("?", begin->key) == 0)
			free(begin->var);
		begin->var = NULL;
		free(begin->key);
		begin->key = NULL;
		free(begin);
		begin = NULL;
		begin = temp;
	}
	lst_env = NULL;
}

//FUNCAO NAO USADA.....
void	to_free_token(t_token **token)
{
	t_token	*begin;
	t_token	*temp;

	begin = (*(token));
	free_splits(begin->arr_cmd_input);
	free(begin->cmd_name);
	free(begin->cmd_input);
	free(begin->env);
	temp = begin->next;
	free(begin);
	begin = temp;
	while (begin != NULL)
	{
		temp = begin->next;
		free_splits(begin->arr_cmd_input);
		free(begin->cmd_name);
		free(begin->cmd_input);
		free(begin->env);
		free(begin);
		begin = NULL;
		begin = temp;
	}
	*token = NULL;
}

void	free_splits(char **split)
{
	int	i;

	i = 0;
	if (split[i] != NULL)
	{
		while (split[i])
		{
			free(split[i]);
			i++;
		}
	}
	//split = NULL;
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
		//free(aux->var); o valor nao e dupado.
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
//	token_free(&bag->cmds);
//	envs_free(&bag->envs);
//	to_free_varenv(bag->envs);
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
	while (aux)
	{
		temp = aux;
		free_splits(aux->arr);
		free(aux->real_path);
		aux->arr = NULL;
		aux->real_path = NULL;
		aux = aux->next;
		free(temp);
	}
}
*/

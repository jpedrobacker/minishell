/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 13:58:43 by jbergfel          #+#    #+#             */
/*   Updated: 2024/05/28 13:39:47 by jbergfel         ###   ########.fr       */
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
		ft_printf("key free: %s\n", begin->key);
		ft_printf("var : %s\n", begin->var);
		free(begin->key);
		ft_printf("pointer free: %p\n", begin);
		free(begin);
		ft_printf("DDDDDDDDDDDDDDDDDDDDDDD\n");
		begin = NULL;
		begin = temp;
	}
	*lst_env = NULL;
}

void	to_free_token(t_token **token)
{
	t_token	*begin;
	t_token	*temp;
	//to free (cmd input, divide cmd input, get env name)
	begin = (*(token));
	while (begin != NULL)
	{
		temp = begin->next;
		free_splits(begin->arr_cmd_input);
		free(begin->cmd_name);
		free(begin->cmd_input);
		free(begin->env);
		free(begin);
		token = NULL;
		begin = temp;
	}
	begin = NULL;
}

void	free_splits(char **split)
{
	int	i;

	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
}

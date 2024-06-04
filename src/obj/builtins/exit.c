/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:39:02 by jbergfel          #+#    #+#             */
/*   Updated: 2024/06/04 11:19:23 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
void	split_free(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
	matrix = NULL;
}

void	teste(t_token **token)
{
	t_token *aux;

	aux = (*token);
	if (aux)
	{
		split_free(aux->arr_cmd_input);
		aux->arr_cmd_input = NULL;
		aux->cmd_input = NULL;
		free(aux->cmd_name);
		aux->cmd_name = NULL;
		free(aux->real_path);
		aux->real_path = NULL;
		free(aux->env);
		aux->env = NULL;
	}
	//free(token);
}
*/

void	built_exit(t_main *main)
{
	//extern int	g_status;
	//fazer exit em caso de ser chamado sem ser pelo comando exit no prompt
	//to_free_token(&token);
	//teste(&token);
	(void) main;
	exit(EXIT_SUCCESS);
}

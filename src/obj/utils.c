/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprado <aprado@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:30:13 by aprado            #+#    #+#             */
/*   Updated: 2024/05/06 14:32:06 by aprado           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_list(t_token **head)
{
	t_token	*aux;

	aux = *head;
	while (aux)
	{
		ft_printf("-------------------------------\n");
		ft_printf("command input :%s:\n", aux->cmd_input);
		ft_printf("comand :%s:\n", aux->cmd_name);
		ft_printf("path :%s:\n", aux->real_path);
		aux = aux->next;
	}
}

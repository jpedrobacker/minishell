/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprado <aprado@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:30:13 by aprado            #+#    #+#             */
/*   Updated: 2024/04/29 15:31:00 by aprado           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_list(t_token **head)
{
	t_token	*aux;

	aux = *head;
	while (aux)
	{
		ft_printf("\n");
		ft_printf("command input :%s:\n", aux->command_input);
		ft_printf("comand :%s:\n", aux->command);
		ft_printf("path :%s:\n", aux->real_path);
		aux = aux->next;
	}
}

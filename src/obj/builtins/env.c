/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:38:53 by jbergfel          #+#    #+#             */
/*   Updated: 2024/05/12 12:20:17 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	built_env(t_varenv **envp)
{
	t_varenv	*aux;

	aux = *envp;
	ft_printf("--------------------\n");
	while (aux)
	{
		ft_printf("key: %s\n", aux->key);
		ft_printf("var: %s\n", aux->var);
		aux = aux->next;
	}
	ft_printf("--------------------\n");
}

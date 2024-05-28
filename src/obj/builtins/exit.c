/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:39:02 by jbergfel          #+#    #+#             */
/*   Updated: 2024/05/28 13:33:16 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	built_exit(t_varenv *env, t_token *token)
{
	//extern int	g_status;
	//fazer exit em caso de ser chamado sem ser pelo comando exit no prompt
	to_free_token(&token);
	to_free_varenv(&env);
	exit(EXIT_SUCCESS);
}

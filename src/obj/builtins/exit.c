/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:39:02 by jbergfel          #+#    #+#             */
/*   Updated: 2024/07/12 15:58:46 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ctrl_d_exit(t_main *main)
{
	free_all(main);
	envs_free(&main->envs);
	token_free(&main->cmds);
	ft_putendl_fd("exit", STDOUT_FILENO);
	exit(EXIT_SUCCESS);
}

void	non_numeric_exit(t_main *main)
{
	free_all(main);
	envs_free(&main->envs);
	token_free(&main->cmds);
	ft_putstr_fd("exit\nnumeric argument required\n", STDOUT_FILENO);
	exit(2);
}

void	many_args_exit(t_main *main)
{
	free_all(main);
	envs_free(&main->envs);
	token_free(&main->cmds);
	ft_putstr_fd("exit\ntoo many arguments\n", STDOUT_FILENO);
	exit(1);
}

void	built_exit(t_main *main, t_token *token)
{
	int	temp;
	int	i;

	if (!token)
		ctrl_d_exit(main);
	if (count_cmds(token->args) > 2)
		many_args_exit(main);
	if (count_cmds(token->args) == 2)
	{
		i = 0;
		while (token->args[1][i])
		{
			if (ft_isdigit(token->args[1][i]) == 0)
				non_numeric_exit(main);
			i++;
		}
		temp = ft_atoi(token->args[1]);
	}
	free_all(main);
	envs_free(&main->envs);
	token_free(&main->cmds);
	ft_putendl_fd("exit", STDOUT_FILENO);
	if (temp)
		exit(temp);
	exit(EXIT_SUCCESS);
}

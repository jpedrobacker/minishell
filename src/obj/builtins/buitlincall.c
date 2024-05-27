/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buitlincall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 13:00:52 by jbergfel          #+#    #+#             */
/*   Updated: 2024/05/27 15:07:41 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	call_cmd(t_token *token, t_varenv *env)
{
	if (ft_strncmp("cd", token->cmd_name, ft_strlen(token->cmd_name)) == 0)
		built_cd(&token);
	if (ft_strncmp("echo", token->cmd_name, ft_strlen(token->cmd_name)) == 0)
		built_echo(&token, echo_flag(token->arr_cmd_input));
	if (ft_strncmp("env", token->cmd_name, ft_strlen(token->cmd_name)) == 0)
		built_env(&env, &token);
	if (ft_strncmp("exit", token->cmd_name, ft_strlen(token->cmd_name)) == 0)
		built_exit(env, token);
	if (ft_strncmp("pwd", token->cmd_name, ft_strlen(token->cmd_name)) == 0)
		built_pwd();
	if (ft_strncmp("export", token->cmd_name, ft_strlen(token->cmd_name)) == 0)
		built_export(&env, &token);
	if (ft_strncmp("unset", token->cmd_name, ft_strlen(token->cmd_name)) == 0)
		built_unset(&env, &token);
	if (ft_strncmp("clear", token->cmd_name, ft_strlen(token->cmd_name)) == 0)
		built_clear();
}

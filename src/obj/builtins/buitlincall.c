/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buitlincall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 13:00:52 by jbergfel          #+#    #+#             */
/*   Updated: 2024/06/03 16:24:06 by aprado           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	call_cmd(t_token *token, t_varenv *env)
{
	if (ft_strncmp("cd", token->arr[0], ft_strlen(token->arr[0])) == 0)
		built_cd(&token);
	if (ft_strncmp("echo", token->arr[0], ft_strlen(token->arr[0])) == 0)
		built_echo(&token, echo_flag(token->arr));
	if (ft_strncmp("env", token->arr[0], ft_strlen(token->arr[0])) == 0)
		built_env(&env, &token);
	if (ft_strncmp("exit", token->arr[0], ft_strlen(token->arr[0])) == 0)
		built_exit(env, token);
	if (ft_strncmp("pwd", token->arr[0], ft_strlen(token->arr[0])) == 0)
		built_pwd();
	if (ft_strncmp("export", token->arr[0], ft_strlen(token->arr[0])) == 0)
		built_export(&env, &token);
	if (ft_strncmp("unset", token->arr[0], ft_strlen(token->arr[0])) == 0)
		built_unset(&env, &token);
	if (ft_strncmp("clear", token->arr[0], ft_strlen(token->arr[0])) == 0)
		built_clear();
}

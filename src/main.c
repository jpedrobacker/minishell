/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:29:24 by jbergfel          #+#    #+#             */
/*   Updated: 2024/05/18 10:43:37 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	expand_env(t_token *head)
{
	t_token	*aux;
	t_varenv *temp;
	char	*old;

	aux = head;
	temp = aux->envs_lst;
	if (aux->flag_expand)
	{
		while (temp)
		{
			if (!ft_strncmp(temp->key, aux->env, ft_strlen(temp->key)))
				break ;
			temp = temp->next;
		}
		if (aux->arr_cmd_input[1])
		{
			old = aux->arr_cmd_input[1];
			aux->arr_cmd_input[1] = ft_strdup(temp->var);
			free(old);
		}
	}
}

int	main(int ac, char **av, char **envp)
{
	char	*usr_input;
	char	*minshell;
	char	curdir[PATH_MAX];
	t_varenv	envp_lst;
	t_token		token;

	(void) ac;
	(void) av;
	signal(SIGQUIT, SIG_IGN);
	envp_lst = make_envp_list(envp);
	while (1)
	{
		minshell = ft_strjoin(getcwd(curdir, sizeof(curdir)), "$ ");
		minshell = ft_strnstr(minshell, "home", ft_strlen(minshell));
		usr_input = readline(minshell);
		if (!usr_input)
		{
			ft_printf("Apertei cntrlD");
			exit(EXIT_SUCCESS);
		}
		//ft_printf("antes: %s\n", usr_input);
		change_input(usr_input);
		//ft_printf("depois: %s\n", usr_input);
		token = create_list(usr_input, envp, &envp_lst);
		//expand_env(&token);
		call_cmd(&token, &envp_lst);
		add_history(usr_input);
		free(usr_input);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:07:29 by aprado            #+#    #+#             */
/*   Updated: 2024/07/01 22:21:42 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	our_builtins(char *s)
{
	if (!s)
		return (0);
	if (!ft_strncmp("cd", s, ft_strlen(s)))
		return (1);
	else if (!ft_strncmp("echo", s, ft_strlen(s)))
		return (1);
	else if (!ft_strncmp("env", s, ft_strlen(s)))
		return (1);
	else if (!ft_strncmp("exit", s, ft_strlen(s)))
		return (1);
	else if (!ft_strncmp("pwd", s, ft_strlen(s)))
		return (1);
	else if (!ft_strncmp("export", s, ft_strlen(s)))
		return (1);
	else if (!ft_strncmp("unset", s, ft_strlen(s)))
		return (1);
	else if (!ft_strncmp("clear", s, ft_strlen(s)))
		return (1);
	return (0);
}

char	*get_real_path(char ***all_paths, char *command)
{
	char	*test;
	char	*test_command;
	char	**paths;
	int		i;

	i = 0;
	if (!command)
		return (NULL);
	if (our_builtins(command))
		return (NULL);
	paths = (*all_paths);
	if (!paths)
		return (NULL);
	test_command = ft_strjoin("/", command);
	while (paths[i])
	{
		test = ft_strjoin(paths[i], test_command);
		if (!test)
			return (NULL);
		if (access(test, F_OK & X_OK) == 0)
			return (free(test_command), test);
		else
			free(test);
		i++;
	}
	free(test_command);
	return (NULL);
}

char	*divide_command_input(char *s)
{
	int		i;
	int		j;
	int		len;
	int		beginning;
	char	*cmd;

	i = 0;
	j = 0;
	len = 0;
	while (s[i] && s[i] == ' ')
		i++;
	beginning = i;
	while (s[i] && s[i] != ' ')
	{
		i++;
		len++;
	}
	cmd = malloc(sizeof(char) * (len + 1));
	if (!cmd)
		return (NULL);
	while (beginning < i)
		cmd[j++] = s[beginning++];
	cmd[len] = '\0';
	return (cmd);
}

char	*find_env_path(t_varenv *envp)
{
	char		*env_path;
	t_varenv	*aux;

	env_path = NULL;
	aux = envp;
	while (aux)
	{
		if (ft_strcmp(aux->key, "PATH") == 0)
		{
			env_path = aux->var;
			break ;
		}
		aux = aux->next;
	}
	return (env_path);
}

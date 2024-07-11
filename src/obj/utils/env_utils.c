/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:26:41 by jbergfel          #+#    #+#             */
/*   Updated: 2024/07/11 10:40:51 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*get_env_key(char *envp, char c)
{
	int		len;
	int		i;
	char	*result;

	len = 0;
	while (envp[len] != '\0' && envp[len] != c)
		len++;
	result = (char *)malloc(len + 1);
	if (!result)
		return (NULL);
	i = 0;
	while (i < len)
	{
		result[i] = envp[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

char	*get_env_name(char *s, int flag)
{
	char	*env;
	int		i;
	int		len;

	if (!flag)
		return (NULL);
	i = 0;
	len = 0;
	while (s[i] && s[i] != '$')
		i++;
	i++;
	while (s[i] && ft_isalnum(s[i]))
	{
		i++;
		len++;
	}
	if (!len)
		return (NULL);
	env = malloc(sizeof(char) * (len + 1));
	if (!env)
		return (NULL);
	env[len] = '\0';
	while (len != -1)
		env[--len] = s[--i];
	return (env);
}

int	find_char(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (0);
		i++;
	}
	return (1);
}

static char	*ft_env_join(char *key, char *var)
{
	char	*nv_one;
	char	*nv_two;

	nv_one = ft_strjoin(key, "=");
	nv_two = ft_strjoin(nv_one, var);
	free(nv_one);
	return (nv_two);
}

char	**linked_to_env(t_varenv *env)
{
	char	**new_env;
	int		linked_len;
	int		i;

	linked_len = env_lst_size(env);
	i = 0;
	new_env = malloc(sizeof(char *) * (linked_len + 1));
	while (env)
	{
		new_env[i] = ft_env_join(env->key, env->var);
		i++;
		env = env->next;
	}
	new_env[i] = NULL;
	return (new_env);
}

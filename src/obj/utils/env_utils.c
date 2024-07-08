/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:26:41 by jbergfel          #+#    #+#             */
/*   Updated: 2024/07/07 19:24:24 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	env_lst_size(t_varenv *env)
{
	int			i;
	t_varenv	*temp;

	temp = env;
	i = 0;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}

char	*find_var_key(t_varenv *env, char *key_to_find)
{
	t_varenv	*aux;

	aux = env;
	while (aux != NULL)
	{
		if (ft_strcmp(aux->key, key_to_find) == 0)
			return (aux->var);
		aux = aux->next;
	}
	return ("");
}

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
/* Funções que fazem a mesma coisa!? */
char	*get_env_name(char *s, int flag, int s_len)
{
	char	*env;
	int		i;
	int		len;

	(void)s_len;
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

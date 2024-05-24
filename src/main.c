/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:29:24 by jbergfel          #+#    #+#             */
/*   Updated: 2024/05/24 15:27:43 by aprado           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
//usar a *ft_substr(string base, onde comecar a copiar a string base, quantos caracteres voce quer copiar)
void	expand_var_aux(char *s, char *env_name, int i, t_varenv *envs)
{
	t_varenv	*aux;
	//char		*value;
	//char		*temp;
	//int			env_len;
	//int			s_len;

	(void)i; //esta na posicao $ da string
	//(void)s;
	aux = envs;
	//env_len = ft_strlen(env_name);
	//s_len = ft_strlen((*s));
	if (!env_name)
		return ;
	//ft_printf("OPPAAA -> %i\n", env_len);
	//ft_printf("OPPAAA -> %i\n", s_len);
	//ft_printf("OPPAAA -> %i\n", i);
	while (aux)
	{
		if (!ft_strncmp(env_name, aux->key, ft_strlen(aux->key)))
		{
			//value = ft_strdup(aux->var);
			ft_printf("void s %s\n", s);
			ft_printf("VAR NAME :%s:\n", aux->key);
			ft_printf("VAR VALUE :%s:\n", aux->var);
		}
		aux = aux->next;
	}
	
	if (i == 0 && ((env_len + 1) == s_len))
	{
		//temp = s;
		*s = value;
		//free(temp);
	}
	
}


void	expand_var(char *s, t_varenv *envs)
{
	//t_varenv	*aux;
	char		*env_name;
	int			i;

	i = 0;
	//aux = envs;
	while (s[i])
	{
		if (s[i] == '$')
		{
			env_name = get_env_name(s + i, 1);
			expand_var_aux(s, env_name, i, envs);
			ft_printf("EXPAND VAR :%s:\n", env_name);
			//if (env_name)
			//	free(env_name);
		}
		i++;
	}
}
*/

int	check_char(char *s, int i, int s_len, char *in)
{
	int	x;

	x = 0;
	if ((i + 1) < s_len)
	{
		if (s[i] == '$' && ft_isalpha(s[i + 1]))
			return (0);
	}
	while (in[x])
	{
		if (s[i] == in[x])
			return (1);
		x++;
	}
	return (0);
}

//echo "OLA 42 $USER rio '$HOME' $ MAIL"
//echo '$ HOME'
//'a'
int	line_count(char *s, char *in, int s_len)
{
	int	i;
	int	lines;
	int	word;

	i = 0;
	lines = 0;
	word = 0;
	while (s[i])
	{
		if (check_char(s, i, s_len, in))
		{
			if (word != 0)
			{
				lines++;
				word = 0;
			}
			lines++;
		}
		else
			word++;
		i++;
	}
	if (word)
		lines++;
	return (lines);
}

//echo '$HOME'
//
//usar a *ft_substr(string base, onde comecar a copiar a string base, quantos caracteres voce quer copiar)
char	**split_in_tokens(char *s, char *in)
{
	int		i;
	int		s_len;
	int		lines;
	//int		line_len;
	char	**new;

	i = 0;
	//line_len = 0;
	s_len = ft_strlen(s);
	lines = line_count(s, in, s_len);
	ft_printf("lines -> :%i:\n", lines);
	new = malloc(sizeof(char *) * (lines + 1));
	if (!new)
		return (NULL);
	new[lines] = NULL;
	int t = 0;
	int j = 0;
	while (s[i])
	{
		if (!check_char(s, i, s_len, in))
			t++;
		else
		{
			if (t != 0)
			{
				new[j] = ft_substr(s, (i - t), t); //implementar free caso de merda.
				j++;
				t = 0;
				i--;
			}
			else
			{
				new[j] = ft_substr(s, i, 1);
				j++;
			}
		}
		i++;
	}
	return (new);
}

int	main(int ac, char **av, char **envp)
{
	char	*usr_input;
	char	*minshell;
	char	curdir[PATH_MAX];
	char	**splited_input;
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
		splited_input = split_in_tokens(usr_input, "\"'$ \v");
		//expand_var(usr_input, &envp_lst);

		/*
		int i = 0;
		while (splited_input[i])
		{
			ft_printf("depois :%s:\n", splited_input[i]);
			i++;
		}
		ft_printf("depois :%s:\n", splited_input[i]);
		*/

		token = create_list(usr_input, envp, &envp_lst);
		call_cmd(&token, &envp_lst);
		add_history(usr_input);
		free(usr_input);
	}
	return (0);
}

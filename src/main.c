/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:29:24 by jbergfel          #+#    #+#             */
/*   Updated: 2024/05/03 14:57:17 by aprado           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//cat "cat | cat"

int	change_pipe(char *s, int start, int end)
{
	int	change;

	change = 0;
	while (start <= end)
	{
		if (s[start] == '|')
		{
			change++;
			s[start] = '\t';
		}
		start++;
	}
	if (change == 0)
		return (0);
	return (1);
}

// " 34
// ' 39

void	change_input(char *s)
{
	int		i;
	int		start;
	int		end;

	i = 0;
	start = 0;
	end = 0;
	while (s[i])
	{
		if (s[i] == 34)
		{
			start = i;
			i++;
			while (s[i] && s[i] != 34)
				i++;
			end = i;
			break ;
		}
		i++;
	}
	if (s[end] == 34)
		change_pipe(s, start, end);
}

int	main(int ac, char **av, char **envp)
{
	char	*usr_input;
	(void) ac;
	(void) av;
	//(void)envp;

	while (1)
	{
		usr_input = readline("minishell: ");
		if (!usr_input)
		{
			ft_printf("Apertei cntrlD");
			exit(EXIT_SUCCESS);
		}
		/*
		if (ft_strncmp(usr_input, "cd", ft_strlen(usr_input)) == 0)
			cd("");
		*/
		//criar uma func que troca o '|' por '\t'
		ft_printf("main :%s:\n", usr_input);
		change_input(usr_input);
		ft_printf("main :%s:\n", usr_input);
		//change_input(&av[1]);
		create_list(usr_input, envp);
		free(usr_input);
	}
	return (1);
}

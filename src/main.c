/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:29:24 by jbergfel          #+#    #+#             */
/*   Updated: 2024/05/06 14:11:53 by aprado           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
		change_input(usr_input);
		create_list(usr_input, envp);
		free(usr_input);
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_redirects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprado <aprado@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:02:14 by aprado            #+#    #+#             */
/*   Updated: 2024/07/01 17:35:25 by aprado           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//echo << a hahah | cat kkkk
//cmd1 heredoc heredoc_arg cmd1_arg | cmd2 cmd2_arg
int	deal_redirects(t_main *bag)
{
	//int		i;
	//char	**s;

	//i = 0;
	if (!bag->dup_usr_input)
		return (0);
	bag->splited_input = split_in_tokens(bag->dup_usr_input, "\"' $\v\t\n\a<>|", bag->envs);
	//s = bag->splited_input;

	//Need to implement this func.
	/*
	while (bag->splited_input[i])
	{
		if (ft_strnstr(bag->splited_input[i], "<<", ft_strlen(bag->splited_input[i])))
		{
			while (bag->splited_input[i])
			{
				i++;
			}
		}
		if (bag->splited_input[i][0] == '<' || bag->splited_input[i][0] == '>')
		{

		}
		i++;
	}
	*/
	//PRINT DA SPLIT IN TOKENS!!!
	int i = 0;
	char **s = bag->splited_input;
	while (s[i])
	{
		ft_printf("splited :%s: \n", s[i]);
		i++;
	}
	return (1);
}

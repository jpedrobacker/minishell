/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:25:23 by jbergfel          #+#    #+#             */
/*   Updated: 2024/04/27 18:26:40 by aprado           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/ft_printf.h"
# include "../lib/libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct	s_token
{
	int			fd_in;
	int			fd_out;
	char		*real_path;
	char		*command;
	char		**env_path;
	char		**arr_command;
	struct s_token	*next;
}			t_token;

void test_print(char *src);

#endif

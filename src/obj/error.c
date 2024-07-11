/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 13:58:43 by jbergfel          #+#    #+#             */
/*   Updated: 2024/07/11 10:47:34 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	*errors_mini(int type_err, char *param)
{
	if (type_err == QUOTE)
		ft_putstr_fd("QUOTE error msg: ", 2);
	else if (type_err == NDIR)
		ft_putstr_fd("NDIR error msg: ", 2);
	else if (type_err == NPERM)
		ft_putstr_fd("NPERM error msg: ", 2);
	else if (type_err == NCMD)
		ft_putstr_fd("NCMD error msg: ", 2);
	else if (type_err == DUPERR)
		ft_putstr_fd("DUPERR error msg: ", 2);
	else if (type_err == FORKERR)
		ft_putstr_fd("FORKERR error msg: ", 2);
	else if (type_err == PIPERR)
		ft_putstr_fd("PIPERR error msg: ", 2);
	else if (type_err == IS_DIR)
		ft_putstr_fd("IS_DIR error msg: ", 2);
	else if (type_err == NO_DIR)
		ft_putstr_fd("NO_DIR error msg: ", 2);
	else if (type_err == ARGS)
		ft_putstr_fd("Too many arguments: ", 2);
	ft_putendl_fd(param, 2);
	return (NULL);
}

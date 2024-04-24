/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 14:29:27 by jbergfel          #+#    #+#             */
/*   Updated: 2023/11/07 16:07:53 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_str(char *s)
{
	int	i;

	if (!s)
		return (ft_printf_str("(null)"));
	i = 0;
	while (s[i] != '\0')
		write(1, &s[i++], 1);
	return (i);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_unsigned.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 09:39:00 by jbergfel          #+#    #+#             */
/*   Updated: 2023/11/07 16:07:57 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_unsigned(unsigned int n)
{
	int				l;
	unsigned int	nbr;

	nbr = n;
	l = 1;
	while (nbr > 9)
	{
		nbr /= 10;
		l++;
	}
	ft_putnbr(n);
	return (l);
}

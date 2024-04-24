/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_nbr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 14:29:16 by jbergfel          #+#    #+#             */
/*   Updated: 2023/11/07 16:07:43 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_nbr(long int n)
{
	long int	nbr;
	int			i;

	nbr = n;
	i = 1;
	if (n < 0)
	{
		nbr = -n;
		i++;
	}
	while (nbr > 9)
	{
		nbr /= 10;
		i++;
	}
	ft_putnbr(n);
	return (i);
}

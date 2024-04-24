/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 11:50:20 by jbergfel          #+#    #+#             */
/*   Updated: 2023/11/07 16:08:01 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	check_types(va_list args, const char format)
{
	int	i;

	i = 0;
	if (format == 'c')
		i += ft_printf_char(va_arg(args, int));
	else if (format == 's')
		i += ft_printf_str(va_arg(args, char *));
	else if (format == 'p')
		i += ft_printf_pointer(va_arg(args, unsigned long));
	else if (format == 'd' || format == 'i')
		i += ft_printf_nbr(va_arg(args, int));
	else if (format == 'u')
		i += ft_printf_unsigned(va_arg(args, unsigned int));
	else if (format == 'x' || format == 'X')
		i += ft_printf_hexadecimal(va_arg(args, unsigned int), format);
	else if (format == '%')
		i += ft_printf_percent();
	return (i);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		p;

	i = 0;
	p = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			p += check_types(args, format[i + 1]);
			i++;
		}
		else
			p += ft_printf_char(format[i]);
		i++;
	}
	va_end(args);
	return (p);
}

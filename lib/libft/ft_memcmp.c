/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 10:38:18 by jbergfel          #+#    #+#             */
/*   Updated: 2023/11/07 16:09:49 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *str1, const void *str2, size_t n)
{
	size_t	i;
	char	*istr1;
	char	*istr2;

	istr1 = (char *)str1;
	istr2 = (char *)str2;
	i = 0;
	while (i < n)
	{
		if (istr1[i] < istr2[i] || istr1[i] > istr2[i])
			return ((unsigned char)istr1[i] - (unsigned char)istr2[i]);
		i++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 10:38:24 by jbergfel          #+#    #+#             */
/*   Updated: 2023/11/07 16:09:56 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dest;
	unsigned char	*dsrc;

	if (!dst && !src)
		return (NULL);
	if (dst < src)
		return (ft_memcpy(dst, src, len));
	dest = (unsigned char *)dst;
	dsrc = (unsigned char *)src;
	while (len > 0)
	{
		dest[len - 1] = dsrc[len - 1];
		len--;
	}
	return (dst);
}

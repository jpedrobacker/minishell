/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 10:39:23 by jbergfel          #+#    #+#             */
/*   Updated: 2024/02/21 15:37:01 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *src, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*dst;

	dst = (char *)malloc(sizeof(*src) * (len + 1));
	if (!dst)
		return (NULL);
	i = 0;
	j = 0;
	while (src[i])
	{
		if (i >= start && j < len)
		{
			dst[j] = src[i];
			j++;
		}
		i++;
	}
	dst[j] = '\0';
	return (dst);
}

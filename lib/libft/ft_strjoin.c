/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 10:38:59 by jbergfel          #+#    #+#             */
/*   Updated: 2024/02/21 15:32:32 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		lenstr1;
	int		lenstr2;
	char	*str;

	i = 0;
	lenstr1 = ft_strlen(s1);
	lenstr2 = ft_strlen(s2);
	if (!s1)
		return (ft_strdup(""));
	if (!s1 && !s2)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (lenstr1 + lenstr2 + 1));
	if (!str)
		return (NULL);
	while (i < lenstr1 || i < lenstr2)
	{
		if (i < lenstr1)
			str[i] = s1[i];
		if (i < lenstr2)
			str[i + lenstr1] = s2[i];
		i++;
	}
	str[lenstr1 + lenstr2] = '\0';
	return (str);
}

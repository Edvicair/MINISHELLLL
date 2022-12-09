/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvicair <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 16:54:57 by edvicair          #+#    #+#             */
/*   Updated: 2021/01/11 13:34:05 by edvicair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (s2[0] == '\0')
		return ((char *)s1);
	if (len == 0)
		return (NULL);
	j = ft_strlen(s2);
	while (i <= (len - j) && s1[i])
	{
		if (ft_strncmp(&s1[i], s2, j) == 0)
			return ((char *)s1 + i);
		i++;
	}
	return (NULL);
}

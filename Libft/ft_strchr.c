/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvicair <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 16:52:44 by edvicair          #+#    #+#             */
/*   Updated: 2021/01/09 16:55:58 by edvicair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	*s_cpy;

	i = 0;
	s_cpy = (char *)s;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
		{
			s_cpy = ((char *)s + i);
			return (s_cpy);
		}
		i++;
	}
	if (c == '\0')
		return (&s_cpy[i]);
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvicair <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 16:40:12 by edvicair          #+#    #+#             */
/*   Updated: 2021/01/09 16:02:32 by edvicair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*s_cpy;
	unsigned char	*s_new;
	size_t			i;

	i = 0;
	s_cpy = (unsigned char *)s;
	s_new = NULL;
	while (i < n)
	{
		if (s_cpy[i] == (unsigned char)c && s_new == NULL)
		{
			s_new = ((unsigned char *)s + i);
			return ((void *)s_new);
		}
		i++;
	}
	return (NULL);
}

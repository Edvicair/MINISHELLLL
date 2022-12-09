/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvicair <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 16:53:09 by edvicair          #+#    #+#             */
/*   Updated: 2021/01/11 14:01:27 by edvicair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	int		last;
	char	*s_cpy;

	i = 0;
	last = -1;
	s_cpy = (char *)s;
	while (s[i])
	{
		if (s[i] == (char)c)
		{
			last = i;
			s_cpy = ((char *)s + last);
		}
		i++;
	}
	if (c == '\0')
		return (s_cpy + i);
	if (last == -1)
		s_cpy = NULL;
	return (s_cpy);
}

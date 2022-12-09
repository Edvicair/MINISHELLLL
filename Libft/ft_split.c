/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvicair <edvicair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 17:14:07 by edvicair          #+#    #+#             */
/*   Updated: 2022/11/12 15:26:46 by edvicair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	srch_end(const char *s, char c, size_t i)
{
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (i);
}

static size_t	srch_start(const char *s, char c, size_t i)
{
	while (s[i] == c)
		i++;
	return (i);
}

static char	**free_tab(char **ret, size_t line)
{
	size_t	x;

	x = 0;
	while (x < line)
	{
		free(ret[x]);
		x++;
	}
	free(ret);
	return (NULL);
}

static size_t	count_word(const char *s, char c)
{
	size_t	i;
	size_t	total;

	i = 0;
	total = 0;
	while (s[i])
	{
		i = srch_start(s, c, i);
		if (s[i])
		{
			i = srch_end(s, c, i);
			total++;
		}
	}
	return (total);
}

char	**ft_split(const char *s, char c)
{
	t_test	b;

	b.i = 0;
	b.start = 0;
	b.end = count_word(s, c);
	b.dest = (char **)malloc(sizeof(char *) * (b.end + 1));
	if (!b.dest)
		return (NULL);
	while (s[b.start] && b.end != 0)
	{
		b.start = srch_start(s, c, b.start);
		b.end = srch_end(s, c, b.start);
		if ((b.end - b.start) != 0)
		{
			b.dest[b.i] = (char *)malloc(sizeof(char) * (b.end - b.start) + 1);
			if (!b.dest[b.i])
				return (free_tab(b.dest, b.i));
			b.j = 0;
			while (b.start < b.end)
				b.dest[b.i][b.j++] = s[b.start++];
			b.dest[b.i++][b.j] = '\0';
		}
	}
	b.dest[b.i] = NULL;
	return (b.dest);
}

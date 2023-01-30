/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvicair <edvicair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 18:22:18 by motaouss          #+#    #+#             */
/*   Updated: 2023/01/30 12:33:23 by edvicair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count(char *str, char c)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	if (str[i] == '\0')
		return (x);
	i = count_bis(str, c, i, 1);
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			i = split_what(str, i, str[i]);
			while (str[i + 1] && str[i + 1] == c)
				i++;
			if (str[i] && str[i] == c)
				x++;
		}
		else if ((str[i] == c) && (str[i - 1] != c))
			x++;
	}
	i = count_bis(str, c, i, 0);
	if (str[i] != c)
		x++;
	return (x);
}

static char	*ft_substr_quote(char *s, int min, int max, char c)
{
	int		i;
	char	*s2;
	int		quote;

	if (c == '|')
		return (ft_substr_pipe(s, min, max));
	s2 = malloc(sizeof(char) * (strlen_quote(s, min, max)));
	if (!s2)
		return (NULL);
	quote = find_quote(s, min, max);
	if (quote)
		max--;
	i = 0;
	while (min < max)
	{
		while (s[min] == quote)
			min++;
		s2[i] = s[min];
		i++;
		min++;
	}
	s2[i] = '\0';
	return (s2);
}

static void	ft_freeze(int n, char **s)
{
	while (n >= 0)
	{
		free(s[n]);
		n--;
	}
}

static	void	boucle(char *str, char **s, char c)
{
	int	i;
	int	n;
	int	min;

	i = 0;
	n = -1;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		min = i;
		while (str[i] && str[i] != c)
		{
			if (str[i] == '\'' || str[i] == '"')
				i = split_what(str, i, str[i]);
			i++;
		}
		if (++n < count(str, c))
		{
			s[n] = ft_substr_quote(str, min, i, c);
			if (s[n] == NULL)
				ft_freeze(n, s);
		}
	}
}

char	**tokenizator(char *str, char c)
{
	char	**s;
	int		i;

	if (!str)
		return (NULL);
	s = malloc(sizeof(char *) * (count(str, c) + 1));
	if (s == NULL)
		return (0);
	i = count(str, c);
	s[i] = NULL;
	boucle(str, s, c);
	return (s);
}

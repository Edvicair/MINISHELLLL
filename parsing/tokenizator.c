/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvicair <edvicair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 18:22:18 by motaouss          #+#    #+#             */
/*   Updated: 2022/12/09 10:00:33 by edvicair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count(char *str)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)) 
		i++;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			i = split_quote(str, i, str[i]);
			while (str[i + 1] && ((str[i + 1] >= 9 && str[i + 1] <= 13) || str[i + 1] == 32))
				i++;
			if (str[i] && (((str[i] >= 9 && str[i] <= 13) || str[i] == 32)))
				x++;
		}
		else if (((str[i] >= 9 && str[i] <= 13) || str[i] == 32) && (str[i - 1] >= 33 && str[i - 1] <= 126))
			x++;
		i++;
	}
	if (str[i - 1] >= 33 && str[i - 1] <= 126)
		x++;
	return (x);
}

static char	*ft_substr_quote(char *s, int min, int max)
{
	int		i;
	char	*s2;
	int		quote;

	s2 = malloc(sizeof(char *) * (strlen_quote(s, min, max)));
	if (!s2)
		return (NULL);
	quote = find_quote(s, min, max);
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

static	void	boucle(char *str, char **s, t_msh *msh)
{
	int	i;
	int	n;
	int	min;
	bool red;

	i = 0;
	n = 0;
	min = 0;
	red = 0;
	while (str[i])
	{
		while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
			i++;
		min = i;
		while (str[i] && (((str[i] <= 9 && str[i] >= 13) || str[i] != 32) && str[i] != 10))
		{
			if ((str[i] == '\'' || str[i] == '"'))
				i = split_quote(str, i, str[i]);
			i++;
		}
		// if (str[min] == '<' || str[min] == '>')
		// {
		// 	printf("il rentre %d\n", min);
		// 	i = redi_less(msh, str, min);
		// 	printf("il sort %d\n", min);
		// }
		if (n < count(str))
		{
			s[n] = ft_substr_quote(str, min, i);
			if (s[n] == NULL)
				ft_freeze(n, s);
			n++;
		}
	}
}

char	**tokenizator(char *str, t_msh *msh)
{
	char **s;
	int i;

	if (!str)
		return (NULL);
	s = malloc(sizeof(char *) * (count(str) + 1));
	if (s == NULL)
		return (0);
	i = count(str);
	s[i] = NULL;
	boucle(str, s, msh);
	return (s);
}
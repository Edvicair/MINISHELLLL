/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvicair <edvicair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 17:24:55 by edvicair          #+#    #+#             */
/*   Updated: 2023/01/20 20:22:34 by edvicair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static unsigned int	ft_sign(int n)
{
	unsigned int	nb;

	if (n < 0)
		nb = -n;
	else
		nb = n;
	return (nb);
}

static unsigned int	ft_count(unsigned int nb)
{
	unsigned int	count;

	count = 0;
	if (nb == 0)
		return (2);
	while (nb != 0)
	{
		count++;
		nb /= 10;
	}
	return (count + 1);
}

char	*resident_evil(unsigned int count, char *res, unsigned int j,
						unsigned int nb)
{
	while (count > j)
	{
		res[--count] = (nb % 10) + '0';
		nb /= 10;
	}
	return (res);
}

char	*ft_itoa(int n)
{
	char			*res;
	int				i;
	unsigned int	nb;
	unsigned int	j;
	unsigned int	count;

	i = 0;
	j = 0;
	nb = ft_sign(n);
	count = ft_count(nb);
	if (n < 0)
		count++;
	if (n < 0)
		j = 1;
	else
		j = 0;
	res = (char *)malloc(sizeof(char) * count);
	if (!res)
		return (NULL);
	res[--count] = '\0';
	if (n == 0)
		res[0] = '0';
	if (n < 0)
		res[0] = '-';
	return (resident_evil(count, res, j, nb));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvicair <edvicair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 05:58:03 by edvicair          #+#    #+#             */
/*   Updated: 2023/01/30 12:33:28 by edvicair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			i = split_what(str, i, str[i]);
		if (!str[i])
			return (1);
		i++;
	}
	return (0);
}

void	freezer(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
}

int	count_bis(char *str, char c, int i, bool a)
{
	if (a == 1)
	{
		while (str[i] && str[i] == c)
			i++;
		return (i - 1);
	}
	else
	{
		if (c == ' ')
			return (i - 1);
		else
			return (i - 2);
	}
}

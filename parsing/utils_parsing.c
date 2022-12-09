/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motaouss <motaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 20:16:33 by motaouss          #+#    #+#             */
/*   Updated: 2022/11/29 01:25:27 by motaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	split_quote(char *str, int i, char quote)
{
	i++;
	while (str[i] != quote && str[i])
		i++;
	return(i);
}

int		is_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			i = split_quote(str, i, str[i]);
		if (!str[i])
			return (1);
		i++;
	}
	return (0);
}
/*
void	freezer(t_token *token)
{
	int i;

	i = 0;
	while (token->tok[i])
	{
		free(token->tok[i]);
		i++;
	}
}
*/
int	strlen_quote(char *str, int min, int max)
{
	int i;
	char	quote;

	i = min;
	while (str[i] != '\'' && str[i] != '"' && i < max)
		i++;
	if (i == max)
		return ((max - min) + 1);
	else
		quote = str[i];
	i = min;
	while (i < max)
	{
		if (str[i] == quote)
			min++;
		i++;
	}
	return ((max - min) + 1);
}

int	find_quote(char *str, int min , int max)
{
	while (min < max)
	{
		if (str[min] == '\'' || str[min] == '"')
			return (str[min]);
		min++;
	}
	return (0);
}
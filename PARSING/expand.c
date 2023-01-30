/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvicair <edvicair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 11:59:16 by motaouss          #+#    #+#             */
/*   Updated: 2023/01/30 12:42:39 by edvicair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*check_env_expand(t_msh *msh, char *str)
{
	int		i;
	t_env	*cpy;

	i = 0;
	cpy = msh->env;
	while (cpy)
	{
		if (!ft_strncmp(str, cpy->name, ft_strlen(cpy->name))
			&& !ft_strncmp(str, cpy->name, ft_strlen(str)))
			return (cpy->value);
		else if (str[0] == '?')
			return (ft_itoa(g_value_exit));
		if (cpy->next)
			cpy = cpy->next;
		else
			break ;
	}
	return (NULL);
}

char	*fill_expand(t_msh *msh, int i, int j, char *word)
{
	char	*str;
	char	*exp;
	int		x;

	x = -1;
	str = NULL;
	exp = check_env_expand(msh, word);
	str = (char *)malloc(sizeof(char) + (ft_strlen(msh->line)
				+ ft_strlen(exp) + 1 - ft_strlen(word)));
	if (!(str))
		return (NULL);
	if (word[0] != '?')
		free(word);
	while (++x < i)
		str[x] = msh->line[x];
	x = 0;
	while (exp[x])
		str[i++] = exp[x++];
	while (msh->line[j])
		str[i++] = msh->line[j++];
	str[i] = '\0';
	if (exp[0] == '1')
		free(exp);
	free(msh->line);
	return (str);
}

char	*fill_no_expand(t_msh *msh, char *word, int i, int j)
{
	int		x;
	char	*str;

	str = (char *)malloc(sizeof(char) + (ft_strlen(msh->line)
				+ 1 - ft_strlen(word)));
	if (!str)
		return (NULL);
	free(word);
	x = 0;
	while (x < i)
	{
		str[x] = msh->line[x];
		x++;
	}
	while (msh->line[j])
	{
		str[x] = msh->line[j];
		x++;
		j++;
	}
	str[x] = '\0';
	free(msh->line);
	return (str);
}

void	add_expand_bis(t_msh *msh, int i, char *word)
{
	int	j;

	j = i + 1;
	while (msh->line[j] && ft_isalnum(msh->line[j]))
		j++;
	word = ft_substr(msh->line, (i + 1), (j - i - 1));
	if (check_env_expand(msh, word))
		msh->line = fill_expand(msh, i, j, word);
	else
		msh->line = fill_no_expand(msh, word, i, j);
}

char	*add_expand(t_msh *msh)
{
	int		i;
	char	*word;
	int		quote;

	i = -1;
	quote = 0;
	msh->line = valeur_retour(msh);
	while (msh->line[++i])
	{
		if (msh->line[i] == '\'' && quote == 0)
			i = split_what(msh->line, i, msh->line[i]);
		if (msh->line[i] == '"')
		{
			if (quote == 1)
				quote = 0;
			else
				quote = 1;
		}
		if (msh->line[i] == '$' && ft_isalnum(msh->line[i + 1]))
			add_expand_bis(msh, i, word);
	}
	return (msh->line);
}

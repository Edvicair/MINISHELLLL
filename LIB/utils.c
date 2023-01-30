/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvicair <edvicair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 00:48:15 by edvicair          #+#    #+#             */
/*   Updated: 2023/01/29 06:36:05 by edvicair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_type	ft_choose_type(int R)
{
	t_type	t;

	if (R == 1)
		t = RE_G;
	else if (R == 2)
		t = H_DOC;
	else if (R == -1)
		t = RE_D;
	else if (R == -2)
		t = RE_DD;
	else
		t = NO_REDIR;
	return (t);
}

size_t	count_tab(t_env *env)
{
	t_env	*cpy;
	size_t	count;

	cpy = env;
	count = 0;
	while (cpy)
	{
		count++;
		if (cpy->next)
			cpy = cpy->next;
		else
			break ;
	}
	return (count);
}

char	*valeur_retour(t_msh *msh)
{
	int		i;
	char	*ss;

	i = 0;
	while (msh->line[i])
	{
		if (msh->line[i] == '\'')
			i = split_what(msh->line, i, msh->line[i]);
		if (msh->line[i] == '$' && msh->line[i + 1] == '?')
		{
			ss = "?\0";
			msh->line = fill_expand(msh, i, (i + 2), ss);
			return (msh->line);
		}
		i++;
	}
	return (msh->line);
}

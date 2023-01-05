/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvicair <edvicair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 06:30:57 by edvicair          #+#    #+#             */
/*   Updated: 2023/01/04 10:24:47 by edvicair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_unset_first(t_msh *msh, t_env *cpy, t_env *cpy_b)
{
	if (!ft_strcmp(cpy->name, msh->token->cmd[1]))
	{
		msh->env = msh->env->next;
		free(cpy->name);
		free(cpy->value);
		free(cpy);
		cpy->name = NULL;
		cpy->value = NULL;
		cpy = NULL;
		return (1);
	}
	return (0);
}

void	cut_env(t_env *env, t_env *cut, bool i)
{
	t_env *tmp;

	tmp = cut;
	if (i)
	{
		cut = cut->next;
		env->next = cut;
	}
	if (tmp->name)
		free(tmp->name);
	if (tmp->value)
		free(tmp->value);
	free(tmp);
}

void	ft_unset(t_msh *msh)
{
	t_env	*cpy;
	t_env	*cpy_b;
	int i;

	if (!msh->token->cmd[1])
		return ;
	cpy = msh->env;
	i = ft_unset_first(msh, cpy, cpy_b);
	while (!i && cpy->next)
	{
		if (!ft_strncmp(cpy->name, msh->token->cmd[1], (ft_strlen(msh->token->cmd[1]) + 1)))
		{
			if (cpy->next)
				cut_env(cpy_b, cpy, 1);
			i++;
			break ;
		}
		cpy_b = cpy;
		cpy = cpy->next;
	}
	if (!i && !ft_strncmp(cpy->name, msh->token->cmd[1], (ft_strlen(msh->token->cmd[1]) + 1)))
	{
		cut_env(cpy_b, cpy, 0);
		cpy_b->next = NULL;
	}
}

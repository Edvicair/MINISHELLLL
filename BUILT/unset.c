/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvicair <edvicair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 06:30:57 by edvicair          #+#    #+#             */
/*   Updated: 2023/01/13 18:02:13 by edvicair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_unset_first(t_msh *msh, t_env *cpy, char **cmd)
{
	if (!ft_strcmp(cpy->name, cmd[1]))
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

int 	ft_unset_bis(t_msh *msh, char **cmd,  t_env *cpy, t_env *cpy_b, int j)
{
	if (!ft_strncmp(cpy->name, cmd[j], (ft_strlen(cmd[j]) + 1)))
	{
		if (cpy->next)
		{
			cut_env(cpy_b, cpy, 1);
			return (1);
		}
	}
	return (0);
}
void	ft_unset(t_msh *msh, char **cmd)
{
	t_env	*cpy;
	t_env	*cpy_b;
	int i;
	int j;

	j = 0;
	if (!cmd[1])
		return ;
	while (cmd[++j])
	{
		i = 0;
		cpy = msh->env;
		i = ft_unset_first(msh, cpy, cmd);
		while (!i && cpy->next)
		{
			cpy_b = cpy;
			cpy = cpy->next;
			i = ft_unset_bis(msh, cmd, cpy, cpy_b, j);
		}
		if (!i && !ft_strncmp(cpy->name, cmd[j], (ft_strlen(cmd[j]) + 1)))
		{
			cut_env(cpy_b, cpy, 0);
			cpy_b->next = NULL;
		}
	}
}

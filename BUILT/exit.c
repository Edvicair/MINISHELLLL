/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvicair <edvicair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 19:12:04 by edvicair          #+#    #+#             */
/*   Updated: 2023/01/30 12:26:14 by edvicair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_env(t_env *env)
{
	t_env	*tmp;

	tmp = NULL;
	while (env)
	{
		if (env->name)
			free(env->name);
		env->name = NULL;
		if (env->value)
			free(env->value);
		env->value = NULL;
		if (env->next)
		{
			tmp = env;
			env = env->next;
			if (tmp)
				free(tmp);
			tmp = NULL;
		}
		else
			break ;
	}
	free(env);
	env = NULL;
}

void	ft_exit_bis(t_msh *msh, int res)
{
	close(msh->fd[0]);
	close(msh->fd[1]);
	dup2(msh->stin, 0);
	dup2(msh->stout, 1);
	close(msh->stin);
	close(msh->stout);
	if (msh->token->cmd[1])
	{
		free(msh->line);
		res = ft_atoi(msh->token->cmd[1]);
		ft_free_token(msh, msh->token);
		exit(res);
	}
}

void	ft_exit(t_msh *msh, int value)
{
	int	res;

	res = 0;
	if (msh->tab)
		free(msh->tab);
	if (msh->env)
		ft_free_env(msh->env);
	if (msh->token)
		ft_exit_bis(msh, res);
	if (msh->token)
		ft_free_token(msh, msh->token);
	free(msh->line);
	exit(value);
}

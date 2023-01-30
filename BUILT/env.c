/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvicair <edvicair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 20:28:00 by edvicair          #+#    #+#             */
/*   Updated: 2023/01/30 12:37:26 by edvicair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_getenv(t_msh *msh, char *namee)
{
	t_env	*cpy;

	cpy = msh->env;
	while (cpy->next)
	{
		if (!ft_strncmp(cpy->name, namee, ft_strlen(namee)))
			return (ft_strdup(cpy->value));
		cpy = cpy->next;
	}
}

void	ft_env_red(t_msh *msh, t_env *cpy, int fd)
{
	while (cpy)
	{
		if (!cpy->egal && cpy->value)
		{
			write(fd, cpy->name, ft_strlen(cpy->name));
			write(fd, cpy->value, ft_strlen(cpy->value));
			write(fd, "\n", 1);
		}
		else if (!cpy->egal && !cpy->value)
		{
			write(fd, cpy->name, ft_strlen(cpy->name));
			write(fd, "=\n", 2);
		}
		if (cpy->next)
			cpy = cpy->next;
		else
			break ;
	}
}

bool	ft_env_bis(t_msh *msh, t_env *cpy)
{
	if (msh->out != 1)
	{
		ft_env_red(msh, cpy, msh->out);
		return (1);
	}
	if (msh->pip)
	{
		ft_env_red(msh, cpy, msh->fd[1]);
		return (1);
	}
	return (0);
}

void	ft_env(t_msh *msh)
{
	t_env	*cpy;

	cpy = msh->env;
	if (msh->token->cmd[1])
	{
		printf("env: '%s': No such file or director", msh->token->cmd[1]);
		return ;
	}
	if (ft_env_bis(msh, cpy))
		return ;
	while (cpy)
	{
		if (!cpy->egal && cpy->value)
			printf("%s=%s\n", cpy->name, cpy->value);
		else if (!cpy->egal && !cpy->value)
			printf("%s=\n", cpy->name);
		if (cpy->next)
			cpy = cpy->next;
		else
			break ;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvicair <edvicair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 20:28:00 by edvicair          #+#    #+#             */
/*   Updated: 2023/01/09 10:18:25 by edvicair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_getenv(t_msh *msh, char *namee)
{
	t_env	*cpy;

	cpy = msh->env;
	while (cpy->next)
	{
		if (!ft_strcmp(cpy->name, namee))
			return (cpy->value);
		cpy = cpy->next;
	}
}

void	ft_env_red(t_msh *msh, t_env *cpy)
{
	while (cpy->next != NULL)
	{
		if (!cpy->egal && cpy->value)
		{
			write(msh->out, cpy->name, ft_strlen(cpy->name));
			write(msh->out, cpy->value, ft_strlen(cpy->value));
			write(msh->out, "\n", 1);
		}
		else if (!cpy->egal && !cpy->value)
		{
			write(msh->out, cpy->name, ft_strlen(cpy->name));
			write(msh->out, "=\n", 2);
		}
		cpy = cpy->next;
	}
	if (cpy->next == NULL && !cpy->egal && cpy->value)
	{
		write(msh->out, cpy->name, ft_strlen(cpy->name));
		write(msh->out, cpy->value, ft_strlen(cpy->value));
		write(msh->out, "\n", 1);
	}
	else if (cpy->next == NULL && !cpy->egal && !cpy->value)
	{	
		write(msh->out, cpy->name, ft_strlen(cpy->name));
		write(msh->out, "=\n", 2);
	}
}

void	ft_env(t_msh *msh)
{
	t_env	*cpy;

	cpy = msh->env;
	if (msh->out != 0 && msh->out != 1)
	{
		ft_env_red(msh, cpy);
		return ;
	}
	while (cpy->next != NULL)
	{
		if (!cpy->egal && cpy->value)
			printf("%s=%s\n", cpy->name, cpy->value);
		else if (!cpy->egal && !cpy->value)
			printf("%s=\n", cpy->name);
		cpy = cpy->next;
	}
	if (cpy->next == NULL && !cpy->egal && cpy->value)
		printf("%s=%s\n", cpy->name, cpy->value);
	else if (cpy->next == NULL && !cpy->egal && !cpy->value)
		printf("%s=\n", cpy->name);
}

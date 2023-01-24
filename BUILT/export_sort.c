/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvicair <edvicair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 15:01:54 by edvicair          #+#    #+#             */
/*   Updated: 2023/01/20 20:24:27 by edvicair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_write_export(int fd, t_env *export)
{
	if (export->value)
	{
		write(fd, "declare -x ", ft_strlen("declare -x "));
		write(fd, export->name, ft_strlen(export->name));
		write(fd, "=\"", 2);
		write(fd, export->value, ft_strlen(export->value));
		write(fd, "\"\n", 2);
	}
	else if (!export->egal)
	{
		write(fd, "declare -x ", ft_strlen("declare -x "));
		write(fd, export->name, ft_strlen(export->name));
		write(fd, "=\"\"\n", 4);
	}
	else
	{
		write(fd, "declare -x ", ft_strlen("declare -x "));
		write(fd, export->name, ft_strlen(export->name));
		write(fd, "\n", 1);
	}
}

void	aff_export(t_msh *msh, t_env *export)
{
	t_env	*tmp;
	int		fd;

	if (msh->out != 1)
		fd = msh->out;
	if (msh->pip)
		fd = msh->fd[1];
	else
		fd = 1;
	while (export)
	{
		ft_write_export(fd, export);
		if (export->next)
		{
			tmp = export;
			export = export->next;
			free(tmp);
			tmp = NULL;
		}
		else
			break ;
	}
	free(export);
	export = NULL;
}

bool	search_export(t_env *exp, char *namee)
{
	t_env	*cpy;

	if (!exp)
		return (0);
	cpy = exp;
	while (cpy && cpy->next)
	{
		if (!ft_strncmp(cpy->name, namee, (ft_strlen(namee) + 1)))
			return (1);
		cpy = cpy->next;
	}
	if (!ft_strncmp(cpy->name, namee, (ft_strlen(namee) + 1)))
		return (1);
	return (0);
}

t_env	*ft_sort_export_bis(t_env *cpy, t_env *export, t_env *a, int res)
{
	t_env	*b;

	b = cpy->next;
	res = ft_strcmp(a->name, b->name);
	if (res > 0)
	{
		if (!search_export(export, b->name))
			return (cpy->next);
	}
	return (a);
}

void	ft_sort_export(t_msh *msh)
{
	t_env	*cpy;
	t_env	*export;
	t_env	*a;
	int		res;

	cpy = msh->env;
	a = cpy;
	export = NULL;
	while (cpy && cpy->next)
	{
		while (cpy && cpy->next)
		{
			a = ft_sort_export_bis(cpy, export, a, res);
			cpy = cpy->next;
		}
		ft_env_add_back(&export, ft_env_new(msh, a->name, a->value, a->egal));
		cpy = msh->env;
		while (cpy->next && search_export(export, cpy->name))
			cpy = cpy->next;
		a = cpy;
	}
	if (!search_export(export, a->name))
		ft_env_add_back(&export, ft_env_new(msh, a->name, a->value, a->egal));
	aff_export(msh, export);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvicair <edvicair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 15:01:54 by edvicair          #+#    #+#             */
/*   Updated: 2022/11/18 17:23:59 by edvicair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	aff_export(t_env *export)
{
	t_env	*tmp;

	while (export->next)
	{
		if (export->value)
			printf("declare -x %s=\"%s\"\n", export->name, export->value);
		else if (!export->egal)
			printf("declare -x %s=\"\"\n", export->name);
		else
			printf("declare -x %s\n", export->name);
		tmp = export;
		export = export->next;
		free(tmp);
		tmp = NULL;
	}
	if (export->value)
		printf("declare -x %s=\"%s\"\n", export->name, export->value);
	else if (!export->egal)
		printf("declare -x %s=\"\"\n", export->name);
	else
		printf("declare -x %s\n", export->name);
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
	aff_export(export);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvicair <edvicair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 17:46:25 by edvicair          #+#    #+#             */
/*   Updated: 2023/01/24 06:43:47 by edvicair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*test_path(t_msh *msh, char **cmd, char **path)
{
	int		i;
	char	*tmp;
	char	*path_b;

	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(msh, path[i], "/");
		path_b = ft_strjoin(msh, tmp, cmd[0]);
		free(tmp);
		if (access(path_b, X_OK) == 0)
			return (path_b);
		free(path_b);
		i++;
	}
	if (!path[i])
	{
		if (access(cmd[0], X_OK) == 0)
			return (cmd[0]);
	}
	return (NULL);
}

char	*exec_bis(t_msh *msh, t_env *cpy, char **cmd)
{
	char	**path;
	char	*paths;

	while (cpy->next)
	{
		if (!ft_strncmp(cpy->name, "PATH", 5))
		{
			path = ft_split(cpy->value, ':');
			break ;
		}
		cpy = cpy->next;
	}
	paths = test_path(msh, cmd, path);
	ft_free_double(path);
	return (paths);
}

void	exec(t_msh *msh, char **cmd, char **env)
{	
	char	*paths;
	t_env	*cpy;

	cpy = msh->env;
	paths = exec_bis(msh, cpy, cmd);
	if (paths == NULL)
	{
		write(2, "Can't find command\n", 19);
		free(paths);
		exit(0);
	}
	else if (execve(paths, cmd, env) == -1)
	{
		perror("Can't execve");
		free(paths);
		exit(0);
	}
}

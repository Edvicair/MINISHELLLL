/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvicair <edvicair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 17:46:25 by edvicair          #+#    #+#             */
/*   Updated: 2022/11/27 23:33:48 by edvicair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*exec_path(char **cmd, char **path)
{
	int		i;
	char	*tmp;
	char *paths

	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		paths = ft_strjoin(tmp, cmd[0]);
		free(tmp);
		if (access(paths, X_OK) == 0)
			return (paths);
		free(paths);
		i++;
	}
	if (!path[i])
	{
		if (access(cmd[0], X_OK) == 0)
			return (cmd[0]);
	}
	return (NULL);
}

void	exec(t_msh *msh, char **cmd, char **env)
{	
	char	**path;
	char	*paths;
	t_env	*cpy;

	cpy = msh->env;
	while (cpy->next)
	{
		if (!ft_strncmp(cpy->name, "PATH", 5))
		{
			path = ft_split(cpy->value, ':');
			break;
		}
		cpy = cpy->next;
	}
	paths = exec_path(cmd, path);
	free(path);
	if (paths == NULL)
	{
		write(2, "Can't find command\n", 19);
		ft_free_double(paths);
		free_double(cmd);
		exit(0);
	}
	else if (execve(paths, cmd, env) == -1)
	{
		perror("Can't execve");
		free_double(paths);
	}
}
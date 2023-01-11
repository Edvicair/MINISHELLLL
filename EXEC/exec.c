/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvicair <edvicair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 17:46:25 by edvicair          #+#    #+#             */
/*   Updated: 2023/01/10 20:48:08 by edvicair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*exec_path(t_msh *msh, char **cmd, char **path)
{
	int		i;
	char	*tmp;
	char *path_b;

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
	paths = exec_path(msh, cmd, path);
	free(path);
	if (paths == NULL)
	{
		write(2, "Can't find command\n", 19);
		free(paths);
	}
	else if (execve(paths, cmd, env) == -1)
	{
		perror("Can't execve");
		free(paths);
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvicair <edvicair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 11:10:32 by edvicair          #+#    #+#             */
/*   Updated: 2023/01/09 09:53:23 by edvicair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t count_tab(t_env *env)
{
	t_env *cpy;
	size_t count;

	cpy = env;
	count = 0;
	while (cpy && cpy->next)
	{
		count++;
		cpy = cpy->next;
	}
	return (count);
}

char	**tab_env(t_msh *msh, t_env *env)
{
	char **str;
	t_env *cpy;
	size_t i;

	cpy = env;
	i = count_tab(env);
	str = (char **)malloc(sizeof(char *) * i + 1);
	i = 0;
	while (cpy->next)
	{
		if (cpy->name && cpy->value)
		{
			str[i] = ft_strjoin(msh, cpy->name, "=");
			str[i] = ft_strjoin(msh, str[i], cpy->value);
		}
		i++;
		cpy = cpy->next;
	}
	if (cpy->name && cpy->value)
	{
		str[i] = ft_strjoin(msh, cpy->name, "=");
		str[i] = ft_strjoin(msh, str[i], cpy->value);
		i++;
		str[i] = NULL;
	}
	return (str);
}

void	one_child(t_msh *msh, int in, int out)
{
	t_token *cpy;
	char **env;

	printf("one child\n");
	printf("	in = %d | out = %d\n", in, out);
	cpy = msh->token;
	env = tab_env(msh, msh->env);
	msh->token->child = fork();
	if (msh->token->child == -1)
	{
		perror("Can't fork");
//	  free_double(pipe->path);
		exit(0);
	}
	if (msh->token->child == 0)
	{
		if (in && !out)
		{
			printf("	if\n");
			dup2(in, STDIN_FILENO);
			dup2(cpy->fd[1], STDOUT_FILENO);
			close(cpy->fd[0]);
			close(cpy->fd[1]);
			exec(msh, msh->token->cmd, env);
		}
		else if (!in && out)
		{
			printf("	else if\n");
			dup2(out, STDOUT_FILENO);
			dup2(cpy->fd[0], STDIN_FILENO);
			close(cpy->fd[1]);
			close(cpy->fd[0]);
			exec(msh, msh->token->cmd, env);
		}
	}
	close(cpy->fd[1]);
	close(cpy->fd[0]);
}
void	ft_child(t_msh *t_msh)
{
	int in;
	int out;
		
}
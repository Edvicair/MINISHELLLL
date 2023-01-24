/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvicair <edvicair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 11:10:32 by edvicair          #+#    #+#             */
/*   Updated: 2023/01/24 08:28:36 by edvicair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	count_tab(t_env *env)
{
	t_env	*cpy;
	size_t	count;

	cpy = env;
	count = 0;
	while (cpy)
	{
		count++;
		if (cpy->next)
			cpy = cpy->next;
		else
			break ;
	}
	return (count);
}

char	**join_env(t_msh *msh, t_env *cpy, char **str)
{
	char	*tmp;
	int		i;

	i = 0;
	while (cpy)
	{
		if (cpy->name && cpy->value)
		{
			tmp = ft_strjoin(msh, cpy->name, "=");
			str[i] = ft_strjoin(msh, tmp, cpy->value);
			free(tmp);
		}
		i++;
		if (cpy->next)
			cpy = cpy->next;
		else
			break ;
	}
	str[i] = NULL;
}

char	**tab_env(t_msh *msh, t_env *env)
{
	char	**str;
	t_env	*cpy;
	size_t	i;

	cpy = env;
	i = count_tab(env);
	str = (char **)malloc(sizeof(char *) * (i + 1));
	if (!str)
		return (NULL);
	i = 0;
	str = join_env(msh, cpy, str);
	return (str);
}

void	ft_dup(t_msh *msh, t_token *token)
{
	if (msh->in)
	{
		dup2(msh->in, 0);
		close(msh->in);
	}
	if (msh->out != 1)
	{
		dup2(msh->out, 1);
		close(msh->out);
	}
	else if (msh->pip)
		dup2(msh->fd[1], 1);
	close(msh->fd[1]);
	close(msh->fd[0]);
}

void	one_child(t_msh *msh, t_token *token, int i)
{
	char	**env;

	signal (SIGINT, SIG_IGN);
	signal (SIGQUIT, SIG_IGN);
	token->child = fork();
	signal (SIGINT, sida_c);
	signal (SIGQUIT, sida_d);
	if (token->child == -1)
	{
		perror("Can't fork");
		exit(0);
	}
	if (token->child == 0)
	{
		env = tab_env(msh, msh->env);
		if (!env)
		{
			perror("No env");
			exit(0);
		}
		ft_dup(msh, token);
		close(msh->stin);
		exec(msh, token->cmd, env);
	}
	msh->tab[i] = token->child;
}

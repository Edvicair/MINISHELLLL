/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvicair <edvicair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 04:36:08 by edvicair          #+#    #+#             */
/*   Updated: 2022/12/09 15:53:57 by edvicair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    free_one_env(t_env *env)
{
    free(env->name);
    env->name = NULL;
    free(env->value);
    env->value = NULL;
    free(env);
    env = NULL;
}

void    ft_free_double(char **s)
{
    int i;

    i = 0;
    if (s == NULL)
        return ;
    while (s[i])
    {
        free(s[i]);
        s[i] = NULL;
        i++;
    }
    free(s);
    s = NULL;
}

void    ft_free_redir(t_redir *redir)
{
    t_redir *tmp;

    while (redir->next)
    {
        if (redir->feldup)
            free(redir->feldup);
        tmp = redir;
        redir = redir->next;
        free(tmp);
    }
    if (redir->feldup)
        free(redir->feldup);
    free(redir);    
}

void	ft_free_token(t_token *token)
{
	t_token *tmp;
	
	while (token->next)
	{
        if (token->redir)
            ft_free_redir(token->redir);
		ft_free_double(token->cmd);
		tmp = token;
		token = token->next;
		free(tmp);
	}
	ft_free_double(token->cmd);
	free(token);
	token = NULL;
}
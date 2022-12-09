/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvicair <edvicair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 17:36:39 by edvicair          #+#    #+#             */
/*   Updated: 2022/12/01 13:05:21 by edvicair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    one_child(t_msh *msh, int child, int in, int out)
{
        t_token *cpy;

        cpy = msh->token;
        child = fork();
        if (child == -1)
        {
            perror("Can't fork");
//          free_double(pipe->path);
            exit(0);
	    }
        if (child = 0)
        {
            if (in && !out)
            {
                dup2(in, STDIN_FILENO);
                dup2(cpy->fd[1], STDOUT_FILENO)
                close(cpy->fd[0]);
                close(cpy->fd[1]);
            }
            else if (!in && out)
            {
                dup2(out, STDOUT_FILENO);
                dup2(cpy->fd[0], STDIN_FILENO);
                close(cpy->fd[1]);
                close(cpy->fd[0]);
            }
            else
            {
                dup2()
            }   
            
        }
}
void    ft_child(t_msh *t_msh)
{
    int in;
    int out;
    
}
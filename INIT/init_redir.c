/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvicair <edvicair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 11:36:23 by edvicair          #+#    #+#             */
/*   Updated: 2022/12/09 15:47:21 by edvicair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_type  ft_choose_type(int R)
{
    t_type t;
	
    if (R == 1)
        t = RE_G;
    else if (R == 2)
        t = H_DOC;
    else if (R == -1)
        t = RE_D;
    else if (R == -2)
		t = RE_DD;
    return (t);
}

t_redir	*ft_redir_new(int R, char *word)
{
	t_redir	*lst_redir;
	char *cpy;

	lst_redir = (t_redir *)malloc(sizeof(t_redir));
	if (!lst_redir)
		return (NULL);
    lst_redir->type = ft_choose_type(R);
    lst_redir->feldup = word; 
	lst_redir->next = 0;
	return (lst_redir);
}

t_redir	*ft_redir_last(t_redir *redir)
{
	if (redir)
	{
		while (redir->next)
			redir = redir->next;
	}
	return (redir);
}

void	ft_redir_add_back(t_redir **redir, t_redir *new)
{
	t_redir	*lst_redir;
	
	if (redir)
	{
		if (*redir)
		{
			lst_redir = ft_redir_last(*redir);
			lst_redir->next = new;
		}
		else
		    *redir = new;
	}
}

t_redir *ft_init_redir(char *word, int R)
{
    t_redir *red;
    
    red = NULL;
    ft_redir_add_back(&red, ft_redir_new(R, word));
    return (red);
}

// int	redi_less(t_msh *msh, char *str, int i)
// {
// 	int R;
// 	int j;
//     t_redir *red;
//     char *word;

// 	R = 0;
// 	while ((str[i] <= 9 && str[i] >= 13) || str[i] != 32)
// 	{
// 		if (str[i] == '>')
// 			R--;
// 		else if (str[i] == '<')
// 			R++;
// 		i++;
// 	}
// 	j = i + 1;
// 	while ((str[j] <= 9 && str[j] >= 13) || str[j] != 32)
// 		j++;
//     word = ft_substr(str, i, ((j - i) + 1));
// 	msh->token->redir = ft_init_redir(word, R);
// 	if(msh->token->redir)
// 		printf("OK\n");
// 	if(!msh->token->redir)
// 		printf("PAS OK\n");
//     printf("FINAL->feldup = %s\n", msh->token->redir->feldup);
// 	return(i + j);
// }

t_redir	*redi_less(char *str)
{
	int i;
	int j;
	int R;
    t_redir *red;
    
    red = NULL;
	i = 0;
	R = 0;
	while (str[i] && str[i] != '<' && str[i] != '>')
		i++;
	while (str[i] && (str[i] == '<' || str[i] == '>'))
	{
		if (str[i] == '>')
			R--;
		else if (str[i] == '<')
			R++;
		i++;
	}
	j = i + 2;
	while (str[j] && ((str[j] <= 9 && str[j] >= 13) || str[j] != 32))
		j++;
    ft_redir_add_back(&red, ft_redir_new(R, ft_substr(str, (i + 1), ((j - i) + 1))));
	return (red);
}
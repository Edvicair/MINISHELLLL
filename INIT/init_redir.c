/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motaouss <motaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 00:20:01 by motaouss          #+#    #+#             */
/*   Updated: 2023/01/18 19:24:02 by motaouss         ###   ########.fr       */
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
	else
		t = NO_REDIR;
    return (t);
}

t_redir	*ft_redir_new(int R, char *word)
{
	t_redir	*lst_redir;

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

t_redir	*redi_less(char *str)
{
	int i;
	int j;
	int R;
    t_redir *red;
    
    red = NULL;
	i = 0;
	j = 0;
	while (str[i])
	{
		R = 0;
		while (str[i] && str[i] != '<' && str[i] != '>')
		{
			if (str[i] == '\'' || str[i] == '"')
				i = split_what(str, i, str[i]);
			i++;
		}
		while (str[i] && (str[i] == '<' || str[i] == '>'))
		{
			if (str[i] == '>')
				R--;
			else if (str[i] == '<')
				R++;
			i++;
		}
		while (str[i] == ' ')
			i++;
		j = i;
		while (str[j] && str[j] != ' ' && str[j] != '>' && str[j] != '>')
			j++;
		if (R != 0)
			ft_redir_add_back(&red, ft_redir_new(R, ft_substr2(str, i, j)));
		else if (R == 0 && !(red))
			ft_redir_add_back(&red, ft_redir_new(R, NULL));
	}
	return (red);
}
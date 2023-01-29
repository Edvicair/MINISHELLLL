/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvicair <edvicair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 00:20:01 by motaouss          #+#    #+#             */
/*   Updated: 2023/01/29 00:47:43 by edvicair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_redir	*ft_redir_new(int R, char *word)
{
	t_redir	*lst_redir;

	lst_redir = (t_redir *)malloc(sizeof(t_redir));
	if (!lst_redir)
		return (NULL);
	lst_redir->type = ft_choose_type(R);
	if (lst_redir->type == H_DOC)
		lst_redir->feldup = here_doc(word);
	else
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

int	redi_bis(char *str, int *i)
{
	int	red;

	red = 0;
	while (str[*i] && str[*i] != '<' && str[*i] != '>')
	{
		if (str[*i] == '\'' || str[*i] == '"')
			*i = split_what(str, *i, str[*i]);
		*i += 1;
	}
	while (str[*i] && (str[*i] == '<' || str[*i] == '>'))
	{
		if (str[*i] == '>')
			red--;
		else if (str[*i] == '<')
			red++;
		*i += 1;
	}
	while (str[*i] == ' ')
		*i += 1;
	return (red);
}

t_redir	*redi_less(char *str)
{
	int		i;
	int		j;
	int		red;
	t_redir	*redir;

	redir = NULL;
	i = 0;
	j = 0;
	while (str[i])
	{
		red = redi_bis(str, &i);
		j = i;
		while (str[j] && str[j] != ' ' && str[j] != '>' && str[j] != '>')
			j++;
		if (red != 0)
			ft_redir_add_back(&redir, ft_redir_new(red, ft_substr2(str, i, j)));
		else if (red == 0 && !(redir))
			ft_redir_add_back(&redir, ft_redir_new(red, NULL));
	}
	return (redir);
}

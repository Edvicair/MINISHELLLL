/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvicair <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 18:18:09 by edvicair          #+#    #+#             */
/*   Updated: 2021/01/11 11:41:28 by edvicair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*res;
	t_list	*tmp;

	if (lst == NULL || (*f) == NULL || (*del) == NULL)
		return (NULL);
	res = ft_lstnew((*f)(lst->content));
	if (!res)
	{
		ft_lstclear(&res, (*del));
		return (NULL);
	}
	tmp = res;
	lst = lst->next;
	while (lst)
	{
		res->next = ft_lstnew((*f)(lst->content));
		if (!res->next)
		{
			ft_lstclear(&res, (*del));
			return (NULL);
		}
		lst = lst->next;
		res = res->next;
	}
	return (tmp);
}

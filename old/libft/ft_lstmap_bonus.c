/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocorrea <jocorrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 11:43:52 by jocorrea          #+#    #+#             */
/*   Updated: 2023/07/09 12:30:29 by jocorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*new_tlist(t_list **new_list, t_list **tmp, void **content)
{
	if (*tmp)
	{
		(*tmp)->next = ft_lstnew(*content);
		if (!(*tmp)->next)
			return (NULL);
		*tmp = (*tmp)->next;
	}
	else
	{
		*tmp = ft_lstnew(*content);
		if (!*tmp)
			return (NULL);
		*new_list = *tmp;
	}
	return (*tmp);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*tmp;
	t_list	*new_list;
	void	*content;

	new_list = NULL;
	tmp = new_list;
	while (lst)
	{
		content = f(lst->content);
		if (!content)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		if (!new_tlist(&new_list, &tmp, &content))
		{
			if (tmp && !tmp->next)
				ft_lstclear(&new_list, del);
			free (content);
			return (NULL);
		}
		lst = lst->next;
	}
	return (new_list);
}

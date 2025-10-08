/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocorrea <jocorrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 11:08:49 by jocorrea          #+#    #+#             */
/*   Updated: 2023/01/22 15:03:02 by jocorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content)
{
	t_list	*linkedlist;

	linkedlist = (t_list *)malloc(sizeof(t_list));
	if (!linkedlist)
		return (NULL);
	linkedlist->content = (void *)content;
	linkedlist->next = NULL;
	return (linkedlist);
}

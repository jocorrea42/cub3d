/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocorrea <jocorrea@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 16:03:17 by jocorrea          #+#    #+#             */
/*   Updated: 2023/01/15 15:22:59 by jocorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *str, size_t n)
{
	unsigned char		*p_dest;
	unsigned const char	*p_str;

	if (dst == NULL && str == NULL)
		return (NULL);
	if (dst < str)
		return (ft_memcpy(dst, str, n));
	p_dest = (unsigned char *) dst;
	p_str = (unsigned const char *) str;
	while (n--)
		p_dest[n] = p_str[n];
	return (dst);
}

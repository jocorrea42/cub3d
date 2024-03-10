/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 11:31:31 by lsulzbac          #+#    #+#             */
/*   Updated: 2023/08/14 11:31:33 by lsulzbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stddef.h>
#include <stdlib.h>

static int	is_delim(char c, const char *delim)
{
	if (!c)
		return (1);
	while (*delim)
	{
		if (c == *delim)
			return (1);
		delim++;
	}
	return (0);
}

char	*ft_strtok(char *input, const char *delim)
{
	static char	*str;
	static int	i;
	static int	size;
	int			start;

	if (input != NULL)
	{
		str = input;
		size = ft_strlen(str);
		i = 0;
	}
	else if (i == size)
		return (NULL);
	else
		i++;
	start = i;
	while (!is_delim(str[i], delim))
		i++;
	str[i] = '\0';
	return (str + start);
}

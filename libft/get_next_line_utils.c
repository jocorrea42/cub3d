/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocorrea <jocorrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 15:19:58 by jocorrea          #+#    #+#             */
/*   Updated: 2023/06/11 17:04:15 by jocorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen_g(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strchr_g(const char *s, int c)
{
	if (s && *s)
	{
		while (*s && *s != (char)c)
			s++;
		if (*s == (char)c)
			return ((char *)s);
	}
	return (NULL);
}

char	*ft_strjoin_g(char *buffer, char *tail, ssize_t size)
{
	int		i;
	int		j;
	char	*tmp;

	if (!buffer)
		buffer = ft_calloc(sizeof(char), 1);
	if (!buffer)
		return (NULL);
	tmp = ft_calloc((ft_strlen_g(buffer) + size + 1), sizeof(char));
	if (!tmp)
		return (true_free(&buffer));
	i = -1;
	while (buffer[++i])
		tmp[i] = buffer[i];
	j = -1;
	while (tail[++j])
		tmp[i++] = tail[j];
	true_free(&buffer);
	return (tmp);
}

void	*true_free(char **buffer)
{
	if (buffer && *buffer)
	{
		free(*buffer);
		*buffer = NULL;
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 19:28:14 by lsulzbac          #+#    #+#             */
/*   Updated: 2023/08/14 11:32:10 by lsulzbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_strcmp(char *s1, char *s2)
{
	if (s1 == NULL && s2 == NULL)
		return (0);
	else if (s1 == NULL || s2 == NULL)
		return (1);
	while (*s1 || *s2)
	{
		if (*s1 != *s2)
			return (1);
		s1++;
		s2++;
	}
	return (0);
}

char	*ft_strcat(char *s1, char *s2, int clean_it)
{
	char	*filepath;
	int		len1;
	int		len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (!len1 && !len2)
		return (NULL);
	filepath = (char *)ft_calloc(1, len1 + len2 + 1);
	if (filepath == NULL)
		return (NULL);
	ft_memcpy(filepath, s1, len1);
	ft_memcpy(filepath + len1, s2, len2);
	if (clean_it && s1 != NULL)
		free(s1);
	return (filepath);
}

void	check_extension(char *filename)
{
	if (ft_strcmp(EXTENSION, ft_strrchr(filename, '.')))
		ft_perror(EINVAL, "map must br .cub");
}

int	ft_open(char *filename)
{
	int	fd;

	check_extension(filename);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		ft_perror(0, "open");
	return (fd);
}

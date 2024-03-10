/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 11:32:14 by lsulzbac          #+#    #+#             */
/*   Updated: 2023/09/05 15:43:08 by lsulzbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*fake_gnl(int fd)
{
	char	*str;
	char	*tmp;
	int		read_result;

	str = NULL;
	tmp = (char *) safe_calloc (1, sizeof(char) * 2);
	read_result = read(fd, tmp, 1);
	while (read_result > 0)
	{
		if (!str)
			str = ft_strdup(tmp);
		else
			str = ft_strcat(str, tmp, 1);
		if (str == NULL)
		{
			close(fd);
			free(tmp);
			ft_perror(ENOMEM, "ft_strcat");
		}
		read_result = read(fd, tmp, 1);
	}
	free(tmp);
	return (str);
}

char	**ft_read(int fd)
{
	char	*map_line;
	char	*tmp;
	char	**ret_arr;

	map_line = fake_gnl(fd);
	close(fd);
	if (map_line == NULL)
		ft_perror(EINVAL, "Empty map");
	tmp = ft_strtrim(map_line, " \n");
	free(map_line);
	map_line = tmp;
	ret_arr = ft_split(map_line, '\n');
	free(map_line);
	if (ret_arr == NULL)
		ft_perror(ENOMEM, "split");
	return (ret_arr);
}

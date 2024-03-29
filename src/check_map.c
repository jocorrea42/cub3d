/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 10:24:24 by lsulzbac          #+#    #+#             */
/*   Updated: 2023/08/15 10:24:27 by lsulzbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	create_square_map(char **tmp, t_data *dt)
{
	size_t	width;
	int		height;

	width = 0;
	height = 0;
	while (tmp[height])
	{
		if (tmp[height][0] == '\0')
			ft_perror(EINVAL, "Space between map");
		if (ft_strlen(tmp[height]) > width)
			width = ft_strlen(tmp[height]);
		height++;
	}
	dt->map2d = (char **)safe_calloc(height + 1, sizeof(char *));
	while (--height >= 0)
	{
		dt->map2d[height] = (char *)safe_calloc(1, sizeof(char) * (width + 1));
		ft_memset(dt->map2d[height], '0', width);
		ft_memcpy(dt->map2d[height], tmp[height], ft_strlen(tmp[height]));
	}
}

void	add_to_count(t_data *data, int i, int j)
{
	if (data->map2d[i][j] == 'N')
		data->p_a = N;
	else if (data->map2d[i][j] == 'S')
		data->p_a = S;
	else if (data->map2d[i][j] == 'W')
		data->p_a = W;
	else if (data->map2d[i][j] == 'E')
		data->p_a = E;
	else
		return ;
	data->p_x = j;
	data->p_y = i;
	data->n_p += 1;
	data->map2d[i][j] = '0';
}

int	check_char(char c)
{
	int	i;

	i = 0;
	while (VALID_CHAR[i])
	{
		if (c == VALID_CHAR[i])
			return (0);
		i++;
	}
	return (1);
}

void	check_valid_char(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->h_map - 1)
	{
		j = 0;
		while (j < data->w_map - 1)
		{
			if (check_char(data->map2d[i][j]))
				ft_perror(EINVAL, "Char not allowed");
			add_to_count(data, i, j);
			j++;
		}
		i++;
	}
	if (data->n_p > 1)
		ft_perror(EINVAL, "More than one player found");
	if (data->n_p < 1)
		ft_perror(EINVAL, "No player found");
}

void	get_map_size(t_data *map)
{
	int	i;

	i = 0;
	map->w_map = ft_strlen(map->map2d[0]);
	while (map->map2d[i] != NULL)
	{
		map->h_map += 1;
		i++;
	}
}

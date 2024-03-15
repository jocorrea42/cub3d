/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_closed.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 18:44:12 by lsulzbac          #+#    #+#             */
/*   Updated: 2023/09/18 10:25:21 by lsulzbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**copy_map(t_data *map)
{
	int		i;
	char	**tmp_map;

	i = 0;
	tmp_map = (char **)safe_calloc((map->h_map + 1), sizeof(char *));
	while (i < map->h_map)
	{
		tmp_map[i] = safe_strdup(map->map2d[i]);
		i++;
	}
	return (tmp_map);
}

int	is_map_closed(t_data *map, int x, int y)
{
	if (x < 0 || y < 0 || x >= (int)map->w_map || y >= (int)map->h_map)
		return (1);
	if (map->map2d[y][x] == '1')
		return (0);
	map->map2d[y][x] = '1';
	if (is_map_closed(map, x, y - 1) || is_map_closed(map, x, y + 1)
		|| is_map_closed(map, x - 1, y) || is_map_closed(map, x + 1, y))
		return (1);
	return (0);
}

void	check_closed(t_cub *data)
{
	char	**tmp_map;

	tmp_map = copy_map(data->dt);
	if (is_map_closed(data->dt, data->dt->p_x, data->dt->p_y))
		ft_perror(EINVAL, "Map not closed");
	clean_array(data->dt->map2d);
	data->dt->map2d = tmp_map;
}

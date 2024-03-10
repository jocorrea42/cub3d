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

void	add_to_count(char c, t_data *data, int i, int j)
{
	if (c != '0' && c != '1' && c != ' ')
	{
		data->p_x = j;
		data->p_y = i;
		data->n_p += 1;
		if (c == 'N')
			data->p_a = N;
		else if (c == 'S')
			data->p_a = S;
		else if (c == 'W')
			data->p_a = W;
		else if (c == 'E')
			data->p_a = E;
	}
}

void	check_quantities(t_data *data)
{
	if (data->n_p > 1)
		ft_perror(EINVAL, "More than one player found");
	if (data->n_p < 1)
		ft_perror(EINVAL, "No player found");

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
			add_to_count(data->map2d[i][j], data, i, j);
			j++;
		}
		i++;
	}
	check_quantities(data);
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

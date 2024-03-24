/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_rays_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocorrea <jocorrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 10:58:15 by lsulzbac          #+#    #+#             */
/*   Updated: 2024/03/24 17:52:12 by jocorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_it_close(t_player *pl, int new_x, int new_y, int tile)
{
	double	distance;

	distance = sqrt(pow(pl->pl_x - new_x, 2)
			+ pow(pl->pl_y - new_y, 2));
	if ((int)distance < tile * 2)
		return (1);
	return (0);
}

void	invert_door(char **map, int x, int y)
{
	if (map[y][x] == '2')
		map[y][x] = '3';
	else
		map[y][x] = '2';
}

void	cast_door_ray(t_cub *mlx)
{
	double	h_inter;
	double	v_inter;

	mlx->ray->flag = 0;
	h_inter = get_h_inter(mlx, nor_angle(mlx->pl->angle));
	v_inter = get_v_inter(mlx, nor_angle(mlx->pl->angle));
	if (v_inter <= h_inter
		&& (mlx->ray->vert_hit == 2 || mlx->ray->vert_hit == 3)
		&& is_it_close(mlx->pl, mlx->ray->vert_x, mlx->ray->vert_y, *mlx->tile))
	{
		invert_door(mlx->dt->map2d, (int)floor(mlx->ray->vert_x / *mlx->tile),
			(int)floor(mlx->ray->vert_y / *mlx->tile));
	}
	else if ((mlx->ray->horiz_hit == 2 || mlx->ray->horiz_hit == 3)
		&& is_it_close(mlx->pl, mlx->ray->horiz_x,
			mlx->ray->horiz_y, *mlx->tile))
	{
		invert_door(mlx->dt->map2d, (int)floor(mlx->ray->horiz_x / *mlx->tile),
			(int)floor(mlx->ray->horiz_y / *mlx->tile));
	}
	mlx->pl->door = 0;
}

int	check_for_door(t_cub *mlx)
{
	double	h_inter;
	double	v_inter;

	mlx->ray->flag = 0;
	mlx->pl->door = 1;
	h_inter = get_h_inter(mlx, nor_angle(mlx->pl->angle));
	v_inter = get_v_inter(mlx, nor_angle(mlx->pl->angle));
	if (v_inter <= h_inter
		&& (mlx->ray->vert_hit == 2 || mlx->ray->vert_hit == 3)
		&& is_it_close(mlx->pl, mlx->ray->vert_x, mlx->ray->vert_y, *mlx->tile))
	{
		return (mlx->ray->vert_hit);
	}
	else if ((mlx->ray->horiz_hit == 2 || mlx->ray->horiz_hit == 3)
		&& is_it_close(mlx->pl, mlx->ray->horiz_x,
			mlx->ray->horiz_y, *mlx->tile))
	{
		return (mlx->ray->horiz_hit);
	}
	mlx->pl->door = 0;
	return (0);
}

int	mouse_click(int button, int x, int y, void *param)
{
	t_player	*pl;

	(void)button;
	(void)x;
	(void)y;
	pl = (t_player *) param;
	pl->shoot = 1;
	return (0);
}

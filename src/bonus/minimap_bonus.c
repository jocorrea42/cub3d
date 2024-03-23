/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 17:55:44 by lsulzbac          #+#    #+#             */
/*   Updated: 2024/03/23 17:55:47 by lsulzbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void minimap(t_cub *mlx)
{
	int i;
	int j;
	double factor_x;
	double factor_y;
	int x_m;
	int x_p;
	int y_m;
	int y_p;
	int tile_x;
	int tile_y;


	tile_x = mlx->dt->h_map * 10;
	tile_y = mlx->dt->w_map * 10;
	if (tile_y > S_W / 4)
	{
		factor_y = tile_y / (S_W / 4);
		tile_y = S_W / 4;
		tile_x = (int)tile_x / factor_y;
	}
	if (tile_x > S_H / 4)
	{
		factor_x = tile_x / (S_W / 4);
		tile_x = S_H / 4;
		tile_y = (int)tile_y / factor_x;
	}
	factor_x = tile_x / (mlx->dt->h_map);
	factor_y = tile_y / (mlx->dt->w_map);
	y_p = mlx->pl->pl_x / *mlx->tile;
	x_p = mlx->pl->pl_y / *mlx->tile;
	if ( mlx->dt->map2d[x_p][y_p] == '1')
	{
		x_p = mlx->old_x;
		y_p = mlx->old_y;
	}
	else
	{
		mlx->old_x = x_p;
		mlx->old_y = y_p;
	}
//	printf("x_m=%d, y_m=%d\n", x_m, y_m);
	i = -1;
	while (++i < tile_x)
	{
		j = -1;
		while (++j < tile_y)
		{
			x_m = (i / factor_x);
			y_m = (j / factor_y);
			if (x_m == x_p && y_m == y_p)
				my_mlx_pixel_put(mlx, j, i, 0xABCDEF);
			else if (x_m < mlx->dt->h_map && y_m < mlx->dt->w_map && mlx->dt->map2d[x_m][y_m] == '1')
				my_mlx_pixel_put(mlx, j, i, 0xFF0000);
			else if (x_m < mlx->dt->h_map && y_m < mlx->dt->w_map && mlx->dt->map2d[x_m][y_m] == '2')
				my_mlx_pixel_put(mlx, j, i, 0x00FF00);
			else if (x_m < mlx->dt->h_map && y_m < mlx->dt->w_map && mlx->dt->map2d[x_m][y_m] == '3')
				my_mlx_pixel_put(mlx, j, i, 0x0000FF);
			else
				my_mlx_pixel_put(mlx, j, i, *mlx->textures->floor);
		}
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocorrea <jocorrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 15:16:37 by jocorrea          #+#    #+#             */
/*   Updated: 2024/03/16 15:13:38 by jocorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	inter_check(float angle, float *inter, float *step, t_cub *mlx)
{
	if (mlx->hrz)
	{
		if (angle > 0 && angle < M_PI)
		{
			*inter += *mlx->tile;
			return (-1);
		}
		*step *= -1;
	}
	else
	{
		if (!(angle > M_PI_2 && angle < 3 * M_PI_2))
		{
			*inter += *mlx->tile;
			return (-1);
		}
		*step *= -1;
	}
	return (1);
}

int	wall_hit(float x, float y, t_cub *mlx)
{
	int	x_m;
	int	y_m;

	if (x < 0 || y < 0)
		return (1);
	x_m = floor(x / *mlx->tile);
	y_m = floor(y / *mlx->tile);
	if ((y_m >= mlx->dt->h_map || x_m >= mlx->dt->w_map))
		return (1);
	if (mlx->dt->map2d[y_m] && x_m <= (int)ft_strlen(mlx->dt->map2d[y_m]))
	{
		if (mlx->dt->map2d[y_m][x_m] == '1')
			return (1);
		if (mlx->dt->map2d[y_m][x_m] == '2' && mlx->pl->door)
			return (2);
		if (mlx->dt->map2d[y_m][x_m] == '3')
			return (3);
	}
	return (0);
}

float	get_h_inter(t_cub *mlx, float angl)
{
	float	h_x;
	float	h_y;
	float	x_step;
	float	y_step;
	int		pixel;

	y_step = *mlx->tile;
	x_step = y_step / tan(angl);
	h_y = floor(mlx->pl->pl_y / *mlx->tile) * *mlx->tile;
	mlx->hrz = 1;
	pixel = inter_check(angl, &h_y, &y_step, mlx);
	h_x = mlx->pl->pl_x + (h_y - mlx->pl->pl_y) / tan(angl);
	if ((unit_circle(angl, 'y') && x_step > 0) || (!unit_circle(angl, 'y') \
		&& x_step < 0))
		x_step *= -1;
	mlx->ray->horiz_hit = wall_hit(h_x, h_y - pixel, mlx);
	while (!mlx->ray->horiz_hit)
	{
		h_x += x_step;
		h_y += y_step;
		mlx->ray->horiz_hit = wall_hit(h_x, h_y - pixel, mlx);
	}
	mlx->ray->horiz_x = h_x;
	mlx->ray->horiz_y = h_y - pixel;
	return (sqrt(pow(h_x - mlx->pl->pl_x, 2) + pow(h_y - mlx->pl->pl_y, 2)));
}

float	get_v_inter(t_cub *mlx, float angl)
{
	float	v_x;
	float	v_y;
	float	x_step;
	float	y_step;
	int		pixel;

	x_step = *mlx->tile;
	y_step = *mlx->tile * tan(angl);
	v_x = floor(mlx->pl->pl_x / *mlx->tile) * *mlx->tile;
	mlx->hrz = 0;
	pixel = inter_check(angl, &v_x, &x_step, mlx);
	v_y = mlx->pl->pl_y + (v_x - mlx->pl->pl_x) * tan(angl);
	if ((unit_circle(angl, 'x') && y_step < 0) || (!unit_circle(angl, 'x')
			&& y_step > 0))
		y_step *= -1;
	mlx->ray->vert_hit = wall_hit(v_x - pixel, v_y, mlx);
	while (!mlx->ray->vert_hit)
	{
		v_x += x_step;
		v_y += y_step;
		mlx->ray->vert_hit = wall_hit(v_x - pixel, v_y, mlx);
	}
	mlx->ray->vert_x = v_x - pixel;
	mlx->ray->vert_y = v_y;
	return (sqrt(pow(v_x - mlx->pl->pl_x, 2) + pow(v_y - mlx->pl->pl_y, 2)));
}

void	cast_rays(t_cub *mlx)
{
	double	h_inter;
	double	v_inter;
	int		ray;

	ray = 0;
	mlx->ray->ray_angle = mlx->pl->angle - (mlx->pl->fov_rd / 2);
	while (ray < S_W)
	{
		mlx->ray->flag = 0;
		h_inter = get_h_inter(mlx, nor_angle(mlx->ray->ray_angle));
		v_inter = get_v_inter(mlx, nor_angle(mlx->ray->ray_angle));
		if (v_inter <= h_inter)
			mlx->ray->distance = v_inter;
		else
		{
			mlx->ray->distance = h_inter;
			mlx->ray->flag = 1;
		}
		render_wall(mlx, ray);
		ray++;
		mlx->ray->ray_angle += (mlx->pl->fov_rd / S_W);
	}
}

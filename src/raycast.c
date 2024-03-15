/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyela <anyela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 15:16:37 by jocorrea          #+#    #+#             */
/*   Updated: 2024/03/04 11:55:35 by anyela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//#################################################################################//
//############################## THE RAYCASTING CODE ##############################//
//#################################################################################//

float	nor_angle(float angle) // normalize the angle
{
	if (angle < 0)
		angle += (2 * M_PI);
	if (angle > (2 * M_PI))
		angle -= (2 * M_PI);
	return (angle);
}

int	unit_circle(float angle, char c) // check the unit circle
{
	if (c == 'x' && (angle > 0 && angle < M_PI))
		return (1);
	else if (c == 'y' && (angle > (M_PI / 2) && angle < (3 * M_PI) / 2))
		return (1);
	return (0);
}

int	inter_check(float angle, float *inter, float *step, int is_horizon,
		t_cub *mlx) // check the intersection
{
	if (is_horizon) // if horizontal hit
	{
		if (angle > 0 && angle < M_PI)
			// between 0 and 180 grade but is down part need negative
		{
			*inter += *mlx->tile;
			return (-1);
		}
		*step *= -1;
	}
	else // vertical hit
	{
		if (!(angle > M_PI / 2 && angle < 3 * M_PI / 2))
			// between 90-270 right part need negative
		{
			*inter += *mlx->tile;
			return (-1);
		}
		*step *= -1;
	}
	return (1);
}

int	wall_hit(float x, float y, t_cub *mlx) // check the wall hit
{
	int x_m;
	int y_m;

	if (x < 0 || y < 0)
		return (0);              // return for overfloat windows
	x_m = floor(x / *mlx->tile); // get the x position in the map
	y_m = floor(y / *mlx->tile); // get the y position in the map
	if ((y_m >= mlx->dt->h_map || x_m >= mlx->dt->w_map))
		return (0);                                                    
			// return for overfloat windows pixels
	if (mlx->dt->map2d[y_m] && x_m <= (int)strlen(mlx->dt->map2d[y_m]))
		// protection leaks
		if (mlx->dt->map2d[y_m][x_m] == '1')                           
			// check the wall in board map
			return (0);
	return (1);
}

float	get_h_inter(t_cub *mlx, float angl) // get the horizontal intersection
{
	float h_x; // horizontal x
	float h_y; // horizontal y
	float x_step;
	float y_step;
	int pixel;

	y_step = *mlx->tile;
	x_step = y_step / tan(angl);
	h_y = floor(mlx->ply->plyr_y / *mlx->tile) * *mlx->tile;
	pixel = inter_check(angl, &h_y, &y_step, 1, mlx);
	h_x = mlx->ply->plyr_x + (h_y - mlx->ply->plyr_y) / tan(angl);
	if ((unit_circle(angl, 'y') && x_step > 0) || (!unit_circle(angl, 'y')
			&& x_step < 0)) // check x_step value
		x_step *= -1;
	while (wall_hit(h_x, h_y - pixel, mlx))
		// check the wall hit whit the pixel value
	{
		h_x += x_step;
		h_y += y_step;
	}
	mlx->ray->horiz_x = h_x;
	mlx->ray->horiz_y = h_y;
	return (sqrt(pow(h_x - mlx->ply->plyr_x, 2) + pow(h_y - mlx->ply->plyr_y,
				2))); // get the distance
}

float	get_v_inter(t_cub *mlx, float angl) // get the vertical intersection
{
	float v_x;
	float v_y;
	float x_step;
	float y_step;
	int pixel;

	x_step = *mlx->tile;
	y_step = *mlx->tile * tan(angl);
	v_x = floor(mlx->ply->plyr_x / *mlx->tile) * *mlx->tile;
	pixel = inter_check(angl, &v_x, &x_step, 0, mlx);
		// check the intersection and get the pixel value
	v_y = mlx->ply->plyr_y + (v_x - mlx->ply->plyr_x) * tan(angl);
	if ((unit_circle(angl, 'x') && y_step < 0) || (!unit_circle(angl, 'x')
			&& y_step > 0)) // check y_step value
		y_step *= -1;
	while (wall_hit(v_x - pixel, v_y, mlx))
		// check the wall hit whit the pixel value
	{
		v_x += x_step;
		v_y += y_step;
	}
	mlx->ray->vert_x = v_x;
	mlx->ray->vert_y = v_y;
	return (sqrt(pow(v_x - mlx->ply->plyr_x, 2) + pow(v_y - mlx->ply->plyr_y,
				2))); // get the distance
}

void	cast_rays(t_cub *mlx) // cast the rays
{
	double h_inter;
	double v_inter;
	int ray;

	ray = 0;
	mlx->ray->ray_angle = mlx->ply->angle - (mlx->ply->fov_rd / 2);
		// the start angle
	while (ray < S_W)                                              
		// loop for the rays
	{
		mlx->ray->flag = 0;                                        
			// flag for the wall
		h_inter = get_h_inter(mlx, nor_angle(mlx->ray->ray_angle));
			// get the horizontal intersection
		v_inter = get_v_inter(mlx, nor_angle(mlx->ray->ray_angle));
			// get the vertical intersection
		if (v_inter <= h_inter)                                    
			// check the distance
			mlx->ray->distance = v_inter;                          
				// get the distance
		else
		{
			mlx->ray->distance = h_inter; // get the distance
			mlx->ray->flag = 1;           // flag for the wall
		}
		render_wall(mlx, ray);                           // render the wall
		ray++;                                           // next ray
		mlx->ray->ray_angle += (mlx->ply->fov_rd / S_W); // next angle
	}
}
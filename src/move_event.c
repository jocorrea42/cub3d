/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_event.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyela <anyela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 09:50:55 by anyela            #+#    #+#             */
/*   Updated: 2024/02/28 10:00:22 by anyela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void rotate_player(t_cub *mlx, int i) // rotate the player
{
	if (i == 1)
	{
		mlx->ply->angle += ROTATION_SPEED; // rotate right
		if (mlx->ply->angle > 2 * PI)
			mlx->ply->angle -= 2 * PI;
	}
	else
	{
		mlx->ply->angle -= ROTATION_SPEED; // rotate left
		if (mlx->ply->angle < 0)
			mlx->ply->angle += 2 * PI;
	}
	mlx->ply->rot = 0;
}

void move_player(t_cub *mlx, double move_x, double move_y) // move the player
{
	int map_grid_y;
	int map_grid_x;
	int new_x;
	int new_y;

	new_x = roundf(mlx->ply->plyr_x + move_x); // get the new x position
	new_y = roundf(mlx->ply->plyr_y + move_y); // get the new y position
	map_grid_x = (new_x / TILE_SIZE);		   // get the x position in the map
	map_grid_y = (new_y / TILE_SIZE);		   // get the y position in the map
	if (mlx->dt->map2d[map_grid_y][map_grid_x] != '1' &&
		(mlx->dt->map2d[map_grid_y][mlx->ply->plyr_x / TILE_SIZE] != '1' &&
		 mlx->dt->map2d[mlx->ply->plyr_y / TILE_SIZE][map_grid_x] != '1')) // check the wall hit and the diagonal wall hit
	{
		mlx->ply->plyr_x = new_x; // move the player
		mlx->ply->plyr_y = new_y; // move the player
	}
}

void ft_exit(t_cub *mlx)   // exit the game
{
 int i = 0;
 while (mlx->dt->map2d[i])
  free(mlx->dt->map2d[i++]); // free the map line by line
 free(mlx->dt->map2d); // free the map
 free(mlx->dt); // free the data structure
 free(mlx->ply); // free the player structure
 free(mlx->ray); // free the ray structure
 mlx_destroy_image(mlx->img->mlx_ptr, mlx->img->img_ptr); // delete the image
 mlx_destroy_window(mlx->img->mlx_ptr, mlx->img->win_ptr); // terminate the mlx pointer
 printf("Game closed\n"); // print the message
 exit(0); // exit the game
}

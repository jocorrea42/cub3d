/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyela <anyela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 09:47:19 by anyela            #+#    #+#             */
/*   Updated: 2024/02/28 09:50:00 by anyela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int read_keys(int key_pressed, void *param)
{
	t_cub *cub;

	cub = (t_cub *)param;
	printf("TECLA = %d\n", key_pressed);
	
	if (key_pressed == 65364 || key_pressed == 115) // move down
		return (cub->ply->u_d = -1);
	else if (key_pressed == 65362 || key_pressed == 119) // move up
		return (cub->ply->u_d = 1);
	else if (key_pressed == 100) //move right
		return (cub->ply->l_r = 1);
	else if (key_pressed == 97)//move left
		return (cub->ply->l_r = -1);
	else if (key_pressed == 65361) // rotate left
		return (cub->ply->rot = -1);
	else if (key_pressed == 65363) // rotate right
		return (cub->ply->rot = 1);
	return (0);
}

void hook(t_cub *mlx, double move_x, double move_y) // hook the player
{
	if (mlx->ply->rot == 1) // rotate right
		rotate_player(mlx, 1);
	if (mlx->ply->rot == -1) // rotate left
		rotate_player(mlx, 0);
	if (mlx->ply->l_r == 1) // move right
	{
		move_x = -sin(mlx->ply->angle) * PLAYER_SPEED;
		move_y = cos(mlx->ply->angle) * PLAYER_SPEED;
		mlx->ply->l_r = 0;
	}
	if (mlx->ply->l_r == -1) // move left
	{
		move_x = sin(mlx->ply->angle) * PLAYER_SPEED;
		move_y = -cos(mlx->ply->angle) * PLAYER_SPEED;
		mlx->ply->l_r = 0;
	}
	if (mlx->ply->u_d == 1) // move up
	{
		move_x = cos(mlx->ply->angle) * PLAYER_SPEED;
		move_y = sin(mlx->ply->angle) * PLAYER_SPEED;
		mlx->ply->u_d = 0;
	}
	if (mlx->ply->u_d == -1) // move down
	{
		move_x = -cos(mlx->ply->angle) * PLAYER_SPEED;
		move_y = -sin(mlx->ply->angle) * PLAYER_SPEED;
		mlx->ply->u_d = 0;
	}
	move_player(mlx, move_x, move_y); // move the player
}

int exit_win(t_img *window)
{
	if (window)
		mlx_destroy_window(window->mlx_ptr, window->win_ptr);
	exit(EXIT_SUCCESS);
}
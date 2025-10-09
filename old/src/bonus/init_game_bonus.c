/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocorrea <jocorrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 10:01:55 by anyela            #+#    #+#             */
/*   Updated: 2024/03/24 17:51:44 by jocorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_main_img(t_cub *mlx, int frame, int random_pass)
{
	mlx_clear_window(mlx->mlx_ptr, mlx->win_ptr);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr,
		mlx->img->img_ptr, 0, 0);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr,
		mlx->textures->sprite->sprites[frame],
		S_W / 2 + (S_W / 6 - random_pass), S_H - mlx->textures->sprite->h + 10);
	if (mlx->pl->is_near_door == 2)
		centered_string(mlx->mlx_ptr, mlx->win_ptr,
			0xFFFFFF, "Press 'E' to close door");
	else if (mlx->pl->is_near_door == 3)
		centered_string(mlx->mlx_ptr, mlx->win_ptr,
			0xFFFFFF, "Press 'E' to open door");
}

void	draw_shoot_animation(t_cub *mlx, int random_pass)
{
	int	i;

	i = 0;
	if (mlx->pl->shoot == mlx->textures->sprite->size)
		mlx->pl->shoot = 0;
	draw_main_img(mlx, mlx->pl->shoot, random_pass);
	usleep(30000);
	if (mlx->pl->shoot)
		mlx->pl->shoot += 1;
	else
	{
		mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr,
			mlx->textures->sprite->sprites[mlx->textures->sprite->size],
			S_W / 2, S_H / 2);
	}
}

void	draw_image(t_cub *mlx)
{
	hook(mlx);
	cast_rays(mlx);
	minimap(mlx);
	mlx->pl->is_near_door = check_for_door(mlx);
	if (mlx->pl->shoot)
		draw_shoot_animation(mlx, mlx->random_pass);
	else
		draw_main_img(mlx, 0, mlx->random_pass);
}

int	game_loop(void *ml)
{
	t_cub	*mlx;

	mlx = ml;
	if (mlx->pl->direction)
		modify_pass(&mlx->random_pass);
	if (mlx->pl->direction != NONE || mlx->pl->rot
		|| (mlx->pl->door && mlx->pl->is_near_door >= 2)
		|| mlx->pl->shoot)
		draw_image(mlx);
	mlx->pl->door = 0;
	return (0);
}

void	start_the_game(t_cub *mlx)
{
	mlx->textures->sprite = new_sprite(mlx);
	draw_image(mlx);
	mlx_mouse_hide(mlx->mlx_ptr, mlx->win_ptr);
	mlx_mouse_move(mlx->mlx_ptr, mlx->win_ptr, S_W / 2, S_H / 2);
	mlx_loop_hook(mlx->mlx_ptr, &game_loop, mlx);
	mlx_mouse_hook(mlx->win_ptr, mouse_click, mlx->pl);
	mlx_hook(mlx->win_ptr, 2, 1L << 0, read_keys, mlx);
	mlx_hook(mlx->win_ptr, 17, 0, exit_win, mlx->img);
	mlx_hook(mlx->win_ptr, 6, 1L << 6, mouse_move, mlx);
	mlx_loop(mlx->mlx_ptr);
	ft_exit(mlx);
}

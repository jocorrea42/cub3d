/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocorrea <jocorrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 10:01:55 by anyela            #+#    #+#             */
/*   Updated: 2024/03/16 14:07:33 by jocorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	mouse_move(int x, int y, void *param)
{
	t_cub	*mlx;

	(void)y;
	mlx = (t_cub *) param;
	if (x > S_W / 2)
		mlx->pl->rot = 1;
	else if (x < S_W / 2)
		mlx->pl->rot = -1;
	mlx->pl->mouse_rot = 1;
	mlx_mouse_move(mlx->mlx_ptr, mlx->win_ptr, S_W / 2, S_H / 2);
	return (0);
}

void	draw_potion(void *mlx, void *win, t_sprite *potion, int *key)
{
	potion->frame = (potion->frame + 1) % 8;
	if (*key == 1)
		mlx_put_image_to_window(mlx, win,
			potion->sprites[potion->frame], S_W / 2, S_H / 2);
	*key = 0;
}

void	centered_string(void *mlx, void *win, int color, char *string)
{
	int	size;
	int	x;
	int	y;

	size = ft_strlen(string);
	x = S_W / 2 - (size / 2) * 10;
	y = S_H - S_H / 8;
	mlx_string_put(mlx, win, x, y, color, string);
}

void	draw_image(t_cub *mlx)
{
	hook(mlx);
	cast_rays(mlx);
	minimap(mlx);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr,
		mlx->img->img_ptr, 0, 0);
	mlx->pl->is_near_door = check_for_door(mlx);
	if (mlx->pl->is_near_door == 2)
		centered_string(mlx->mlx_ptr, mlx->win_ptr,
			0xFFFFFF, "Press 'E' to close door");
	else if (mlx->pl->is_near_door == 3)
		centered_string(mlx->mlx_ptr, mlx->win_ptr,
			0xFFFFFF, "Press 'E' to open door");
}

int	game_loop(void *ml)
{
	t_cub	*mlx;

	mlx = ml;
	if (mlx->pl->direction != NONE || mlx->pl->rot
		|| (mlx->pl->door && mlx->pl->is_near_door >= 2)
		|| mlx->pl->potion == -1)
		draw_image(mlx);
	if (mlx->pl->potion)
		draw_potion(mlx->mlx_ptr, mlx->win_ptr,
			mlx->textures->potion, &mlx->pl->potion);
	mlx->pl->door = 0;
	return (0);
}

int	key_release(int key, void *param)
{
	t_player	*pl;

	printf("key release: %d\n", key);
	if (key != 12)
		return (0);
	pl = (t_player *)param;
	pl->potion = -1;
	return (0);
}

void	start_the_game(t_cub *mlx)
{
	mlx->textures->potion = new_sprite(mlx);
	draw_image(mlx);
	mlx_mouse_hide(mlx->mlx_ptr, mlx->win_ptr);
	mlx_mouse_move(mlx->mlx_ptr, mlx->win_ptr, S_W / 2, S_H / 2);
	mlx_loop_hook(mlx->mlx_ptr, &game_loop, mlx);
	mlx_hook(mlx->win_ptr, 2, 1L << 0, read_keys, mlx);
	mlx_hook(mlx->win_ptr, 17, 0, exit_win, mlx->img);
	mlx_hook(mlx->win_ptr, 6, 1L << 6, mouse_move, mlx);
	mlx_hook(mlx->win_ptr, 3, 1L << 1, key_release, mlx->pl);
	mlx_loop(mlx->mlx_ptr);
	ft_exit(mlx);
}

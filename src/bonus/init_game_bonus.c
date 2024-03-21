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
	mlx_mouse_move(mlx->win_ptr, S_W / 2, S_H / 2);
	return (0);
}

void	draw_image(t_cub *mlx)
{
	hook(mlx);
	cast_rays(mlx);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr,
		mlx->img->img_ptr, 0, 0);
}

int	game_loop(void *ml)
{
	t_cub	*mlx;

	mlx = ml;
	if (mlx->pl->direction != NONE || mlx->pl->rot)
		draw_image(mlx);
	return (0);
}

void	start_the_game(t_cub *mlx)
{
	draw_image(mlx);
	mlx_mouse_hide(mlx->mlx_ptr, mlx->win_ptr);
	mlx_mouse_move(mlx->win_ptr, S_W / 2, S_H / 2);
	mlx_loop_hook(mlx->mlx_ptr, &game_loop, mlx);
	mlx_hook(mlx->win_ptr, 2, 1L << 0, read_keys, mlx);
	mlx_hook(mlx->win_ptr, 17, 0, exit_win, mlx->img);
	mlx_hook(mlx->win_ptr, 6, 1L << 6, mouse_move, mlx);
	mlx_loop(mlx->mlx_ptr);
	ft_exit(mlx);
}

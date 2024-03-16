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
	mlx_loop_hook(mlx->mlx_ptr, &game_loop, mlx);
	mlx_hook(mlx->win_ptr, 2, 1L << 0, read_keys, mlx);
	mlx_hook(mlx->win_ptr, 17, 0, exit_win, mlx->img);
	mlx_loop(mlx->mlx_ptr);
	ft_exit(mlx);
}

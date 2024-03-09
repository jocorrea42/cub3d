/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyela <anyela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 10:01:55 by anyela            #+#    #+#             */
/*   Updated: 2024/03/06 12:57:24 by anyela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_argument(char *argv, t_cub *mlx) // init the data structure
{
	//char	**tmp;
	
	mlx->dt = safe_calloc(1, sizeof(t_data)); // init the data structure
	mlx->ply = safe_calloc(1, sizeof(t_player));
	mlx->ray = safe_calloc(1, sizeof(t_ray));
	mlx->img = new_program(S_W, S_H, "CUB3D");
	mlx->dt->map2d = ft_read(ft_open(argv));          // Change to input chars
	get_map_size(mlx->dt);
	check_valid_char(mlx->dt);
	//return (dt); // return the data structure
}

void	init_the_player(t_cub *mlx) // init the player structure
{
	mlx->ply->plyr_x = mlx->dt->p_x * TILE_SIZE + TILE_SIZE / 2;
		// player x position in pixels in the center of the tile
	mlx->ply->plyr_y = mlx->dt->p_y * TILE_SIZE + TILE_SIZE / 2;
		// player y position in pixels in the center of the tile
	mlx->ply->fov_rd = (FOV * PI) / 180;                       
		// field of view in radians
	mlx->ply->angle = mlx->dt->p_a;                              // player angle
																// the rest of the variables are initialized to zero by calloc
}

void	draw_image(t_cub *mlx)
{
	hook(mlx, 0, 0);                                                                    
		// hook the player
	cast_rays(mlx);                                                                     
		// cast the rays
	mlx_put_image_to_window(mlx->img->mlx_ptr, mlx->img->win_ptr,
		mlx->img->img_ptr, 0, 0); // put the image to the window
}

int	game_loop(void *ml) // game loop
{
	t_cub *mlx;

	mlx = ml;                                           
		// cast to the mlx structure
	if (mlx->ply->l_r || mlx->ply->u_d || mlx->ply->rot)
		// check if player moved. If not does not draw another image
		draw_image(mlx);
	return (0);
}

void	start_the_game(t_cub *mlx) // start the game
{
	mlx->textures->north = new_file_img("textures/north.xpm", mlx);
	mlx->textures->south = new_file_img("textures/south.xpm", mlx);
	mlx->textures->west = new_file_img("textures/west.xpm", mlx);
	mlx->textures->east = new_file_img("textures/east.xpm", mlx);
	mlx->textures->ceiling = 0x00BFFF;
	mlx->textures->floor = 0x3C302A;

	// mlx_put_image_to_window (mlx.tex.mlx_ptr, mlx.tex.win_ptr,mlx.tex.img_ptr, 0, 0);
	init_the_player(mlx); // init the player structure
	draw_image(mlx);
	mlx_loop_hook(mlx->img->mlx_ptr, &game_loop, mlx);
		// game loop continuously call a specified function to update the game state and render the frames.
	mlx_hook(mlx->img->win_ptr, 2, 1L << 0, read_keys, mlx);
	mlx_hook(mlx->img->win_ptr, 17, 0, exit_win, mlx->img);
	// printf("text.h=%d, text.w=%d\n", mlx.tex.h, mlx.tex.w);
	mlx_loop(mlx->img->mlx_ptr); // mlx loop
	ft_exit(mlx);             // exit the game
}

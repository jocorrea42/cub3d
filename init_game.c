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

t_data *init_argumet() // init the data structure
{
 t_data *dt = ft_calloc(1, sizeof(t_data)); // init the data structure
 dt->map2d = ft_calloc(10, sizeof(char *)); // init the map
 dt->map2d[0] = strdup("1111111111111111111111111"); //fill the map
 dt->map2d[1] = strdup("1000000000000000000100001");
 dt->map2d[2] = strdup("1001000000000P00000000001");
 dt->map2d[3] = strdup("1001000000000000001000001");
 dt->map2d[4] = strdup("1001000000000000001000001");
 dt->map2d[5] = strdup("1001000000100000001000001");
 dt->map2d[6] = strdup("1001000000000000001000001");
 dt->map2d[7] = strdup("1001000000001000001000001");
 dt->map2d[8] = strdup("1111111111111111111111111");
 dt->map2d[9] = NULL;
 dt->p_y = 3; // player y position in the map
 dt->p_x = 14; // player x position in the map
 dt->w_map = 25; // map width
 dt->h_map = 9; // map height
 return (dt); // return the data structure
}

void init_the_player(t_cub mlx) // init the player structure
{
 mlx.ply->plyr_x = mlx.dt->p_x * TILE_SIZE + TILE_SIZE / 2; // player x position in pixels in the center of the tile
 mlx.ply->plyr_y = mlx.dt->p_y * TILE_SIZE + TILE_SIZE / 2; // player y position in pixels in the center of the tile
 mlx.ply->fov_rd = (FOV * PI) / 180; // field of view in radians
 mlx.ply->angle = PI/2 + 0.5; // player angle
 //the rest of the variables are initialized to zero by calloc
}

void    draw_image(t_cub *mlx)
{
    mlx_destroy_image(mlx->img.mlx_ptr, mlx->img.img_ptr); // delete the image
    mlx->img.img_ptr = mlx_new_image(mlx->img.mlx_ptr, S_W, S_H); // create new image
    hook(mlx, 0, 0); // hook the player
    cast_rays(mlx); // cast the rays
    mlx_put_image_to_window(mlx->img.mlx_ptr, mlx->img.win_ptr, mlx->img.img_ptr, 0, 0); // put the image to the window
}

int game_loop(void *ml) // game loop
{
 t_cub *mlx;

 mlx = ml; // cast to the mlx structure
 if (mlx->ply->l_r || mlx->ply->u_d || mlx->ply->rot) // check if player moved. If not does not draw another image
    draw_image(mlx);
 return (0);
}

void start_the_game(t_data *dt) // start the game
{
 t_cub mlx;

 mlx.dt = dt; // init the mlx structure
 mlx.ply = calloc(1, sizeof(t_player)); // init the player structure i'm using calloc to initialize the variables to zero
 mlx.ray = calloc(1, sizeof(t_ray)); // init the ray structure
 mlx.img = new_program(S_W, S_H, "CUB3D");
 mlx.tex = new_file_img("redbrick.xpm", mlx.img);
 
 mlx_put_image_to_window (mlx.tex.mlx_ptr, mlx.tex.win_ptr, mlx.tex.img_ptr, 0, 0);
 init_the_player(mlx); // init the player structure
 draw_image(&mlx);
 mlx_loop_hook(mlx.img.mlx_ptr, &game_loop, &mlx); // game loop continuously call a specified function to update the game state and render the frames.
 mlx_hook(mlx.img.win_ptr, 2, 1L<<0, read_keys, &mlx);
 mlx_hook(mlx.img.win_ptr, 17, 0, exit_win, &mlx.img);
 printf("text.h=%d, text.w=%d\n", mlx.tex.h, mlx.tex.w);
 mlx_loop(mlx.img.mlx_ptr); // mlx loop
 ft_exit(&mlx); // exit the game
}

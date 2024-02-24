/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocorrea <jocorrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:13:53 by jocorrea          #+#    #+#             */
/*   Updated: 2024/02/24 17:48:20 by jocorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "./mlx/mlx.h"
# include "./libft/libft.h"
# include "./libft/get_next_line.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

#define PI 3.14159265
#define W 320

typedef struct s_player //the player structure
{
 int  plyr_x; // player x position in pixels
 int  plyr_y; // player y position in pixels
 double angle; // player angle
 float fov_rd; // field of view in radians
 int  rot; // rotation flag
 int  l_r; // left right flag
 int  u_d; // up down flag
} t_player;

typedef struct s_ray //the ray structure
{
 double ray_ngl; // ray angle
 double distance; // distance to the wall
 int  flag;  // flag for the wall
} t_ray;

typedef struct s_data //the data structure
{
 char **map2d; // the map
 int  p_x;  // player x position in the map
 int  p_y;  // player y position in the map
 int  w_map;  // map width
 int  h_map;  // map height
} t_data;

typedef struct s_img
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		h;
	int		w;
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		endian;
	int		l_len;
}		t_img;

typedef struct s_cub //the mlx structure
{
 t_img   img; // the image
 t_ray   *ray; // the ray structure
 t_data   *dt; // the data structure
 t_player  *ply; // the player structure
} t_cub;

typedef struct s_square {
	 float	x;
	 float	y;
	unsigned short int	size;
	int					color;
}		t_square;

int			exit_win(t_img *window);
t_img 		new_program(int w, int h, char *str);
void		put_pixel_img(t_img img, int x, int y, int color);
void		draw_square(t_square square, t_img img);

#endif

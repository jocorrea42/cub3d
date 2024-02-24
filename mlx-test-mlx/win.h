/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocorrea <jocorrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 12:52:04 by jocorrea          #+#    #+#             */
/*   Updated: 2024/02/24 15:30:21 by jocorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WIN_H
# define WIN_H

# include "../mlx/mlx.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <math.h>

# define S_W 1900 // screen width
# define S_H 1000 // screen height
# define TILE_SIZE 30 // tile size
# define FOV 60 // field of view
# define ROTATION_SPEED 0.045 // rotation speed
# define PLAYER_SPEED 4 // player speed
# define PI 3.14159265
# define WIN 320

# define ESC 53   // key escape
# define ENTER 36 // key "enter"
# define FOLLOW 3 // key "f"
# define COLOR 8  // key "c"
# define UP 126   // key "arrow up"
# define DOWN 125 // key "arrow down"
# define PENGUIN 35 // key "p"
# define RAND_COLOR 15 // key "r"

typedef struct s_square {
	unsigned short int	x;
	unsigned short int	y;
	unsigned short int	size;
	int					color;
}		t_square;

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

typedef struct s_win
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		height;
	int		width;
}		t_win;

typedef struct s_img
{
	t_win	win;
	void	*img_ptr;
	char	*addr;
	int		h;
	int		w;
	int		bpp;
	int		endian;
	int		line_len;
}		t_img;

typedef struct s_mlx //the mlx structure
{
 t_img   img; // the image
 t_ray   *ray; // the ray structure
 t_data   *dt; // the data structure
 t_player  *ply; // the player structure
} t_mlx;

//windows and image handling
t_win		new_program(int w, int h, char *str);
int			gen_trgb(int opacity, int red, int green, int blue);
int			get_opacity(int trgb);
int			get_r(int trgb);
int			get_g(int trgb);
int			get_b(int trgb);
void		put_pixel_img_all(t_img img, int x, int y, int color);
void		put_pixel_img(t_img img, int x, int y, int color);
t_img		new_img(int w, int h, t_win window);
//hook
int	exit_win(t_win *window);
//draw
void	draw_square(t_square square, t_img img);
//key
int read_keys(int key_pressed, void *param);
int read_mouse(int button, int mouse_x, int mouse_y, void *param);
#endif

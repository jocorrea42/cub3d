/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyela <anyela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:13:53 by jocorrea          #+#    #+#             */
/*   Updated: 2024/03/06 12:34:40 by anyela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "./mlx/mlx.h"
# include "libft.h"
# include "./libft/get_next_line.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <fcntl.h>

# define PI 3.14159265
# define W 800
# define S_W 800				 // screen width
# define S_H 600				 // screen height
# define TILE_SIZE 64	 // tile size
# define FOV 70			 // field of view
# define ROTATION_SPEED 0.045 // rotation speed
# define PLAYER_SPEED 16		 // player speed
#define texWidth 64
#define texHeight 64
#define mapWidth 25
#define mapHeight 9


/*typedef struct s_tex
{
	mlx_texture_t	*no;
	mlx_texture_t	*so;
	mlx_texture_t	*we;
	mlx_texture_t	*ea;
}	t_tex;

typedef struct s_txtr
{
	char			*key;
	char			*value;
	struct s_txtr	*next;
}	t_txtr;
*/

typedef struct s_player // the player structure
{
	int		plyr_x;	  // player x position in pixels
	int		plyr_y;	  // player y position in pixels
	int		rot;	  // rotation flag
	int		l_r;	  // left right flag
	int		u_d;	  // up down flag
	double	angle; // player angle
	float	fov_rd; // field of view in radians

}			t_player;

typedef struct s_ray // the ray structure
{
	int		flag;		 // flag for the wall
	int		index;
	double	ray_angle;	 // ray angle
	double	distance; // distance to the wall
	double	horiz_x;
	double	horiz_y;
	double	vert_x;
	double	vert_y;
	
}			t_ray;

typedef struct s_data // the data structure
{
	int		p_x;	  // player x position in the map
	int		p_y;	  // player y position in the map
	int		w_map;	  // map width
	int		h_map;	  // map height
	char	**map2d; // the map

}			t_data;

typedef struct s_img
{
	int		h;
	int		w;
	int		bpp;
	int		endian;
	int		l_len;
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*addr;
}			t_img;

typedef struct s_cub // the mlx structure
{
	t_img		img;	   // the image
	t_ray		*ray;	   // the ray structure
	t_data		*dt;	   // the data structure
	t_player	*ply; // the player structure
    t_img		tex;
	//t_txtr		*l_ture;
}				t_cub;

typedef struct s_square
{
	int					color;
	float				x;
	float				y;
	unsigned short int	size;
	
} 						t_square;

int			exit_win(t_img *window);
t_img		new_program(int w, int h, char *str);
void		my_mlx_pixel_put(t_cub *cub, int x, int y, int color);
void		cast_rays(t_cub *mlx);
void		render_wall(t_cub *mlx, int ray);
float		nor_angle(float angle);
int			unit_circle(float angle, char c);
int			r_angle(int angle);
double		fcos(int angle);
void		hook(t_cub *mlx, double move_x, double move_y);
int			read_keys(int key_pressed, void *param);
void		ft_exit(t_cub *mlx);
int			exit_win(t_img *window);
void		move_player(t_cub *mlx, double move_x, double move_y);
void		rotate_player(t_cub *mlx, int i);
t_data		*init_argumet();
void		start_the_game(t_data *dt);

t_img			new_file_img(char * path, t_img window);
unsigned int	get_pixel_img(t_img img, int x, int y);
#endif

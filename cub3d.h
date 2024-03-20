/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocorrea <jocorrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:13:53 by jocorrea          #+#    #+#             */
/*   Updated: 2024/03/16 14:04:58 by jocorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# ifdef __linux__
#  include "./mlx_linux/mlx.h"
# elif __APPLE__
#  include "./mlx/mlx.h"
# else
#  error "OS not supported!"
# endif
# include "libft.h"
# include "./libft/get_next_line.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <fcntl.h>
# include <errno.h>

# define S_W			1920
# define S_H			1080
# define TILE_SIZE		64
# define FOV			60
# define COLLISION_FOV	4
# define ROTATION_SPEED	0.045
# define E	0
# define W	M_PI
# define S	M_PI_2
# define N	-M_PI_2

# define EXTENSION	".cub"
# ifdef BONUS
#  define VALID_CHAR	"0123 NEWS"
# else
#  define VALID_CHAR	"01 NEWS"
# endif

typedef enum e_dir
{
	NONE,
	UP,
	DOWN,
	LEFT,
	RIGHT
}	t_dir;

typedef struct s_player
{
	int		pl_x;
	int		pl_y;
	int		rot;
	t_dir	direction;
	double	angle;
	float	fov_rd;
	int		speed;
}	t_player;

typedef struct s_ray
{
	int		flag;
	int		index;
	double	ray_angle;
	double	distance;
	double	horiz_x;
	double	horiz_y;
	int		horiz_hit;
	double	vert_x;
	double	vert_y;
	int		vert_hit;
}	t_ray;

typedef struct s_data
{
	int		p_x;
	int		p_y;
	double	p_a;
	int		w_map;
	int		h_map;
	int		n_p;
	char	**map2d;
}	t_data;

typedef struct s_img
{
	int		h;
	int		w;
	int		bpp;
	int		endian;
	int		l_len;
	void	*img_ptr;
	char	*addr;
}	t_img;

typedef struct s_tex
{
	t_img	*north;
	t_img	*south;
	t_img	*west;
	t_img	*east;
	t_img	*door;
	int		*floor;
	int		*ceiling;
}	t_tex;

typedef struct s_cub
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		*img;
	t_ray		*ray;
	t_data		*dt;
	t_player	*pl;
	t_tex		*textures;
	int			*tile;
	int			hrz;
}	t_cub;

typedef struct s_square
{
	int					color;
	float				x;
	float				y;
	unsigned short int	size;
}	t_square;

t_img			*new_program(t_cub *mlx);
void			my_mlx_pixel_put(t_cub *cub, int x, int y, int color);
void			cast_rays(t_cub *mlx);
void			render_wall(t_cub *mlx, int ray);
float			nor_angle(float angle);
int				unit_circle(float angle, char c);
void			hook(t_cub *mlx);
int				read_keys(int key_pressed, void *param);
void			ft_exit(t_cub *mlx);
int				exit_win(void);
void			move_player(t_cub *mlx, double move_x, double move_y);
void			rotate_player(t_player *player);
void			general_move_player(t_cub *mlx);
void			start_the_game(t_cub *mlx);
unsigned int	get_pixel_img(t_img img, int x, int y);
/* Texture and color functions */
int				*create_new_color(char *path);
t_img			*new_file_img(char *path, t_cub *window);
int				is_textures_ok(t_tex *tex);
void			check_texture_input(char *line, t_cub *mlx);
void			invert_image_x(t_img *img);

/* Parsing functions */
int				ft_open(char *filename);
char			*ft_strcat(char *s1, char *s2, int clean_it);
char			**ft_read(int fd);
void			init_structs(t_cub *mlx);
void			parse_input(char *argv, t_cub *mlx);
void			get_map_size(t_data *map);
void			check_valid_char(t_data *data);
void			check_closed(t_cub *data);
void			create_square_map(char **tmp, t_data *dt);
char			**fake_split(char const *s, char c);
/* Errors functions */
void			ft_perror(int err, char *msg);
/* Safe allocation functions */
void			*safe_calloc(size_t count, size_t size);
char			*safe_strtrim(char const *s1, char const *set);
char			*safe_strdup(const char *s1);
char			*safe_substr(char const *s, unsigned int start, size_t len);
/* Utils functions */
char			*ft_strtok(char *input, const char *delim);
int				ft_strcmp(char *str1, char *str2);
void			clean_array(void *array);
void			print_array(char **arr);

float	get_v_inter(t_cub *mlx, float angl);
float	get_h_inter(t_cub *mlx, float angl);
int	cast_direction_ray(t_cub *mlx, int new_x, int new_y);
#endif

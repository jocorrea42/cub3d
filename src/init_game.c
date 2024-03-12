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

void	init_the_player(t_cub *mlx) // init the player structure
{
	mlx->ply->plyr_x = mlx->dt->p_x * TILE_SIZE + TILE_SIZE / 2;
		// player x position in pixels in the center of the tile
	mlx->ply->plyr_y = mlx->dt->p_y * TILE_SIZE + TILE_SIZE / 2;
		// player y position in pixels in the center of the tile
	mlx->ply->fov_rd = (FOV * M_PI) / 180;                       
		// field of view in radians
	mlx->ply->angle = mlx->dt->p_a;                              // player angle
																// the rest of the variables are initialized to zero by calloc
}

void print_array(char **arr) // DEBUG FUNCTION -> DELETE
{
	while (*arr)
	{
		printf("%s\n", *arr);
		arr++;
	}
}

void	init_structs(t_cub *mlx) // init the data structure
{
	mlx->dt = (t_data *) safe_calloc(1, sizeof(t_data)); // init the data structure
	mlx->ply = (t_player *) safe_calloc(1, sizeof(t_player));
	mlx->ray = (t_ray *)safe_calloc(1, sizeof(t_ray));
	mlx->textures = (t_tex *) safe_calloc (1, sizeof(t_tex));
	mlx->img = new_program(S_W, S_H, "CUB3D");
}

int		is_textures_ok(t_tex *tex)
{
	return (tex->ceiling && tex->floor && tex->north && tex->south && tex->west && tex->east);
}

void	add_texture(char *tok, char *info, t_cub *mlx)
{
	if (!ft_strcmp(tok, "NO") && !mlx->textures->north)
		mlx->textures->north = new_file_img(info, mlx);
	else if (!ft_strcmp(tok, "SO") && !mlx->textures->south)
		mlx->textures->south = new_file_img(info, mlx);
	else if (!ft_strcmp(tok, "WE") && !mlx->textures->west)
		mlx->textures->west = new_file_img(info, mlx);
	else if (!ft_strcmp(tok, "EA") && !mlx->textures->east)
		mlx->textures->east = new_file_img(info, mlx);
	else if (!ft_strcmp(tok, "C") && !mlx->textures->ceiling)
		mlx->textures->ceiling = create_new_color(info);
	else if (!ft_strcmp(tok, "F") && !mlx->textures->floor)
		mlx->textures->floor = create_new_color(info);
	else
		ft_perror(EINVAL, "Invalid texture/color identifier");
}

void	check_texture_input(char *line, t_cub *mlx) // Case  F      17,    38,     64 not works
{
	char *tok;
	char *info;
	char *rest;

	tok = ft_strtok(line, " "); // if tok C or F...
	info = ft_strtok(NULL, " ");
	rest = ft_strtok(NULL, " ");
	if (info == NULL || rest != NULL)
		ft_perror(EINVAL, "Invalid texture/color format");
	add_texture(tok, info, mlx);
}

void	create_square_map(char **tmp, t_data *dt)
{
	size_t	width;
	int		height;

	width = 0;
	height = 0;
	while (tmp[height])
	{
		if (tmp[height][0] == '\0')
			ft_perror(EINVAL, "Space between map");
		if (ft_strlen(tmp[height]) > width)
			width = ft_strlen(tmp[height]);
		height++;
	}
	dt->map2d = (char **) safe_calloc (height + 1, sizeof(char *));
	while (--height >= 0)
	{
		dt->map2d[height] = (char *) safe_calloc (1, sizeof(char) * (width + 1));
		ft_memset(dt->map2d[height], '0', width);
		ft_memcpy(dt->map2d[height], tmp[height], ft_strlen(tmp[height]));
	}
}
int	get_t(int trgb)
{
	return ((trgb >> 24) & 0xFF);
}

int	get_r(int trgb)
{
	return ((trgb >> 16) & 0xFF);
}

int	get_g(int trgb)
{
	return ((trgb >> 8) & 0xFF);
}

int	get_b(int trgb)
{
	return (trgb & 0xFF);
}



void	parse_input(char *argv, t_cub *mlx)
{
	char	**tmp;
	char	*line;
	int		i;

	(void)mlx;
	i = 0;
	tmp = ft_read(ft_open(argv)); // Currently read using split erases all empty lines. Change it?
	while (tmp[i] && !is_textures_ok(mlx->textures)) // loop until all textures are filled
	{
		line = ft_strtrim(tmp[i], " \n");
		if (line[0] != '\0')
			check_texture_input(line, mlx);
		free(line);
		i++;
	}
	printf("Floor: R - %d G - %d B - %d\n", get_r(mlx->textures->floor), get_g(mlx->textures->floor), get_b(mlx->textures->floor));
	printf("Ceiling: R - %d G - %d B - %d\n", get_r(mlx->textures->ceiling), get_g(mlx->textures->ceiling), get_b(mlx->textures->ceiling));
	if (!tmp[i])
		ft_perror(EINVAL, "No map");
	while (tmp[i] && tmp[i][0] == '\0')
		i++;
	create_square_map(tmp + i, mlx->dt);
	get_map_size(mlx->dt);
	check_valid_char(mlx->dt);
	check_closed(mlx);
	print_array(tmp);
	clean_array(tmp);
	init_the_player(mlx); // init the player structure
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
	draw_image(mlx);
	mlx_loop_hook(mlx->img->mlx_ptr, &game_loop, mlx);
	mlx_hook(mlx->img->win_ptr, 2, 1L << 0, read_keys, mlx);
	mlx_hook(mlx->img->win_ptr, 17, 0, exit_win, mlx->img);
	mlx_loop(mlx->img->mlx_ptr); // mlx loop
	ft_exit(mlx);             // exit the game
}

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

void	init_the_player(t_cub *mlx)
{
	mlx->ply->plyr_x = mlx->dt->p_x * *mlx->tile + *mlx->tile / 2;
	mlx->ply->plyr_y = mlx->dt->p_y * *mlx->tile + *mlx->tile / 2;
	mlx->ply->fov_rd = (FOV * M_PI) / 180;
	mlx->ply->angle = mlx->dt->p_a;
	mlx->ply->speed = *mlx->tile / 3;
}

void	print_array(char **arr) // DEBUG FUNCTION -> DELETE
{
	while (*arr)
	{
		printf("%s\n", *arr);
		arr++;
	}
}

void	init_structs(t_cub *mlx)
{
	mlx->dt = (t_data *)safe_calloc(1, sizeof(t_data));
	mlx->ply = (t_player *)safe_calloc(1, sizeof(t_player));
	mlx->ray = (t_ray *)safe_calloc(1, sizeof(t_ray));
	mlx->textures = (t_tex *)safe_calloc(1, sizeof(t_tex));
	mlx->tile = NULL;
	mlx->img = new_program(mlx);
}

int	is_textures_ok(t_tex *tex)
{
	return (tex->ceiling && tex->floor && tex->north && tex->south && tex->west
		&& tex->east);
}

void	add_texture(char *tok, char *info, t_cub *mlx)
{
	char	*tmp;

	if (!info)
		ft_perror(EINVAL, "Invalid texture - No path");
	tmp = ft_strtok(info, " ");
	if (!ft_strcmp(tok, "NO") && !mlx->textures->north)
		mlx->textures->north = new_file_img(tmp, mlx);
	else if (!ft_strcmp(tok, "SO") && !mlx->textures->south)
		mlx->textures->south = new_file_img(tmp, mlx);
	else if (!ft_strcmp(tok, "WE") && !mlx->textures->west)
		mlx->textures->west = new_file_img(tmp, mlx);
	else if (!ft_strcmp(tok, "EA") && !mlx->textures->east)
		mlx->textures->east = new_file_img(tmp, mlx);
	else
		ft_perror(EINVAL, "Invalid texture - Wrong identifier");
	if (ft_strtok(NULL, " "))
		ft_perror(EINVAL, "Invalid texture - Extra information in line");
}

void	add_color(char *tok, char *info, t_cub *mlx)
{
	if (!info)
		ft_perror(EINVAL, "Invalid color - No RGB");
	if (!ft_strcmp(tok, "C") && !mlx->textures->ceiling)
		mlx->textures->ceiling = create_new_color(info);
	else if (!ft_strcmp(tok, "F") && !mlx->textures->floor)
		mlx->textures->floor = create_new_color(info);
}

void	check_texture_input(char *line, t_cub *mlx)
{
	char	*tok;

	if (line[0] == '\0')
	{
		free(line);
		return ;
	}
	tok = ft_strtok(line, " ");
	if (!ft_strcmp(tok, "C") || !ft_strcmp(tok, "F"))
		add_color(tok, ft_strtok(NULL, "\0"), mlx);
	else
		add_texture(tok, ft_strtok(NULL, "\0"), mlx);
	free(line);
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
	dt->map2d = (char **)safe_calloc(height + 1, sizeof(char *));
	while (--height >= 0)
	{
		dt->map2d[height] = (char *)safe_calloc(1, sizeof(char) * (width + 1));
		ft_memset(dt->map2d[height], '0', width);
		ft_memcpy(dt->map2d[height], tmp[height], ft_strlen(tmp[height]));
	}
}

void	parse_input(char *argv, t_cub *mlx)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = ft_read(ft_open(argv));
	while (tmp[i] && !is_textures_ok(mlx->textures))
	{
		check_texture_input(safe_strtrim(tmp[i], " "), mlx);
		i++;
	}
	while (tmp[i] && tmp[i][0] == '\0')
		i++;
	if (!tmp[i])
		ft_perror(EINVAL, "No map");
	create_square_map(tmp + i, mlx->dt);
	clean_array(tmp);
	get_map_size(mlx->dt);
	check_valid_char(mlx->dt);
	check_closed(mlx);
	init_the_player(mlx);
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, S_W, S_H, "cub3D");
	if (!mlx->win_ptr)
		ft_perror(ENOMEM, "mlx new window failed");
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
	if (mlx->ply->direction != NONE || mlx->ply->rot)
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

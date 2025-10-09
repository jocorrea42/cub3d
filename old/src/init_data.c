/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocorrea <jocorrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 10:16:57 by lsulzbac          #+#    #+#             */
/*   Updated: 2024/03/23 15:18:38 by jocorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_the_player(t_cub *mlx)
{
	mlx->pl->pl_x = mlx->dt->p_x * *mlx->tile + *mlx->tile / 2;
	mlx->pl->pl_y = mlx->dt->p_y * *mlx->tile + *mlx->tile / 2;
	mlx->pl->fov_rd = (FOV * M_PI) / 180;
	mlx->pl->angle = mlx->dt->p_a;
	mlx->pl->speed = *mlx->tile / 3;
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

void	init_structs(t_cub *mlx)
{
	mlx->dt = (t_data *)safe_calloc(1, sizeof(t_data));
	mlx->pl = (t_player *)safe_calloc(1, sizeof(t_player));
	mlx->ray = (t_ray *)safe_calloc(1, sizeof(t_ray));
	mlx->textures = (t_tex *)safe_calloc(1, sizeof(t_tex));
	mlx->tile = NULL;
	mlx->img = new_program(mlx);
}

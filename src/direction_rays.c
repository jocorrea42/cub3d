#include "cub3d.h"

static double	get_initial_angle(t_cub *mlx)
{
	if (mlx->pl->direction == UP)
		return (mlx->pl->angle - mlx->pl->fov_rd / COLLISION_FOV);
	else if (mlx->pl->direction == LEFT)
		return (mlx->ray->ray_angle = mlx->pl->angle - M_PI / 2
			- mlx->pl->fov_rd / COLLISION_FOV);
	else if (mlx->pl->direction == RIGHT)
		return (mlx->ray->ray_angle = mlx->pl->angle + M_PI / 2
			- mlx->pl->fov_rd / COLLISION_FOV);
	else
		return (mlx->ray->ray_angle = mlx->pl->angle + M_PI
			- mlx->pl->fov_rd / COLLISION_FOV);
}

int	cast_direction_ray(t_cub *mlx, int new_x, int new_y)
{
	double	h_inter;
	double	v_inter;
	double	distance;
	int		i;

	i = 0;
	distance = sqrt(pow(mlx->pl->pl_x - new_x, 2)
			+ pow(mlx->pl->pl_y - new_y, 2));
	mlx->ray->ray_angle = get_initial_angle(mlx);
	while (i < 3)
	{
		h_inter = get_h_inter(mlx, nor_angle(mlx->ray->ray_angle));
		v_inter = get_v_inter(mlx, nor_angle(mlx->ray->ray_angle));
		if (v_inter <= h_inter && v_inter < distance)
			return (0);
		else if (h_inter < distance)
			return (0);
		i++;
		mlx->ray->ray_angle += mlx->pl->fov_rd / COLLISION_FOV;
	}
	return (1);
}

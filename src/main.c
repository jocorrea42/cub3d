/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocorrea <jocorrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 12:19:51 by jocorrea          #+#    #+#             */
/*   Updated: 2024/03/16 12:59:22 by jocorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_cub	mlx;

	ft_bzero(&mlx, sizeof(t_cub));
	if (argc != 2)
		ft_perror(EINVAL, "./cub3d [MAP.cub]");
	init_structs(&mlx);
	parse_input(argv[1], &mlx);
	start_the_game(&mlx);
	return (0);
}

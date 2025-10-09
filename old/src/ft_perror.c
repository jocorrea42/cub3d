/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 11:31:31 by lsulzbac          #+#    #+#             */
/*   Updated: 2023/08/14 11:31:33 by lsulzbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_perror(int err, char *msg)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	if (err)
		errno = err;
	perror(msg);
	exit(EXIT_FAILURE);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmuminov <nmuminov@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 13:10:31 by nmuminov          #+#    #+#             */
/*   Updated: 2023/05/25 16:35:42 by nmuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	fail(char *str)
{
	ft_putstr_fd(str, 1);
	exit(1);
}

void	read_map(int *map)
{
	char	buff[255];
	int 	fd;
	char	*res;

	res = NULL;
	fd = open(*map, O_RDONLY);
	int nbr = read(fd, buff, 255);
	while (nbr)
	{
		res = ft_strjoin(res, buff);
		nbr = read(fd, buff, 255);
	}
	close(fd);
	return (res);
}
int	main(void)
{
	void	*mlx_wind;
	void	*mlx;
	
	mlx = mlx_init();
	mlx_wind = mlx_new_window(mlx, 640, 640, "game");
	mlx_loop(mlx);
}

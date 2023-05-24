/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmuminov <nmuminov@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 13:10:31 by nmuminov          #+#    #+#             */
/*   Updated: 2023/05/24 16:38:53 by nmuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	fail(char *str)
{
	ft_putstr_fd(str, 1);
	exit(1);
}
/*int read_map(char *map)
{
    *map = open(, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR
			| S_IRGRP | S_IROTH);
    get_next_line  =       
}*/

int main(void)
{
	void	*img;
	void	*mlx;

	mlx = mlx_init()
    if (mlx == NULL)
    	fail("error mlx");
	img = mlx_new_image(mlx, 640, 640);
}
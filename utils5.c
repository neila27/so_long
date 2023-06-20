/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmuminov <nmuminov@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 13:10:31 by nmuminov          #+#    #+#             */
/*   Updated: 2023/06/20 17:43:09 by nmuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	put_image_windows_by_type(t_data *data, t_game type, int y, int x)
{
	if (type == FLOOR)
		mlx_put_image_to_window(data->mlx, data->mlx_win,
			data->asset.floor.image, x * TILE_SIZE, y * TILE_SIZE);
	else if (type == WALL)
		mlx_put_image_to_window(data->mlx, data->mlx_win,
			data->asset.wall.image, x * TILE_SIZE, y * TILE_SIZE);
	else if (data->map[y][x] == COIN)
	{
		mlx_put_image_to_window(data->mlx, data->mlx_win,
			data->asset.floor.image, x * TILE_SIZE, y * TILE_SIZE);
		mlx_put_image_to_window(data->mlx, data->mlx_win,
			data->asset.coin.image, x * TILE_SIZE, y * TILE_SIZE);
	}
	else if (data->map[y][x] == EXIT)
		mlx_put_image_to_window(data->mlx, data->mlx_win,
			data->asset.exit.image, x * TILE_SIZE, y * TILE_SIZE);
	else if (data->map[y][x] == PLAYER)
	{
		mlx_put_image_to_window(data->mlx, data->mlx_win,
			data->asset.floor.image, x * TILE_SIZE, y * TILE_SIZE);
		mlx_put_image_to_window(data->mlx, data->mlx_win,
			data->asset.player.image, x * TILE_SIZE, y * TILE_SIZE);
	}
}

void	print_map(t_data *data, int y_len, int x_len)
{
	int	y;
	int	x;

	y = 0;
	while (y < y_len)
	{
		x = 0;
		while (x < x_len)
		{
			put_image_windows_by_type(data, data->map[y][x], y, x);
			x++;
		}
		y++;
	}
}
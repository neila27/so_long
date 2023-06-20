/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmuminov <nmuminov@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 13:10:31 by nmuminov          #+#    #+#             */
/*   Updated: 2023/06/20 16:24:22 by nmuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	fridge(t_data *data, int y, int x)
{
	if (data->map[y][x] != EXIT)
		return (0);
	if (coin(data, data->y_lenm, data->x_lenm) == 0)
		kill_game(data);
	return (1);
}

int	up(t_data *data)
{
	int	avance;

	avance = 0;
	if (fridge(data, data->player_y - 1, data->player_x))
		return (0);
		data->map[data->player_y][data->player_x] = FLOOR;
		data->player_y--;
		data->map[data->player_y][data->player_x] = PLAYER;
	return (1);
}

int	down(t_data *data)
{
	if (fridge(data, data->player_y + 1, data->player_x))
		return (0);
		data->map[data->player_y][data->player_x] = FLOOR;
		data->player_y++;
		data->map[data->player_y][data->player_x] = PLAYER;
	return (1);
}

int	left(t_data *data)
{
	if (fridge(data, data->player_y, data->player_x - 1))
		return (0);
		data->map[data->player_y][data->player_x] = FLOOR;
		data->player_x--;
		data->map[data->player_y][data->player_x] = PLAYER;
	return (1);
}

int	right(t_data *data)
{
	if (fridge(data, data->player_y, data->player_x + 1))
		return (0);
		data->map[data->player_y][data->player_x] = FLOOR;
		data->player_x++;
		data->map[data->player_y][data->player_x] = PLAYER;
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmuminov <nmuminov@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 13:10:31 by nmuminov          #+#    #+#             */
/*   Updated: 2023/06/20 17:46:08 by nmuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_game	**parse(char *str, int x, int y, t_data *data)
{
	t_game	**res;
	int		z;
	int		i;

	res = ft_calloc(sizeof(t_game *), y);
	i = 0;
	while (i < y)
	{
		res[i] = ft_calloc(sizeof(t_game), x);
		z = 0;
		while (z < x)
		{
			if (*str == '0')
				res[i][z] = FLOOR;
			else if (*str == '1')
				res[i][z] = WALL;
			else if (*str == 'P')
			{
				res[i][z] = PLAYER;
				data->player_y = i;
				data->player_x = z;
			}
			else if (*str == 'C')
				res[i][z] = COIN;
			else if (*str == 'E')
				res[i][z] = EXIT;
			z++;
			str++;
		}
		str++;
		i++;
	}
	return (res);
}

void	floodfill(t_data *data, t_game **game, int x, int y)
{
	if (x > data->x_lenm || x < 0 || y < 0 || y > data->y_lenm
		|| game[y][x] == IS_ENTRY
		|| game[y][x] == WALL)
		return ;
	game[y][x] = IS_ENTRY;
	floodfill(game, data->x_lenm, data->y_lenm, x, y + 1);
	floodfill(game, data->x_lenm, data->y_lenm, x, y - 1);
	floodfill(game, data->x_lenm, data->y_lenm, x - 1, y);
	floodfill(game, data->x_lenm, data->y_lenm, x + 1, y);
}

t_game	**copy_map(t_game **map, int y_len, int x_len)
{
	t_game	**cpy;
	int		y;

	cpy = ft_calloc(sizeof(t_game *), y_len);
	y = 0;
	while (y < y_len)
	{
		cpy[y] = ft_calloc(sizeof(t_game), x_len);
		ft_memcpy(cpy[y], map[y], sizeof(t_game) * x_len);
		y++;
	}
	return (cpy);
}

int	correct_map(int argc, char **argv, t_data *data)
{
	t_game		**cpy;
	char		*str;

	if (argc != 2)
		fail("where is the map??\n");
	else if (reverse_strncmp(argv[1], ".ber", 4) != 0)
		fail("not a .ber map\n");
	str = read_map(argv[1]);
	calc_len(str, &data->x_lenm, &data->y_lenm);
	data->map = parse(str, data->x_lenm, data->y_lenm, data);
	free(str);
	if (wall_correct(data->map, data->y_lenm, data->x_lenm) == 1)
		fail("not enough walls\n");
	else if (only_one_element(data->map, data->x_lenm, data->y_lenm, PLAYER)
		|| only_one_element(data->map, data->x_lenm, data->y_lenm, EXIT) != 0)
		fail("more than 1 door/player\n");
	if (is_map_empty(data->map, data->y_lenm, data->x_lenm, COIN) <= 0)
		fail("no coin\n");
	cpy = copy_map(data->map, data->y_lenm, data->x_lenm);
	floodfill(cpy, data->x_lenm, data->y_lenm, data->player_x, data->player_y);
	if (is_map_empty(cpy, data->y_lenm, data->x_lenm, COIN) != 0
		|| is_map_empty(cpy, data->y_lenm, data->x_lenm, EXIT) != 0)
		fail("coin/door isn't accessible\n");
	free_map(cpy, data->y_lenm);
	return (0);
}

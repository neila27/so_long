/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmuminov <nmuminov@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 13:10:31 by nmuminov          #+#    #+#             */
/*   Updated: 2023/06/20 16:23:44 by nmuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	steps_counter(t_data *data)
{
	char	*tmp;

	tmp = ft_itoa(++data->cnt_step);
	ft_putstr_fd(tmp, 1);
	ft_putchar_fd('\n', 1);
	free (tmp);
}

int	keypad(int keypress, t_data *data)
{
	int		avance;

	avance = 0;
	if (keypress == KEY_W && data->map[data->player_y - 1]
		[data->player_x] != WALL && data->map[data->player_y - 1])
		avance = up(data);
	else if (keypress == KEY_S && data->map[data->player_y + 1]
		[data->player_x] != WALL && data->map[data->player_y + 1])
		avance = down(data);
	else if (keypress == KEY_A && data->map[data->player_y]
		[data->player_x - 1] != WALL && data->map[data->player_y])
		avance = left(data);
	else if (keypress == KEY_D && data->map[data->player_y]
		[data->player_x + 1] != WALL && data->map[data->player_y])
		avance = right(data);
	else if (keypress == 53)
		kill_game(data);
	if (avance)
		steps_counter(data);
	print_map(data, data->y_lenm, data->x_lenm);
	return (0);
}

int get_xpm(void *mlx, t_image *image, char *path_name)
{
	image->image = mlx_xpm_file_to_image(mlx, path_name, &image->x_len,
			&image->y_len);
	if (!image->image)
		return (1);
	return (0);
}

int	get_load_image(t_data *data)
{
	if (get_xpm(data->mlx, &data->asset.floor, "./assets/floor.xpm") != 0
		|| get_xpm(data->mlx, &data->asset.wall, "./assets/wall.xpm") != 0
		|| get_xpm(data->mlx, &data->asset.coin, "./assets/coin.xpm") != 0
		|| get_xpm(data->mlx, &data->asset.exit, "./assets/exit.xpm") != 0
		|| get_xpm(data->mlx, &data->asset.player, "./assets/player.xpm") != 0)
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	data.cnt_step = 0;
	data.mlx = mlx_init();
	if (data.mlx == NULL)
		fail("error init mlx");
	correct_map(argc, argv, &data);
	data.mlx_win = mlx_new_window(data.mlx, data.x_lenm * 64,
			data.y_lenm * 64, "so_long");
	if (data.mlx_win == NULL)
		fail("error window creation");
	mlx_hook(data.mlx_win, 2, 1L << 0, keypad, (void *)&data);
	mlx_hook(data.mlx_win, KEY_DESTROY, 1L << 0, kill_game(data), &data);
	get_load_image(&data);
	print_map(&data, data.y_lenm, data.x_lenm);
	mlx_loop(data.mlx);
	return (0);
}

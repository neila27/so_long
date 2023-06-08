/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Probook <Probook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 13:10:31 by nmuminov          #+#    #+#             */
/*   Updated: 2023/06/08 12:43:30 by Probook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	fail(char *str)
{
	ft_putstr_fd(str, 1);
	exit(1);
}

char *read_map(char *map)
{
	char	buff[255];
	int		fd;
	char	*res;

	res = NULL;
	fd = open(map, O_RDONLY);
	int nbr = read(fd, buff, 255);
	while (nbr)
	{
		res = ft_strjoin(res, buff);
		nbr = read(fd, buff, 255);
	}
	close(fd);
	return (res);
}

void calc_len(char *str, int *x, int *y)
{
	*x = 0;
	*y = 0;
	int tmp = 0;

	if (str == NULL)
		fail("the string is empty");
	while (str)
	{
		if (*str == '\n')
		{
			if (*x == 0)
				*x = tmp;
			else if (*x != tmp)
				fail("not rectan\n");
			(*y)++;
			tmp = 0;
		}
		else if (*str !=  '1' || *str != '0' || *str != 'E' || *str != 'C' || *str != 'P')
			fail("unknown char in the map\n");
		str++;
		tmp++;
	}
	(*y)++;
}

t_game **parse(char *str, int *x, int *y)
{
	t_game **res = ft_calloc(sizeof(t_game *), *y);
	int z;
	int i  = 0;
	while (i < *y)
	{
		res[i] = ft_calloc(sizeof(t_game), *x);
		z = 0;
		while(z < *x)
		{
			if (*str == '0')
				res[i][z] = FLOOR;
			else if (*str == '1')
				res[i][z] = WALL;
			else if (*str == 'P')
				res[i][z] = PLAYER;
			else if (*str == 'C')
				res[i][z] = COIN;
			else if (*str == 'E')
				res[i][z] = EXIT;	
			z++;
			str++;
		}
		i++;
	}
	return (res);
}

void floodfill(t_game **game, int x_len, int y_len, int x, int y)
{
	if (x > x_len  || x < 0 || y < 0 || y > y_len || game[y][x] == IS_ENTRY || game[y][x] == WALL)
		return ;
	game[y][x] = IS_ENTRY;
	floodfill(game, x_len, y_len, x, y + 1);
	floodfill(game, x_len, y_len, x, y - 1);
	floodfill(game, x_len, y_len, x - 1, y);
	floodfill(game, x_len, y_len, x + 1, y);
}

t_game **copy_map(t_game **map, int y_len, int x_len)
{
	t_game **cpy;
	int y;
	cpy = ft_calloc(sizeof(t_game *), y_len);
	y = 0;
	while (y < y_len)
	{
	
		cpy[y] = ft_calloc(sizeof(t_game *), x_len);
		ft_memcpy(cpy[y], map[y], x_len);
		y++;
	}
	return (cpy);
}

int	is_map_empty(t_game **map, int y_len, int x_len, t_game element)
{
	int x;
	int	y;
	int counter;

	x = 0;
	y = 0;
	counter = 0;
	while (x < x_len)
	{
		x = 0;
		while(y < y_len)
		{
			if (map[y][x] == element)
				counter ++;
			y++;
		}
		x++;
	}
	if (counter != 0)
			return (1);
	return (0);
}

int	wall_correct(t_game **map, int y_len, int x_len)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < x_len)
	{
		if (map[0][x] != WALL)
			return (1);
		if (map[y_len - 1][x] != WALL)
			return (1);
		x++;
	}
	while (y < y_len)
	{
		if (map[y][0] != WALL)
			return (1);
		if (map[y][x_len - 1] != WALL)
			return (1);
		y++;
	}
	return (0);
}

int only_one_element(t_game **map, int x_len, int y_len, t_game element)
{
	int x;
	int y;
	int counter;

	x = 0;
	y = 0;
	counter = 0;
	while (x < x_len)
	{
		y = 0;
		while(y < y_len)
		{
			if (map[y][x] == element)
				counter ++;
			y++;
		}
		x++;
	}
	if (counter != 1)
			return (1);
	return (0);
}

int	reverse_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = ft_strlen(s1) - 1;
	if (n == 0)
		return (0);
	while (s1[i] && s2[i] && n)
	{
		if (s1[i] != s2[i])
			break ;
		i--;
		n--;
	}
	return ((unsigned char) s1[i] - (unsigned char) s2[i]);
}

int correct_map(int argc, char **argv, t_game **map, int y_len, int x_len, int y, int x)
{
	t_game **cpy ;

	if (argc != 1)
		fail("more than 1 arg\n");
	else if (wall_correct(map, y_len, x_len) == 1)
		fail("not enough walls\n");
	else if (reverse_strncmp(argv[1], ".ber", 4) != 0)
		fail("not a .ber map\n");
	else if (only_one_element(map, x_len, y_len, PLAYER)
	|| only_one_element(map, x_len, y_len, EXIT) != 0)
		fail("more than 1 door/player\n");
	cpy = copy_map(map, y_len, x_len);
	floodfill(cpy, x_len, y_len, x, y);
	if (is_map_empty(cpy, y_len, x_len, COIN) != 0)
		fail("coin\n");
	else if (is_map_empty(cpy, y_len, x_len, EXIT) != 0)
		fail("exit\n");
	else if (is_map_empty(cpy,y_len, x_len, PLAYER) != 0)
		fail("player\n");
	return (0);
}

int	 get_xpm(void *mlx, t_image *image, char *path_name)
{
	image->image = mlx_xpm_file_to_image(mlx, path_name, &image->x_len, &image->y_len);
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
		fail("error while loading image\n");
	return (0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_len + x * (data->bits_pix / 8));
	*(unsigned int*)dst = color;
}

int	close_win(t_data *data);
{
	mlx_destroy_window(data->mlx, data->mlx_win);
	return (0);
}

int	main(void)
{
	t_data	data;
	t_data	tmp_img;

	data.mlx = mlx_init();
	if (data.mlx == NULL)
		fail("error init mlx");

	data.mlx_win = mlx_new_window(data.mlx, HEIGHT, WIDTH, "so_long");
	if (data.mlx_win == NULL)
		fail("error window creation");
	mlx_key_hook();
	data.image = mlx_new_image(data.mlx, HEIGHT, WIDTH); 
	data.addr = mlx_get_data_addr(data.image, &data.bits_pix, &data.line_len, &data.endian);

	tmp_img.image = get_load_image(&data);
	if (tmp_img.image == NULL)
		fail("error while loading image");
	
	tmp_img.addr = mlx_get_data_addr(tmp_img.image, &tmps_img.bits_pix, &tmp_img.line_len, &tmps_img.endian);

	my_mlx_pixel_put(tmp_img.image, 5, 5, 0x00FF0000);

	mlx_put_image_to_window(data.mlx, data.mlx_win, data.image, 0, 0);
	mlx_loop(data.mlx);

	mlx_destroy_image(data.mlx, tmp_img.image);	
	mlx_destroy_image(data.mlx, data.image);
	mlx_hook(data.mlx_win, ON_DESTROY, 0, close_win, &data);
	mlx_destroy(data.mlx);

	return (0);
}

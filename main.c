/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmuminov <nmuminov@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 13:10:31 by nmuminov          #+#    #+#             */
/*   Updated: 2023/06/16 16:21:55 by nmuminov         ###   ########.fr       */
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
	if (fd < 0)
		return (NULL);
	int nbr = read(fd, buff, 255);
	if (nbr <= 0)
	{
		close(fd);
		return (NULL);
	}
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
	while (*str)
	{
		if (*str == '\n')
		{
			if (*x == 0)
				*x = tmp;
			else if (*x != tmp)
				fail("not rectan\n");	
			(*y)++;
			tmp = -1;
		}
		else if (*str !=  '1' && *str != '0' && *str != 'E' && *str != 'C' && *str != 'P' && *str != '\n')
			fail("unknown char in the map\n");
		str++;
		tmp++;
	}
	(*y)++;
}

t_game **parse(char *str, int x, int y)
{
	t_game **res = ft_calloc(sizeof(t_game *), y);
	int z;
	int i  = 0;
	while (i < y)
	{
		res[i] = ft_calloc(sizeof(t_game), x);
		z = 0;
		while(z < x)
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
		str++;
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
	size_t	i1;
	size_t	i2;

	i1 = ft_strlen(s1) - 1;
	i2 = ft_strlen(s2) - 1;
	if (n == 0)
		return (0);
	while (i1 >= 0 && i2 >= 0 && n)
	{
		if (s1[i1] != s2[i2])
			break ;
		i1--;
		i2--;
		n--;
	}
	if (n == 0)
		return (0);
	return ((unsigned char) s1[i1] - (unsigned char) s2[i2]);
}


int correct_map(int argc, char **argv, t_data *data)
{
	t_game		**cpy;
	char		*str;

	if (argc != 2)
		fail("more than 1 arg\n");
	else if (reverse_strncmp(argv[1], ".ber", 4) != 0)
		fail("not a .ber map\n");
	str = read_map(argv[1]);
	calc_len(str, &data->x_lenm, &data->y_lenm);
	data->map = parse(str, data->x_lenm, data->y_lenm);
	if (wall_correct(data->map, data->y_lenm, data->x_lenm) == 1)
		fail("not enough walls\n");
	else if (only_one_element(data->map, data->x_lenm, data->y_lenm, PLAYER)
	|| only_one_element(data->map, data->x_lenm, data->y_lenm, EXIT) != 0)
		fail("more than 1 door/player\n");
	cpy = copy_map(data->map, data->y_lenm, data->x_lenm);
	floodfill(cpy, data->x_lenm, data->y_lenm, 0, 0);
	if (is_map_empty(cpy, data->y_lenm, data->x_lenm, COIN) != 0)
		fail("collect all the coins pls\n");
	return (0);
}

void print_map(t_data *data, int y_len, int x_len)
{
	int y;
	int x;

	y = 0;
	while (y < y_len)
	{
		x = 0;
		while (x < x_len)
		{
			if (data->map[y][x] == FLOOR)
				mlx_put_image_to_window(data->mlx, data->mlx_win, &data->asset.floor.image, x * TILE_SIZE, y * TILE_SIZE);
			else if (data->map[y][x] == WALL)
				mlx_put_image_to_window(data->mlx, data->mlx_win, data->asset.wall.image, x * TILE_SIZE, y * TILE_SIZE);
			else if (data->map[y][x] == COIN)
				mlx_put_image_to_window(data->mlx, data->mlx_win, &data->asset.coin.image, x * TILE_SIZE, y * TILE_SIZE);
			else if (data->map[y][x] == EXIT)
				mlx_put_image_to_window(data->mlx, data->mlx_win, &data->asset.exit.image, x * TILE_SIZE, y * TILE_SIZE);
			else if (data->map[y][x] == PLAYER)
				mlx_put_image_to_window(data->mlx, data->mlx_win, &data->asset.player.image, x * TILE_SIZE, y * TILE_SIZE);
			x++;
		}
		y++;
	}
}

/*keyhook fonction
{
	if (map[y][x] == COIN) press touche E ????????????????????????????????????????????
		map[x][y] == FLOOR
		// ausii le faire quand je touche x ou exit sur l'interface
}
void keypad(t_game )
{
   if (key == KEY_W)
		pla = player[y + 1][x];
    else if (key == KEY_S)
		player = player[y - 1][x];
    else if (key == KEY_A)
		player = player[y][x - 1];
    else if (key == KEY_D)
		player = player[y][x + 1];
	else if (key == E) ???????????????????????????????????????????????????????????????
return (0);
}*/

//game terminé quand player[][] == exit[][] 

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
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	data.mlx = mlx_init();
	if (data.mlx == NULL)
		fail("error init mlx");
	correct_map(argc, argv, &data);
	data.mlx_win = mlx_new_window(data.mlx, HEIGHT, WIDTH, "so_long");
	if (data.mlx_win == NULL)
		fail("error window creation");
	//mlx_hook(data.mlx_win, ON_DESTROY, 0, ???, &data);//pour X la fenetre
	//mlx_hook(data.mlx_win, )//pour exit 
	get_load_image(&data);
	print_map(&data, data.y_lenm, data.x_lenm);
	mlx_loop(data.mlx);
	//mlx_destroy_image(data.mlx, data.image);
	//mlx_destroy_window(data.mlx, data.mlx_win);
	return (0);
}

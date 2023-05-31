/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmuminov <nmuminov@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 13:10:31 by nmuminov          #+#    #+#             */
/*   Updated: 2023/05/31 16:34:41 by nmuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	fail(char *str)
{
	ft_putstr_fd(str, 1);
	exit(1);
}

char *read_map(int *map)
{
	char	buff[255];
	int		fd;
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

t_game **calc_len(char *str, int *x, int *y)
{
	int i = 0;
	*x = 0;
	*y = 0;
	int tmp = 0;

	if (str == NULL)
		return (NULL);
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
	else if (is_map_empty(cpy, y_len, x_len, COIN) != 0)
		fail("coin\n");
	else if (is_map_empty(cpy, y_len, x_len, EXIT) != 0)
		fail("exit\n");
	else if (is_map_empty(cpy,y_len, x_len, PLAYER) != 0)
		fail("player\n");
	return (0);
}

t_game **copy_map(t_game **map, int y_len, int x_len)
{
	t_game **cpy;
	int y;
	int x;
	cpy = ft_calloc(sizeof(t_game *), y_len);
	y = 0;
	while (y < y_len)
	{
	
		cpy[y] = ft_calloc(sizeof(t_game *), x_len);
		ft_memcpy(cpy[y], map[y], x);
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

int	 get_xpm(void *mlx, t_image *image, char *path_name)
{
	char a[2][3];
	image->image = (mlx, path_name, &image->x_len, &image->y_len);
	if (!image->image)
		return (1);
	return (0);
}

void	get_load_image(t_data *data)
{
	if (get_xpm(data->mlx, data->asset.floor, "./assets/floor.xpm"
	|| get_xpm(data->mlx, data->asset.wall, "./assets/wall.xpm"
	|| data->mlx, data->asset.coin, "./assets/coin.xpm" 
	|| data->mlx, data->asset.exit, "./assets/exit.xpm"
	|| data->mlx, data->asset.player, "./assets/player.xpm" != 0)
		fail("error while loading image\n");
}

void	image_adress(t_data *data)
{
	data->addr = mlx_get_data_addr(data.img, &data.bits_pix, &data.image.y_len,
								&img.endian);
}

void	my_mlx_pixel_put(t_data *data, int x, int y)
{
	char	*dst;

	dst = data->addr + (y * data->y_len + x * (data->bits_pix / 8));
	*(unsigned int*)dst = data.image.color;
}

int	main(void)
{
	t_data	data;

	data.mlx = mlx_init();
	data.mlx_win = mlx_new_window(mlx, 64, 64, "game");
	mlx_loop(mlx);
	get_load_image(&data);
	
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmuminov <nmuminov@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 13:10:31 by nmuminov          #+#    #+#             */
/*   Updated: 2023/05/30 16:33:29 by nmuminov         ###   ########.fr       */
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
			fail("smth is missing\n");
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
	//1. If node is not Inside return.
	if (x > x_len  || x < 0|| y > y_len || game[y][x] == IS_ENTRY || game[y][x] == WALL )
		return ;
	//2. Set the node
	game[y][x] = IS_ENTRY;
	//3. Perform Flood-fill one step to the south of node.
	floodfill(game, x_len, y_len, x, y + 1);
	//4. Perform Flood-fill one step to the north of node
	floodfill(game, x_len, y_len, x, y - 1);
	//5. Perform Flood-fill one step to the west of node
	floodfill(game, x_len, y_len, x - 1, y);
	//6. Perform Flood-fill one step to the east of node
	floodfill(game, x_len, y_len, x + 1, y);
}

int correct_map(t_game **map, int *y, int *x)
{
	if (argc != 1)
		exit(1);
	if (wall_correct() == 1)
		fail("not enough walls");
	if (reverse_strncmp(argv[1], ".ber", 4) != 0)
		fail();
	if (only_one_element(map, *x, *y, PLAYER)
	|| only_one_element(map, *x, *y, EXIT))
		fail();

	///befor flood fill copy map
	//copy
	//call floodfill()
	//verify correct map no coin no exit inside map (hola refais la meme que celle qui check 1 element mais pour 0 eleement pour voir si la map est termine lol)

	//all coin is accessible => flood fill
	else if ()
}

void	wall_correct(t_game **map, int y_len, int x_len)
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

int	main(void)
{
	void	*mlx_wind;
	void	*mlx;

	mlx = mlx_init();
	mlx_wind = mlx_new_window(mlx, 640, 640, "game");
	mlx_loop(mlx);
	
}

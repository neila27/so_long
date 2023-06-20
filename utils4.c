/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmuminov <nmuminov@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 13:10:31 by nmuminov          #+#    #+#             */
/*   Updated: 2023/06/20 16:34:37 by nmuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	kill_game(void *data)
{
	(void)data;
	exit (0);
	return (0);
}

void	fail(char *str)
{
	ft_putstr_fd(str, 1);
	exit(1);
}

char	*read_map(char *map)
{
	char	buff[255];
	int		fd;
	char	*res;
	int		nbr;

	res = NULL;
	fd = open(map, O_RDONLY);
	if (fd < 0)
		fail("can't open the file\n");
	nbr = read(fd, buff, 254);
	buff[nbr] = 0;
	if (nbr <= 0)
	{
		close(fd);
		return (NULL);
	}
	while (nbr)
	{
		res = ft_strjoin(res, buff);
		nbr = read(fd, buff, 254);
		buff[nbr] = 0;
	}
	close(fd);

	return (res);
}

void	calc_len(char *str, int *x, int *y)
{
	int	tmp;

	*x = 0;
	*y = 0;
	tmp = 0;
	if (str == NULL)
		fail("the string is empty\n");
	while (*str)
	{
		if (*str == '\n')
		{
			if (*x == 0)
				*x = tmp;
			else if (*x != tmp)
				fail("not rectangle\n");
			(*y)++;
			tmp = -1;
		}
		else if (*str != '1' && *str != '0' && *str != 'E' && *str != 'C'
			&& *str != 'P' && *str != '\n')
			fail("unknown char in the map\n");
		str++;
		tmp++;
	}
	(*y)++;
}

int	coin(t_data *data, int y_len, int x_len)
{
	int	x;
	int	y;
	int	nbr_coin;

	nbr_coin = 0;
	x = 0;
	while (x < x_len)
	{
		y = 0;
		while (y < y_len)
		{
			if (data->map[y][x] == COIN)
				nbr_coin ++;
			y++;
		}
		x++;
	}
	return (nbr_coin);
}

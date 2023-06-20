/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmuminov <nmuminov@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 13:10:31 by nmuminov          #+#    #+#             */
/*   Updated: 2023/06/20 15:38:18 by nmuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	is_map_empty(t_game **map, int y_len, int x_len, t_game element)
{
	int	x;
	int	y;
	int	counter;

	y = 0;
	counter = 0;
	while (y < y_len)
	{
		x = 0;
		while (x < x_len)
		{
			if (map[y][x] == element)
				counter ++;
			x++;
		}
		y++;
	}
	return (counter);
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

int	only_one_element(t_game **map, int x_len, int y_len, t_game element)
{
	int	x;
	int	y;
	int	counter;

	x = 0;
	counter = 0;
	while (x < x_len)
	{
		y = 0;
		while (y < y_len)
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

void	free_map(t_game **map, int y_len)
{
	int	y;

	y = 0;
	while (y < y_len)
	{
		free(map[y]);
		y++;
	}
	free (map);
}

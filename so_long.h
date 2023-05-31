/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmuminov <nmuminov@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 13:10:31 by nmuminov          #+#    #+#             */
/*   Updated: 2023/05/31 16:34:43 by nmuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/errno.h>
# include "libft.h"
# include "mlx.h"

typedef struct s_image {
	int		x_len;
	int		y_len;
	void	*image;
	int		color
} t_image;

typedef struct	s_asset {
	t_images	floor;
	t_images	wall;
	t_images	coin;
	t_images	exit;
	t_images	player;
} t_asset;

typedef struct s_data {
	void	*mlx;
	void	*mlx_win;
	t_asset	asset;
	t_image image;
	char *addr;
	int bits_pix;
	int	line_len;
	int endian;
}			t_data;

typedef enum e_game {
	FLOOR,
	WALL,
	COIN,
	EXIT,
	PLAYER,
	IS_ENTRY,
}	t_game;

#endif

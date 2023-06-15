/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Probook <Probook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 13:10:31 by nmuminov          #+#    #+#             */
/*   Updated: 2023/06/15 12:21:15 by Probook          ###   ########.fr       */
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

# define HEIGHT 1920 
# define WIDTH 1080
# define TILE_SIZE 64

typedef struct s_image {
	int		x_len;
	int		y_len;
	void	*image;
	int		color;
} t_image;

typedef struct	s_asset {
	t_image	floor;
	t_image	wall;
	t_image	coin;
	t_image	exit;
	t_image	player;
} t_asset;

typedef struct s_data {
	void	*mlx;
	void	*mlx_win;
	t_asset	asset;
	char	*addr;
	int		bits_pix;
	int		line_len;
	int		endian;
	void	*image;
}			t_data;

typedef enum e_game {
	FLOOR,
	WALL,
	COIN,
	EXIT,
	PLAYER,
	IS_ENTRY,
}	t_game;

typedef enum e_key {
	KEY_W,
	KEY_S,
	KEY_A,
	KEY_D,
	ON_DESTROY = 17,
}	t_key;

#endif

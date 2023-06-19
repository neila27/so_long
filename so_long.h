/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmuminov <nmuminov@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 13:10:31 by nmuminov          #+#    #+#             */
/*   Updated: 2023/06/19 17:21:59 by nmuminov         ###   ########.fr       */
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

typedef struct s_asset {
	t_image	floor;
	t_image	wall;
	t_image	coin;
	t_image	exit;
	t_image	player;
} t_asset;

typedef enum e_game {
	FLOOR,
	WALL,
	COIN,
	EXIT,
	PLAYER,
	IS_ENTRY,
}	t_game;

typedef struct s_data {
	void	*mlx;
	void	*mlx_win;
	t_asset	asset;
	char	*addr;
	int		bits_pix;
	int		line_len;
	int		endian;
	void	*image;
	int		player_x;
	int 	player_y;
	t_game	**map;
	int		x_lenm;
	int		y_lenm;
	int		cnt_step;

}			t_data;

typedef enum e_key {
	KEY_A = 0,
	KEY_S = 1,
	KEY_D = 2,
	KEY_W = 13,
	KEY_DESTROY = 17,
	KEY_ESCAPE = 53,
}	t_key;

#endif

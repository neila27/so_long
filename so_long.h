/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmuminov <nmuminov@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 13:10:31 by nmuminov          #+#    #+#             */
/*   Updated: 2023/06/20 16:53:43 by nmuminov         ###   ########.fr       */
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
}			t_image;

typedef struct s_asset {
	t_image	floor;
	t_image	wall;
	t_image	coin;
	t_image	exit;
	t_image	player;
}	t_asset;

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
	int		player_y;
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

int		is_map_empty(t_game **map, int y_len, int x_len, t_game element);
int		wall_correct(t_game **map, int y_len, int x_len);
int		only_one_element(t_game **map, int x_len, int y_len, t_game element);
int		reverse_strncmp(const char *s1, const char *s2, size_t n);
void	free_map(t_game **map, int y_len);

void	steps_counter(t_data *data);
int		keypad(int keypress, t_data *data);
int		get_xpm(void *mlx, t_image *image, char *path_name);
int		get_load_image(t_data *data);
int		main(int argc, char **argv);

int		fridge(t_data *data, int y, int x);
int		up(t_data *data);
int		down(t_data *data);
int		left(t_data *data);
int		right(t_data *data);

int		kill_game(void *data);
void	fail(char *str);
char	*read_map(char *map);
void	calc_len(char *str, int *x, int *y);
int		coin(t_data *data, int y_len, int x_len);

#endif

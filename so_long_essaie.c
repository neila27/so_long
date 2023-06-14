void	fail(char *str)
{
	ft_putstr_fd(str, 1);
	exit(1);
}

int move_player(t_data *data):
    if key == "w":
        data->player->y_len -= 1
    else if key == "s":
        player.y_len += 1
    else if key == "a":
        player.x_len -= 1
    else if key == "d":
        player.x_len += 1
    return (0);
// initialisation de l'asset a l'endroit de depart et mouvement 
void	w_key(t_mlx *mlx)
{
	if (mlx->player.pos[1] <= 0) 
	if (ft_check_wall(mlx, 'w') == 1)
	{
		mlx->assets.path = ft_strjoin("", "./assets/basic_stand_W.xpm");
		mlx->player.pos[1] -= 50;
		move_player(mlx);
	}
	else 
	{
		mlx_clear_window(mlx->mlx, mlx->win);
		ft_print_map(mlx);
		mlx->assets.path = ft_strjoin("", "./assets/basic_stand_W.xpm");
		mlx->assets.img = mlx_xpm_file_to_image(mlx->mlx, mlx->assets.path,
				&mlx->assets.width, &mlx->assets.height);
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->assets.img,
			mlx->player.pos[0], mlx->player.pos[1]);
		free(mlx->assets.path);
	}
}

void	a_key(t_mlx *mlx)
{
	if (mlx->player.pos[0] <= 0)
		return ;
	if (ft_check_wall(mlx, 'a') == 1)
	{
		mlx->assets.path = ft_strjoin("", "./assets/basic_stand_A.xpm");
		mlx->player.pos[0] -= 50;
		move_player(mlx);
	}
	else
	{
		mlx_clear_window(mlx->mlx, mlx->win);
		ft_print_map(mlx);
		mlx->assets.path = ft_strjoin("", "./assets/basic_stand_A.xpm");
		mlx->assets.img = mlx_xpm_file_to_image(mlx->mlx, mlx->assets.path,
				&mlx->assets.width, &mlx->assets.height);
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->assets.img,
			mlx->player.pos[0], mlx->player.pos[1]);
		free(mlx->assets.path);
	}
}

void	s_key(t_mlx *mlx)
{
	if (mlx->player.pos[1] >= (mlx->map.size_y * 50) - 50)
		return ;
	if (ft_check_wall(mlx, 's') == 1)
	{
		mlx->assets.path = ft_strjoin("", "./assets/basic_stand_S.xpm");
		mlx->player.pos[1] += 50;
		move_player(mlx);
	}
	else
	{
		mlx_clear_window(mlx->mlx, mlx->win);
		ft_print_map(mlx);
		mlx->assets.path = ft_strjoin("", "./assets/basic_stand_S.xpm");
		mlx->assets.img = mlx_xpm_file_to_image(mlx->mlx, mlx->assets.path,
				&mlx->assets.width, &mlx->assets.height);
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->assets.img,
			mlx->player.pos[0], mlx->player.pos[1]);
		free(mlx->assets.path);
	}
}

void	d_key(t_mlx *mlx)
{
	if (mlx->player.pos[0] >= (mlx->map.size_x * 50) - 50)
		return ;
	if (ft_check_wall(mlx, 'd') == 1)
	{
		mlx->assets.path = ft_strjoin("", "./assets/basic_stand_D.xpm");
		mlx->player.pos[0] += 50;
		move_player(mlx);
	}
	else
	{
		mlx_clear_window(mlx->mlx, mlx->win);
		ft_print_map(mlx);
		mlx->assets.path = ft_strjoin("", "./assets/basic_stand_D.xpm");
		mlx->assets.img = mlx_xpm_file_to_image(mlx->mlx, mlx->assets.path,
				&mlx->assets.width, &mlx->assets.height);
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->assets.img,
			mlx->player.pos[0], mlx->player.pos[1]);
		free(mlx->assets.path);
	}
}

void	put_to_coords(t_mlx *mlx, char *line)
{
	if (mlx->map.size_y <= 1)
	{
		mlx->map.coords = malloc(mlx->map.size_y * sizeof(char *));
		mlx->map.coords[0] = malloc(mlx->map.size_x * sizeof(char *));
		ft_copy_line(mlx, line, 0);
		free(line);
		return ;
	}
	mlx->map.coords = ft_copy_ptr(mlx);
	ft_copy_line(mlx, line, mlx->map.size_y - 1);
	free(line);
	return ;
}

int	ft_check_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '1' || line[i] == 'E' || line[i] == '0'
			|| line[i] == 'C' || line[i] == 'P' || line[i] == '\n'
			|| line[i] == 'V')
			i++;
		else
			return (0);
	}
	return (1);
}

int	ft_map_init(t_mlx *mlx)
{
	int		i;
	char	*line;

	i = 1;
	mlx->map.coords = NULL;
	mlx->map.size_y = 1;
	mlx->map.fd = open(mlx->map.path, O_RDONLY);
	line = get_next_line(mlx->map.fd);
	if (line != NULL)
		mlx->map.size_x = ft_strlen(line) - 1;
	while (i == 1)
	{
		if (line == NULL && mlx->map.size_y <= 2)
			return (ft_error_map(mlx, line));
		if (line == NULL && mlx->map.size_y > 2)
			return (1);
		if (ft_check_line(line) != 1)
			return (ft_error_map(mlx, line));
		put_to_coords(mlx, line);
		line = get_next_line(mlx->map.fd);
		mlx->map.size_y++;
	}
	close(mlx->map.fd);
	return (1);
}

int	ft_create_map(t_mlx *mlx) // creation de la map pas seulement innitialisation
{
	if (ft_map_init(mlx) != 1)
		return (0);
	mlx->map.size_y--;
	if (ft_check_map(mlx) != 1)
	{
		ft_putstr("Error\n");
		return (0);
	}
	if (ft_is_winnable(mlx) != 1)
	{
		ft_putstr("Error\n");
		return (0);
	}
	return (1);
}

int	ft_first_last(t_mlx *mlx)
{
	int	i;

	i = 0;
	while (i < mlx->map.size_x)
	{
		if (mlx->map.coords[0][i] != '1')
			return (0);
		if (mlx->map.coords[mlx->map.size_y - 1][i] != '1')
			return (0);
		i++;
	}
	return (1);
}

int	ft_check_middle(t_mlx *mlx)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while (i < mlx->map.size_y)
	{
		if (mlx->map.coords[i][0] != '1'
			|| mlx->map.coords[i][mlx->map.size_x - 1] != '1')
			return (0);
		i++;
	}
	return (1);
}

//permet de ckeck si 1 seul player + m.a.j de la position du player et initialisation de l'asset a cet endroit parce que le player se deplace 
int	ft_check_start(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (x < mlx->map.size_y)
	{
		x = 0;
		while (y < mlx->map.size_x)
		{
			if (mlx->map.coords[i][x] == 'P')
			{
				mlx->player.pos[0] = x * 50;
				mlx->player.pos[1] = y * 50;
				y++;
			}
		}
	}
	if (z == 1)
		return (1);
	return (0);
}

// trouve l'emplacement de l'asset et initialise sa position 
int	ft_check_end(t_mlx *mlx)
{
	int	i;
	int	x;
	int	z;

	i = 0;
	z = 0;
	while (++i < mlx->map.size_y - 1)
	{
		x = -1;
		while (++x < mlx->map.size_x)
		{
			if (mlx->map.coords[i][x] == 'E')
			{
				mlx->map.pos_end[0] = i; // voir si je devrais pas donner la position moi aussi ?
				mlx->map.pos_end[1] = x;
				z++;
			}
		}
	}
	if (z == 1)
		return (1);
	return (0);
}

int	ft_check_item(t_mlx *mlx)
{
	int	i;
	int	x;

	i = 0;
	mlx->map.nb_items = 0;
	while (++i < mlx->map.size_y - 1)
	{
		x = -1;
		while (++x < mlx->map.size_x)
		{
			if (mlx->map.coords[i][x] == 'C')
				mlx->map.nb_items++;
		}
	}
	mlx->map.get_items = 0;
	if (mlx->map.nb_items >= 1)
		return (1);
	return (0);
}

void	ft_copy_line(t_mlx *mlx, char *line, int index)
{
	int	i;

	i = 0;
	if (line == NULL)
		return ;
	while (i < mlx->map.size_x && line[i] != '\n' && line[i] != '\0')
	{
		mlx->map.coords[index][i] = line[i];
		i++;
	}
	mlx->map.coords[index][i] = '\0';
	return ;
}
copie de la map "cpy ptr"
char	**ft_copy_ptr(t_mlx *mlx)
{
	char	**new_tab;
	int		i;
	int		x;

	i = -1;
	new_tab = malloc(mlx->map.size_y * sizeof(char *));
	if (!new_tab)
		return (0);
	while (++i <= mlx->map.size_y)
	{
		x = -1;
		new_tab[i] = malloc(mlx->map.size_x + 1 * sizeof(char *));
		if (!new_tab[i])
			return (0);
		if (i == mlx->map.size_y - 1)
		{
			free(mlx->map.coords);
			return (new_tab);
		}
		while (++x <= mlx->map.size_x && mlx->map.coords[i][x] != '\0')
			new_tab[i][x] = mlx->map.coords[i][x];
	}
	free(mlx->map.coords);
	return (new_tab);
}

int	ft_check_map(t_mlx *mlx)
{
	if (ft_first_last(mlx) != 1)
		return (0);
	if (ft_check_middle(mlx) != 1)
		return (0);
	if (ft_check_start(mlx) != 1)
		return (0);
	if (ft_check_end(mlx) != 1)
		return (0);
	if (ft_check_item(mlx) != 1)
		return (0);
	return (1);
}

int	keypress(int keycode, t_mlx *vars)
{
	if (keycode == 53)
		ft_exit(vars);
	else if (keycode == 13)
		w_key(vars);
	else if (keycode == 0)
		a_key(vars);
	else if (keycode == 1)
		s_key(vars);
	else if (keycode == 2)
		d_key(vars);
	return (0);
}

int	ft_check_x(t_mlx *mlx, char c)
{
	if (c == 'a')
	{
		if (mlx->map.coords[mlx->player.pos[1] / 50]
			[mlx->player.pos[0] / 50 - 1] != '1')
			return (1);
	}
	if (c == 'd')
	{
		if (mlx->map.coords[mlx->player.pos[1] / 50]
			[mlx->player.pos[0] / 50 + 1] != '1')
			return (1);
	}
	return (0);
}

int	ft_check_y(t_mlx *mlx, char c) //verifie si le deplacement est possible >>pk pas utiliser floodfile ??
{
	if (c == 'w')
	{
		if (mlx->map.coords[mlx->player.pos[1] / 50 - 1]
			[mlx->player.pos[0] / 50] != '1')
			return (1);
	}
	if (c == 's')
	{
		if (mlx->map.coords[mlx->player.pos[1] / 50 + 1]
			[mlx->player.pos[0] / 50] != '1')
			return (1);
	}
	return (0);
}

int	ft_check_wall(t_mlx *mlx, char c) //check si il peut avancer ou si c'est un mur >>floodfile???
{
	if (c == 'a')
	{
		if (ft_check_x(mlx, c) != 1)
			return (0);
	}
	else if (c == 'd')
	{
		if (ft_check_x(mlx, c) != 1)
			return (0);
	}
	else if (c == 'w')
	{
		if (ft_check_y(mlx, c) != 1)
			return (0);
	}
	else if (c == 's')
	{
		if (ft_check_y(mlx, c) != 1)
			return (0);
	}
	return (1);
}

int	ft_check_collect_item(t_mlx *mlx) //collecter les coin
{
	if (mlx->map.coords[mlx->player.pos[1] / 50]
		[mlx->player.pos[0] / 50] == 'C') //est ce que P est sur un C ?
	{
		mlx->map.get_items++;
		mlx->map.coords[mlx->player.pos[1] / 50]
		[mlx->player.pos[0] / 50] = '0'; //change la case en rien
		return (1);
	}
	return (0);
}

int	ft_move_check(t_mlx *mlx)
{
	if (ft_check_collect_item(mlx) == 1)
		return (0);
	if (mlx->map.coords[mlx->player.pos[1] / 50]
		[mlx->player.pos[0] / 50] == 'E'
		&& mlx->map.get_items == mlx->map.nb_items) //a pris tous les coins et est sur l'exit
	{
		mlx->assets.img = mlx_xpm_file_to_image(mlx->mlx, mlx->assets.path, //pk ici ? vrmt pas necessaire wsh
				&mlx->assets.width, &mlx->assets.height);
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->assets.img,
			mlx->player.pos[0], mlx->player.pos[1]);
		mlx->player.count++;
		return (1);
	}
	return (0);
}

void	ft_print_assets(t_mlx *mlx, int y, int x) // j'ai un equivalent mais a modifier ptt 
{
	mlx->assets.img = mlx_xpm_file_to_image(mlx->mlx, mlx->map.path,
			&mlx->assets.width, &mlx->assets.height);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->assets.img, x, y);
	free(mlx->map.path);
}

void	ft_print_spe(t_mlx *mlx, int y, int x) //pareil
{
	mlx->map.path = ft_strjoin("", "./assets/void_text.xpm");
	ft_print_assets(mlx, y, x);
}

void	ft_select_assets(t_mlx *mlx, int num_line, int c_pos) //associe les asset aux touches et aux fichiers et imprime selon taille pixel
{
	if (mlx->map.coords[num_line][c_pos] == '0') //toutes mes images son 64 donc moi je dois tout faire x64
		mlx->map.path = ft_strjoin("", "./assets/void_text.xpm");
	else if (mlx->map.coords[num_line][c_pos] == '1')
		mlx->map.path = ft_strjoin("", "./assets/wall_text.xpm");
	else if (mlx->map.coords[num_line][c_pos] == 'P')
	{
		ft_print_spe(mlx, num_line * 50, c_pos * 50);
		mlx->map.coords[num_line][c_pos] = '0';
		mlx->map.path = ft_strjoin("", "./assets/basic_stand_S.xpm");
	}
	else if (mlx->map.coords[num_line][c_pos] == 'E')
	{
		ft_print_spe(mlx, num_line * 50, c_pos * 50);
		mlx->map.path = ft_strjoin("", "./assets/exit_text.xpm");
	}
	else if (mlx->map.coords[num_line][c_pos] == 'C')
	{
		ft_print_spe(mlx, num_line * 50, c_pos * 50);
		mlx->map.path = ft_strjoin("", "./assets/collect_text.xpm");
	}
	else if (mlx->map.coords[num_line][c_pos] == 'V')
	{
		ft_print_spe(mlx, num_line * 50, c_pos * 50);
		mlx->map.path = ft_strjoin("", "./assets/enemy.xpm");
	}
}

int	ft_print_map(t_mlx *mlx) //jsp si j'ai une fonction qui print la map...
{
	int	i;
	int	x;

	i = 0;
	while (i < mlx->map.size_y)
	{
		x = 0;
		while (x < mlx->map.size_x)
		{
			ft_select_assets(mlx, i, x);
			ft_print_assets(mlx, i * 50, x * 50);
			x++;
		}
		i++;
	}
	return (1);
}

char	**ft_copy_floadfill(t_mlx *mlx) //simple copie de la map pour faire quoi??
{
	char	**new_tab;
	int		i;
	int		x;

	i = -1;
	new_tab = malloc(mlx->map.size_y * sizeof(char *));
	if (!new_tab)
		return (0);
	while (++i <= mlx->map.size_y)
	{
		x = -1;
		new_tab[i] = malloc(mlx->map.size_x * sizeof(char *));
		if (!new_tab[i])
			return (0);
		if (i == mlx->map.size_y - 1)
			return (new_tab);
		while (++x <= mlx->map.size_x)
			new_tab[i][x] = mlx->map.coords[i][x];
	}
	return (new_tab);
}


//algo mais jsp pk il l'utilise comme ca 
int	ft_check_element_map(t_mlx *mlx, char **tab, int y, int x)
{
	if (tab[y][x - 1] == '4') //lien avec floodfile ?? pk 4
	{
		mlx->map.get_items++;
		return (1);
	}
	else if (tab[y][x + 1] == '4')
	{
		mlx->map.get_items++;
		return (1);
	}
	else if (tab[y - 1][x] == '4')
	{
		mlx->map.get_items++;
		return (1);
	}
	else if (tab[y + 1][x] == '4')
	{
		mlx->map.get_items++;
		return (1);
	}
	return (0);
}

int	ft_check_floadfill(t_mlx *mlx, char **tab, int y, int x)
{
	(void) mlx;
	if (tab[y][x] == 'P')
		return (1);
	else if (tab[y][x] == 'C' || tab[y][x] == 'E')
		return (ft_check_element_map(mlx, tab, y, x));
	else if (tab[y][x - 1] == '4' && tab[y][x] == '0')
		return (1);
	else if (tab[y][x + 1] == '4' && tab[y][x] == '0')
		return (1);
	else if (tab[y - 1][x] == '4' && tab[y][x] == '0')
		return (1);
	else if (tab[y + 1][x] == '4' && tab[y][x] == '0')
		return (1);
	return (0);
}

void	ft_algo_check(t_mlx *mlx)
{
	int		x;
	int		y;
	char	**temp;

	temp = ft_copy_floadfill(mlx);
	x = 0;
	y = 0;
	while (++y < mlx->map.size_y - 1)
	{
		while (++x < mlx->map.size_x - 1)
		{
			if (ft_check_floadfill(mlx, temp, y, x) == 1)
			{
				temp[y][x] = '4';
				x = 1;
				y = 1;
			}
		}
		x = 0;
	}
	free(temp);
}

int	ft_is_winnable(t_mlx *mlx)
{
	int		tot;

	mlx->map.get_items = 0;
	tot = mlx->map.nb_items + 1; // tout collecté + la porte 
	ft_algo_check(mlx); //jouable 
	if (mlx->map.get_items == tot)
	{
		mlx->map.get_items = 0;
		return (1);
	}
	return (0);
}

void	ft_check_arg(int check, char *path, t_mlx *mlx)
{
	if (check != 2)
		ft_exit(mlx);
	mlx->map.path = path;
}

void	move_player(t_mlx *mlx) //c'est ici qu'il print osn image (au debut il l'a reinitialise wtf y'avais quoi dedans man)
{
	mlx_clear_window(mlx->mlx, mlx->win);
	if (ft_move_check(mlx) == 1)
		ft_exit(mlx);
	ft_print_map(mlx);
	mlx->assets.img = mlx_xpm_file_to_image(mlx->mlx, mlx->assets.path,
			&mlx->assets.width, &mlx->assets.height);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->assets.img,
		mlx->player.pos[0], mlx->player.pos[1]);
	free(mlx->assets.path);
	if (mlx->start == 1)
	{
		mlx->player.count++;
		ft_putstr("move: ");
		ft_putnbr(mlx->player.count); //compteur de mouvement que j'ai pas 
		ft_putstr("\n");
	}
}

int	main(int argc, char **argv)
{
	static t_mlx	mlx;
	int				i;
	int				x;

	i = 0;
	x = 0;
	mlx.start = 0;
	mlx.mlx = mlx_init();
	ft_check_arg(argc, argv[1], &mlx);
	mlx.assets.path = ft_strjoin("", "./assets/basic_stand_S.xpm"); //imprime tout
	if (ft_create_map(&mlx) != 1) // !!!!!!!!!!!!!!!!!!!!!
		return (ft_exit(&mlx));
	mlx.win = mlx_new_window(mlx.mlx, mlx.map.size_x * 50,
			mlx.map.size_y * 50, "so_long");
	if (ft_print_map(&mlx) != 1)
		return (ft_exit(&mlx));
	move_player(&mlx); // !!!!!!!!!!!!!!!!!!!!!
	mlx.start = 1; // !!!
	mlx_hook(mlx.win, 2, 1L << 0, keypress, &mlx);// important 
	mlx_hook(mlx.win, 17, 1L << 0, ft_exit, &mlx);// important
	mlx_loop(mlx.mlx);
	return (0);
}

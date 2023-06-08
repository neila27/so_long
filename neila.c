int	main(int argc, char **argv, t_game **map)
{
	t_data	data;

	correct_map(argc, argv, map, data.y_len, data.x_len);
    read_map(data.map);
    calc_len(argv[1], data.x_len, data.y_len);
    is_map_empty(map, data.y_len, data.x_len);
    wall_correct(map, data.y_len, data.x_len);
    data.mlx = mlx_init();
	if (data.mlx == NULL)
		fail("error init mlx");
	data.mlx_win = mlx_new_window(data.mlx, HEIGHT, WIDTH, "so_long");
	if (data.mlx_win == NULL)
		fail("error window creation");
	mlx_hook(data.mlx_win, ON_DESTROY, 0, close_win, &data);
    parse(argv[1], data.x_len, data.y_len);
	mlx_put_image_to_window(data.mlx, data.mlx_win, data.asset.coin.image, 0, 0);
    
	mlx_loop(data.mlx);

	mlx_destroy_window(data.mlx, data.mlx_win);
    mlx_destroy_image(data.mlx, data.image);

	return (0);
}
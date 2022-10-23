#include "cub3D.h"

_Bool	check_usage(int argc)
{
	if (argc != 2)
		return (false);
	return (true);
}

int	draw(t_scene *sc)
{
	ftmlx_fill_img(sc->canvas, (t_color) {255, 0, 0, 0});
	mlx_put_image_to_window(sc->ftmlx.mlx, sc->ftmlx.win, sc->canvas->img, 0, 0);
	return (0);
}

void	config_loop(t_scene *sc)
{
	t_mlx mlx;

	mlx = sc->ftmlx.mlx;
	mlx_loop_hook(mlx, &draw, sc);
}

int	main(int argc, char **argv)
{
	t_scene	sc;

	init_scene(&sc);
	if (!check_usage(argc))
	{
		clean_scene(&sc);
		print_error("wrong_user");
		return (1);
	}
	if (!parser(argv[1], &sc))
	{
		clean_scene(&sc);
		print_error("wrong_parser");
		return (1);
	}
	config_loop(&sc);
	mlx_loop(sc.ftmlx.mlx);
	clean_scene(&sc);
	return (0);
}

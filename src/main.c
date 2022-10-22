#include "cub3D.h"

_Bool	check_usage(int argc)
{
	if (argc != 2)
		return (false);
	return (true);
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
	return (0);
}
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

	if (!check_usage(argc))
	{
		ft_putstr_fd("wrong_user", STDERR_FILENO);
		return (1);
	}
	if (!parser(argv[1], &sc))
	{
		ft_putstr_fd("wrong_parser", STDERR_FILENO);
		return (1);
	}
	return (0);
}
#include "cub3D.h"

void	init_scene(t_scene *sc)
{
	*sc = (t_scene) {0};
	sc->player.pos = (t_fvec2){-1, -1};
}

_Bool	check_scene(t_scene *sc)
{
	if (sc->player.pos.x < 0 || sc->player.pos.y < 0)
	{
		ft_putstr_fd("check_scene: player not found\n", STDERR_FILENO);
		return (false);
	}
	if (!check_map(sc->map.data, sc->map.len))
	{
		ft_putstr_fd("check_scene: check_map failed\n", STDERR_FILENO);
		return (false);
	}

	return (true);
}
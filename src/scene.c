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
		print_error("check_scene: player not found");
		return (false);
	}
	if (!check_map(sc->map.data, sc->map.len))
	{
		print_error("check_scene: check_map failed");
		return (false);
	}
	return (true);
}
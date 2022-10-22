#include "cub3D.h"

//todo? check if map is not one part ?
static _Bool	check_hole(int **map, t_vec2 len, t_vec2 pos)
{
	if ((pos.x == 0 || pos.x == len.x - 1 || pos.y == 0 || pos.y == len.y -1)) //check if empty case is not at map len border
		return (false);
	if (map[pos.y][pos.x - 1] == -1 || map[pos.y][pos.x + 1] == -1
			|| map[pos.y - 1][pos.x] == -1 || map[pos.y + 1][pos.x] == -1) //check if empty case is adj to void (-1)
		return (false);
	return (true);
}

_Bool check_map(int **map, t_vec2 len)
{
	t_vec2	pos;

	pos = (t_vec2) {0};
	while (pos.y < len.y )
	{
		pos.x = 0;
		while (pos.x < len.x)
		{
			if (map[pos.y][pos.x] == 0)
			{
				if (!check_hole(map, len, pos))
				{
					ft_putstr_fd("check_hole\n", STDERR_FILENO);
					return (false);
				}
			}
			++pos.x;
		}
		++pos.y;
	}
	return (true);
}

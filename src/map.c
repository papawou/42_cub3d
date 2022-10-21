#include "cub3D.h"

static void	reset_map(t_int_2d map)
{
	t_vec2	map_i;

	map_i = (t_vec2) {0};
	while (map_i.y < map.len.y)
	{
		map_i.x = 0;
		while (map_i.x < map.len.x)
		{
			map.data[map_i.y][map_i.x] = -1;
			++map_i.x;
		}
		++map_i.y;
	}
}

int	**create_map(t_vec2 map_size)
{
	int	**map;
	int	i;

	if (map_size.y <= 0 || map_size.x <= 0)
	{
		ft_putstr_fd("create_map: map_size incorrect\n", STDERR_FILENO);
		return (false);
	}
	map = (int **)malloc(sizeof(int *) * map_size.y);
	if (map == NULL)
		return (NULL);
	i = 0;
	while (i < map_size.y)
	{
		map[i] = malloc(sizeof(int) * map_size.x);
		if (map[i] == NULL)
		{
			while (i--)
				free(map[i]);
			return (NULL);
		}
		++i;
	}
	//todo set map at -1
	reset_map((t_int_2d){.len= map_size, .data= map});
	return (map);
}
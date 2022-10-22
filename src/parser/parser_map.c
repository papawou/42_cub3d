#include "cub3D.h"

int	count_line_x_words(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
		++i;
	return (i);
}

t_vec2	parse_map_size(t_list *book)
{
	t_vec2	map_size;
	int			book_line_x;

	map_size = (t_vec2) {0, 0};
	while (book)
	{
		book_line_x = count_line_x_words(book->content);
		if (book_line_x > map_size.x)
			map_size.x = book_line_x;
		book = book->next;
		++map_size.y;
	}
	return (map_size);
}

_Bool	parse_player_pos(t_obj *player, t_vec2 map_pos, char dir)
{
	float	deg;

	player->pos = (t_fvec2) {map_pos.x + 0.5, map_pos.y + 0.5};
	if (dir == 'N')
		deg = 0;
	else if (dir == 'S')
		deg = 180;
	else if (dir == 'E')
		deg = -90;
	else if (dir == 'W')
		deg = 90;
	else
		return (false);
	player->rot = axisg_to_quat((t_axisg){0, 1, 0, deg});
	return (true);
}

_Bool	parse_map(t_int_2d map, t_obj *player, t_list *book)
{
	t_vec2	map_i;

	map_i = (t_vec2){0};
	while (book)
	{
		map_i.x = 0;
		while (((char *)book->content)[map_i.x] && ((char *)book->content)[map_i.x] != '\n')
		{
			if (((char *)book->content)[map_i.x] == '0')
				map.data[map_i.y][map_i.x] = 0;
			else if (((char *)book->content)[map_i.x] == '1')
				map.data[map_i.y][map_i.x] = 1;
			else if (((char *)book->content)[map_i.x] == ' ')
				map.data[map_i.y][map_i.x] = -1;
			else if (parse_player_pos(player, map_i, ((char *)book->content)[map_i.x]))
				map.data[map_i.y][map_i.x] = 0;
			else //unknown char
				return (false);
			++map_i.x;
		}
		book = book->next;
		++map_i.y;
	}
	return (true);
}
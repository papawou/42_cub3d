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

int	**gen_map(t_vec2 map_size)
{
	int	**map;
	int	i;

	map = (int **)malloc(sizeof(int *) * map_size.y);
	if (map == NULL)
		return (NULL);
	map[map_size.y] = NULL;
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
	return (map);
}
#include <fcntl.h>

#include "cub3D.h"

t_list	*get_parser_book(char *file_path)
{
	char	*line;
	t_list	*book;
	t_list	*tmp;
	int		fd;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("open failed\n", STDERR_FILENO);
		return (false);
	}
	line = NULL;
	book = NULL;
	tmp = NULL;
	line = get_next_line(fd);
	while (line)
	{
		tmp = ft_lstnew(line);
		if (tmp == NULL)
		{
			ft_putstr_fd("ft_lstnew failed\n", STDERR_FILENO);
			ft_lstclear(&book, free);
			return (NULL);
		}
		ft_lstadd_back(&book, tmp);
		line = get_next_line(fd);
	}
	return (book);
}

_Bool parser(char *file_path, t_scene *sc)
{
	t_list	*book;

	book = get_parser_book(file_path);
	if (book == NULL)
	{
		ft_putstr_fd("get_parser_book\n", STDERR_FILENO);
		return (false);
	}
	sc->map.len = parse_map_size(book);
	sc->map.data = create_map(sc->map.len);
	if (sc->map.data == NULL)
		return (false);
	if (!parse_map(sc->map, &sc->player, book))
	{
		ft_putstr_fd("parse_map\n", STDERR_FILENO);
		return (false);
	}
	if (!check_scene(sc))
	{
		ft_putstr_fd("check_scene\n", STDERR_FILENO);
		return (false);
	}
	return (true);
}
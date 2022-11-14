/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 23:35:48 by kmendes           #+#    #+#             */
/*   Updated: 2022/11/10 22:07:47 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>

#include "cub3D.h"

void	clean_parser(t_list	**book)
{
	ft_lstclear(book, free);
}

t_list	*get_parser_book(char *file_path)
{
	char	*line;
	t_list	*book;
	t_list	*tmp;
	int		fd;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
	{
		print_error("open failed");
		return (false);
	}
	book = NULL;
	line = get_next_line(fd);
	while (line)
	{
		tmp = ft_lstnew(line);
		if (tmp == NULL)
		{
			ft_lstclear(&book, free);
			return (NULL);
		}
		ft_lstadd_back(&book, tmp);
		line = get_next_line(fd);
	}
	return (book);
}

_Bool	parser(char *file_path, t_scene *sc)
{
	t_list	*book;

	book = get_parser_book(file_path);
	if (book == NULL)
		return (false);
	sc->map.len = parse_map_size(book);
	sc->map.data = create_map(sc->map.len);
	if (sc->map.data == NULL)
	{
		clean_parser(&book);
		return (false);
	}
	if (!parse_atlas(sc))
	{
		clean_parser(&book);
		return (false);
	}
	if (!parse_map(sc->map, &sc->player, book))
	{
		clean_parser(&book);
		return (false);
	}
	clean_parser(&book);
	if (!check_scene(sc))
		return (false);
	return (true);
}

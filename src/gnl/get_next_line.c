/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 04:31:24 by kmendes           #+#    #+#             */
/*   Updated: 2022/05/31 04:31:24 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	gnl_fill_buff(char *buf, char *cursor)
{
	size_t	i;

	i = 0;
	while (cursor && cursor[i])
	{
		buf[i] = cursor[i];
		++i;
	}
	buf[i] = 0;
}

static char	*gnl_gen_out(char *buf, t_page *entry_page, size_t out_size)
{
	char	*cursor_page;
	char	*out;
	size_t	i;

	if (out_size < 1)
		return (NULL);
	out = malloc(out_size + 1);
	if (out == NULL)
		gnl_exit_clean(E_CODE_CLEAN | E_CODE_RESET, NULL);
	out[out_size] = 0;
	i = 0;
	while (buf[i] && i < out_size)
	{
		out[i] = buf[i];
		++i;
	}
	if (entry_page)
	{
		cursor_page = gnl_cpyn_book(out + i, out_size - i, &entry_page);
		gnl_fill_buff(buf, cursor_page);
		free(entry_page);
	}
	else
		gnl_fill_buff(buf, buf + i);
	return (out);
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1] = "";
	t_page		*entry_page;
	char		*buf_cursor;
	size_t		size_test;

	if (fd < 0)
		return (NULL);
	entry_page = NULL;
	gnl_exit_clean(E_CODE_INIT, &entry_page);
	buf_cursor = gnl_ft_strchr(buf, '\n');
	if (*buf_cursor != '\n')
	{
		size_test = gnl_read_book(&entry_page, fd);
		return (gnl_gen_out(buf, entry_page, (buf_cursor - buf) + size_test));
	}
	else if (*buf_cursor)
		return (gnl_gen_out(buf, entry_page, buf_cursor - buf + 1));
	else
		return (NULL);
}

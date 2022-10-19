/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 13:33:33 by kmendes           #+#    #+#             */
/*   Updated: 2022/06/01 13:33:33 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <sys/types.h>
# include <stdlib.h>
# include <unistd.h>

# include "cub3D.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 255
# endif

typedef struct s_page
{
	char			buf[BUFFER_SIZE + 1];
	struct s_page	*next;
}	t_page;

char	*get_next_line(int fd);
char	*gnl_ft_strchr(const char *src, const char c);
size_t	gnl_read_book(t_page **page, const int fd);
char	*gnl_cpyn_book(char *out, size_t out_size, t_page **page);
void	gnl_exit_clean(int code, t_page **entry);

#endif
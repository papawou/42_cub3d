#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <mlx.h>
# include <math.h>
# include <stdbool.h>
# include <unistd.h>
# include <errno.h>

# include "libft.h"
# include "libftmlx.h"
# include "get_next_line.h"

# define E_CODE_RESET 1
# define E_CODE_INIT 2
# define E_CODE_CLEAN 4

typedef struct s_obj
{
	t_fvec3	pos;
	t_quat	rot;
}	t_obj;

typedef struct s_atlas
{
	t_color	floor;
	t_color	ceil;
	t_img	*text_no;
	t_img	*text_so;
	t_img	*text_we;
	t_img	*text_ea;
}	t_atlas;

typedef struct s_scene
{
	t_atlas	atlas;
	t_obj	player;
	int		**map;
	t_vec2	map_size;
}	t_scene;

//parser.c
_Bool		parser(char *file_path, t_scene *sc);
void		exit_clean_parser(void);
int			count_line_x_words(char *line);
t_vec2	parse_map_size(t_list *book);
int			**gen_map(t_vec2 map_size);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 23:28:01 by kmendes           #+#    #+#             */
/*   Updated: 2022/10/26 14:35:07 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

# define SCREEN_WIDTH 1280
# define SCREEN_HEIGHT 720

enum e_tile
{
	EMPTY = -1,
	GROUND = 0,
	WALL = 1
};

typedef struct s_obj
{
	t_fvec2	pos;
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

typedef struct s_int_2d
{
	t_vec2	len;
	int		**data;
}	t_int_2d;

typedef struct s_scene
{
	t_obj		player;
	t_int_2d	map;
	t_ftmlx		ftmlx;
	t_img		*canvas;
	t_img		*minimap;
	t_atlas		atlas;
}	t_scene;

//PARSER/*
//	parser.c
_Bool		parser(char *file_path, t_scene *sc);
//	parser_map.c
int			count_line_x_words(char *line);
t_vec2		parse_map_size(t_list *book); //faut fermer sa session :)
_Bool		parse_map(t_int_2d map, t_obj *player, t_list *book);
//	check_map.c
_Bool		check_map(int **map, t_vec2 len);
//	parser_clean.c
void		exit_clean_parser(void);

//map.c
int			**create_map(t_vec2 map_size);
void		clean_map(t_int_2d *map);
void		tostring_map(t_int_2d *map);

//scene.c
void		init_scene(t_scene *sc);
_Bool		check_scene(t_scene *sc);
void		clean_scene(t_scene *sc);

//format.c
void		print_error(char *str);

//controls.c
int			controls_listener(int keycode, t_scene *sc);

//player.c
void		move_player(t_scene *sc, t_fvec2 move);
void		rotate_player(t_scene *sc, t_quat rot);
t_fvec2		get_player_dir(t_scene *sc);

//GRAPHICS/*
//	minimap.c
void		render_minimap(t_scene *sc);
//	atlas.c
void		clean_atlas(t_mlx mlx, t_atlas *atlas);

//physics.c
void		raycast(t_scene *sc);

//minimap.c
void	debug_minimap(t_scene *sc);

#endif
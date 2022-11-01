/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   physics.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 15:43:42 by kmendes           #+#    #+#             */
/*   Updated: 2022/11/01 07:44:46 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

#define DEBUG_MAP_X 10
#define DEBUG_MAP_Y 10

static void	debug_physics_raycast(t_scene *sc)
{
	double			i_y, i_x;
	double			sx, sy;
	t_vec2			mouse_pos;
	t_fvec2			ray_dir, ray_start;
	t_vec2			step;
	t_vec2			curr_cell;
	double			trash;

	mlx_mouse_get_pos(sc->ftmlx.win, &mouse_pos.x, &mouse_pos.y);
	
	ray_dir = fvec2_norm(fvec2_minus((t_fvec2) {(float)mouse_pos.x / DEBUG_MAP_X, (float)mouse_pos.y / DEBUG_MAP_Y}, sc->player.pos));
	ray_start = (t_fvec2){sc->player.pos.x, sc->player.pos.y};
	sx = sqrt(1 + pow((double)ray_dir.y / ray_dir.x, 2));
	sy = sqrt(1 + pow((double)ray_dir.x / ray_dir.y, 2));
	step = (t_vec2){1, 1};
	curr_cell = (t_vec2) {(int)ray_start.x, (int)ray_start.y};
	
	if (ray_dir.x < 0)
	{
		i_x = modf(sc->player.pos.x, &trash);
		step.x = -1;
	}
	else
		i_x = 1 - modf(sc->player.pos.x, &trash);
	if (ray_dir.y < 0)
	{
		i_y = modf(sc->player.pos.y, &trash);
		step.y = -1;
	}
	else
		i_y = 1 - modf(sc->player.pos.y, &trash);
	
	
	while (0 <= curr_cell.x && curr_cell.x < sc->debug_physics.map.len.x &&
		0 <= curr_cell.y && curr_cell.y < sc->debug_physics.map.len.y &&
		sc->debug_physics.map.data[curr_cell.y][curr_cell.x] < 1)
	{
		if (i_x * sx < i_y * sy)
		{
			curr_cell.x += step.x;
			++i_x;
		}
		else
		{
			curr_cell.y += step.y;
			++i_y;
		}
	}
	
	{ //reset prev hit wall
		t_vec2		map_i;
		t_int_2d	*map = &sc->debug_physics.map;
		map_i = (t_vec2){0};
		while (map_i.y < map->len.y)
		{
			map_i.x = 0;
			while (map_i.x < map->len.x)
			{
				if (map->data[map_i.y][map_i.x] == 2)
					map->data[map_i.y][map_i.x] = 1;
				++map_i.x;
			}
			++map_i.y;
		}
	}
	
	sc->debug_physics.map.data[curr_cell.y][curr_cell.x] = 2;
}

int	debug_physics_mouse_hook(int button, int x, int y, t_scene *sc)
{
	if (x < 0 || x >= sc->canvas->width || y < 0 || y >= sc->canvas->height)
		return (0);
	if (button == XK_LMB)
		sc->debug_physics.map.data[y / DEBUG_MAP_Y][x / DEBUG_MAP_X] = 1;
	return (0);
}

int	debug_physics_controls_listener(int keycode, t_scene *sc)
{
	if (keycode == XK_LEFT)
		rotate_player(sc, axisg_to_quat((t_axisg){0, 1, 0, 1}));
	else if (keycode == XK_RIGHT)
		rotate_player(sc, axisg_to_quat((t_axisg){0, 1, 0, -1}));
	else if (keycode == XK_A)
		move_player(sc, (t_fvec2){-0.22, 0});
	else if (keycode == XK_D)
		move_player(sc, (t_fvec2){0.22, 0});
	else if (keycode == XK_W)
		move_player(sc, (t_fvec2){0, -0.22});
	else if (keycode == XK_S)
		move_player(sc, (t_fvec2){0, 0.22});
	else if (keycode == XK_SPACE)
	{
		t_vec2	mouse_pos;

		mlx_mouse_get_pos(sc->ftmlx.win, &mouse_pos.x, &mouse_pos.y);
		sc->debug_physics.map.data[mouse_pos.y][mouse_pos.x] = 1;
	}
	return (0);
}

static t_color	debug_physics_get_tile_color(t_scene *sc, t_fvec2 pos)
{
	enum e_tile	tile;

	if (pos.x < 0 || sc->debug_physics.map.len.x <= pos.x
		|| pos.y < 0 || sc->debug_physics.map.len.y <= pos.y)
		return ((t_color){255, 20, 147, 0});
	tile = sc->debug_physics.map.data[(int)pos.y][(int)pos.x];
	if (tile == EMPTY)
		return ((t_color){127, 127, 127, 0});
	else if (tile == GROUND)
		return ((t_color){0, 255, 0, 0});
	else if (tile == WALL)
		return ((t_color){210, 105, 30, 0});
	else if (tile == 2)
		return ((t_color){0, 0, 255, 0});
	return ((t_color){255, 20, 147, 0});
}

void	debug_physics_draw_map(t_scene *sc)
{
	t_vec2	map_i;
	
	map_i = (t_vec2) {0};
	while (map_i.y < sc->debug_physics.map.len.y)
	{
		map_i.x = 0;
		while (map_i.x < sc->debug_physics.map.len.x)
		{
			t_aabb box;

			box.a = (t_vec2) {map_i.x * DEBUG_MAP_X, map_i.y * DEBUG_MAP_Y};
			box.b = (t_vec2) {map_i.x * DEBUG_MAP_X + DEBUG_MAP_X - 1, map_i.y * DEBUG_MAP_Y + DEBUG_MAP_Y - 1};
			ftmlx_put_aabb(box, debug_physics_get_tile_color(sc, (t_fvec2){map_i.x, map_i.y}), sc->canvas);
			++map_i.x;
		}
		++map_i.y;
	}
}

void	debug_physics_draw_game(t_scene *sc)
{
	t_vec2	mouse_pos;

	mlx_mouse_get_pos(sc->ftmlx.win, &mouse_pos.x, &mouse_pos.y);
	ftmlx_put_circle((t_vec2){sc->player.pos.x * DEBUG_MAP_X, sc->player.pos.y * DEBUG_MAP_Y}, 2, (t_color) {255, 255, 0, 0}, sc->canvas);
	ftmlx_put_circle(mouse_pos, 3, (t_color) {0, 255, 255, 0}, sc->canvas);
	ftmlx_put_bresen_line((t_vec2){sc->player.pos.x * DEBUG_MAP_X, sc->player.pos.y * DEBUG_MAP_Y}, mouse_pos,
		(t_color[2]) {{255, 255, 255, 0}, {255, 255, 255, 0}}, sc->canvas);
	debug_physics_raycast(sc);
}

int	debug_physics_draw(t_scene *sc)
{
	ftmlx_fill_img(sc->canvas, (t_color){255, 0, 0, 0});
	debug_physics_draw_map(sc);
	debug_physics_draw_game(sc);
	mlx_put_image_to_window(sc->ftmlx.mlx, sc->ftmlx.win,
		sc->canvas->img, 0, 0);
	return (0);
}

void	init_debug_physics(t_scene *sc)
{
	sc->debug_physics.map.len = (t_vec2) {sc->canvas->width / DEBUG_MAP_X, sc->canvas->height / DEBUG_MAP_Y};
	
	sc->player.pos = (t_fvec2) {(SCREEN_WIDTH / 2) / DEBUG_MAP_X, (SCREEN_HEIGHT / 2) / DEBUG_MAP_Y};
	sc->debug_physics.map.data = create_map(sc->debug_physics.map.len);
	
	int x = 0;
	while (x < sc->debug_physics.map.len.x)
	{
		sc->debug_physics.map.data[0][x] = 1;
		sc->debug_physics.map.data[sc->debug_physics.map.len.y - 1][x] = 1;
		++x;
	}
	x = 0;
	while (x < sc->debug_physics.map.len.y)
	{
		sc->debug_physics.map.data[x][0] = 1;
		sc->debug_physics.map.data[x][sc->debug_physics.map.len.x - 1] = 1;
		++x;
	}
	x = 0;
	while (x < sc->debug_physics.map.len.x / 2)
	{
		sc->debug_physics.map.data[sc->debug_physics.map.len.y / 2][x] = 1;
		++x;
	}
	mlx_do_key_autorepeaton(sc->ftmlx.mlx);
	mlx_mouse_hook(sc->ftmlx.win, &debug_physics_mouse_hook, sc);
	mlx_key_hook(sc->ftmlx.win, &debug_physics_controls_listener, sc);
	mlx_loop_hook(sc->ftmlx.mlx, &debug_physics_draw, sc);
}


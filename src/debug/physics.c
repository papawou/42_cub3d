/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   physics.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 15:43:42 by kmendes           #+#    #+#             */
/*   Updated: 2022/11/01 12:12:37 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

#define DEBUG_MAP_X 10
#define DEBUG_MAP_Y 10

/*
static void	debug_physics_raycast_screen(t_scene *sc)
{
	t_vec2	mouse_pos;
	int			x;

	x = 0;
	mlx_mouse_get_pos(sc->ftmlx.win, &mouse_pos.x, &mouse_pos.y);
	
	t_fvec2 dir = fvec2_norm(fvec2_minus((t_fvec2) {(float)mouse_pos.x / DEBUG_MAP_X, (float)mouse_pos.y / DEBUG_MAP_Y}, sc->player.pos));
	t_quat rot = axisg_to_quat((t_axisg){0, 1, 0, rad_to_deg(atan2(dir.y, dir.x))});
	
	while (x < SCREEN_WIDTH)
	{
		float cam_x = 2 * ((double) x / SCREEN_WIDTH) - 1;
		t_fvec2 ray_dir;
		ray_dir.x = dir.x + plane.x * cam.x;
		ray_dir.y = dir.y + plane.y * cam.x;
		//debug_physics_raycast()
		++x;
	}
}
*/
static void	debug_physics_raycast(t_scene *sc)
{
	t_fvec2		s;
	t_fvec2		ray_dir, ray_dir_test;
	t_vec2		step;
	t_vec2		curr_cell;
	t_fvec2		d;
	int				side;
	t_vec2		mouse_pos;
	
	mlx_mouse_get_pos(sc->ftmlx.win, &mouse_pos.x, &mouse_pos.y);
	ray_dir_test = fvec2_norm(fvec2_minus((t_fvec2) {(float)mouse_pos.x / DEBUG_MAP_X, (float)mouse_pos.y / DEBUG_MAP_Y}, sc->player.pos));
	
	t_quat rot = axisg_to_quat((t_axisg){0, 0, 1, rad_to_deg(atan2(ray_dir_test.y, ray_dir_test.x))});
	t_fvec3 tmp = quat_mult_vec(rot, (t_fvec3){1, 0, 0});
	ray_dir = fvec2_norm((t_fvec2){tmp.x, tmp.y});
	
	if (ray_dir.x == 0)
		d.x = 1e30;
	else
		d.x = fabsf(1 / ray_dir.x);
	if (ray_dir.y == 0)
		d.y = 1e30;
	else
		d.y = fabsf(1 / ray_dir.y);
	step = (t_vec2){1, 1};
	curr_cell = (t_vec2){(int)sc->player.pos.x, (int)sc->player.pos.y};
	
	if (ray_dir.x < 0)
	{
		step.x = -1;
		s.x = (sc->player.pos.x - curr_cell.x) * d.x;
	}
	else
	{
		step.x = 1;
		s.x = (curr_cell.x + 1 - sc->player.pos.x) * d.x;
	}
	if (ray_dir.y < 0)
	{
		step.y = -1;
		s.y = (sc->player.pos.y - curr_cell.y) * d.y;
	}
	else
	{
		step.y = 1;
		s.y = (curr_cell.y + 1 - sc->player.pos.y) * d.y;
	}
	
	while (0 <= curr_cell.x && curr_cell.x < sc->debug_physics.map.len.x &&
		0 <= curr_cell.y && curr_cell.y < sc->debug_physics.map.len.y &&
		sc->debug_physics.map.data[curr_cell.y][curr_cell.x] < 1)
	{
		if (s.x < s.y)
		{
			s.x += d.x;
			curr_cell.x += step.x;
			side = 0;
		}
		else
		{
			s.y += d.y;
			curr_cell.y += step.y;
			side = 1;
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

#include <stdio.h>
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


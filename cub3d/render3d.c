/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 18:21:30 by hchorfi           #+#    #+#             */
/*   Updated: 2020/11/04 18:21:32 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_3d(int i)
{
	g_wall_3d.wal_3d_distance =
		g_ray[i].distance * cosf(g_ray[i].angle - g_player.rotation_angle);
	g_wall_3d.distance_pro_plan = (g_mlx_data.w_width / 2) / tan(FOV_ANGLE / 2);
	g_wall_3d.pro_wall_hie =
		(TILE_SIZE / g_wall_3d.wal_3d_distance) * g_wall_3d.distance_pro_plan;
	g_wall_3d.wall_strip_hie = (int)g_wall_3d.pro_wall_hie;
	g_wall_3d.wal_top =
		(g_mlx_data.w_height / 2) - (g_wall_3d.wall_strip_hie / 2);
	g_wall_3d.wal_top = g_wall_3d.wal_top < 0 ? 0 : g_wall_3d.wal_top;
	g_wall_3d.wal_bot =
		(g_mlx_data.w_height / 2) + (g_wall_3d.wall_strip_hie / 2);
	g_wall_3d.wal_bot = g_wall_3d.wal_bot > g_mlx_data.w_height
		? g_mlx_data.w_height : g_wall_3d.wal_bot;
}

void	draw_walls(int y, int i)
{
	int distance_from_top;

	distance_from_top =
		y + (g_wall_3d.wall_strip_hie / 2) - (g_mlx_data.w_height / 2);
	g_txt.y = (int)((distance_from_top * g_txt.tile)
		/ g_wall_3d.wall_strip_hie);
	if (g_ray[i].vertical_hit && g_ray[i].face_right)
		g_mlx_data.addr[i + y * g_mlx_data.w_width] =
			g_txt.txt[EA][g_txt.x + (g_txt.tile * g_txt.y)];
	else if (g_ray[i].vertical_hit && g_ray[i].face_left)
		g_mlx_data.addr[i + y * g_mlx_data.w_width] =
			g_txt.txt[WE][g_txt.x + (g_txt.tile * g_txt.y)];
	else if (!g_ray[i].vertical_hit && g_ray[i].face_up)
		g_mlx_data.addr[i + y * g_mlx_data.w_width] =
			g_txt.txt[NO][g_txt.x + (g_txt.tile * g_txt.y)];
	else if (!g_ray[i].vertical_hit && g_ray[i].face_down)
		g_mlx_data.addr[i + y * g_mlx_data.w_width] =
			g_txt.txt[SO][g_txt.x + (g_txt.tile * g_txt.y)];
}

void	render_3d_walls(int i, int y)
{
	while (i < g_mlx_data.w_width)
	{
		init_3d(i);
		g_txt.x = g_ray[i].vertical_hit == 1 ? fmod(g_ray[i].wall_hity,
			g_txt.tile) : fmod(g_ray[i].wall_hitx, g_txt.tile);
		y = 0;
		while (y < g_wall_3d.wal_top)
		{
			g_mlx_data.addr[i + (y * g_mlx_data.w_width)] = g_txt.hex_color[1];
			y++;
		}
		y = g_wall_3d.wal_top;
		while (y < g_wall_3d.wal_bot)
		{
			draw_walls(y, i);
			y++;
		}
		while (y < g_mlx_data.w_height)
		{
			g_mlx_data.addr[i + (y * g_mlx_data.w_width)] = g_txt.hex_color[0];
			y++;
		}
		i++;
	}
}

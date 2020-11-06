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
	wall_3d.wal_3d_distance =
		ray[i].distance * cosf(ray[i].angle - player.rotation_angle);
	wall_3d.distance_pro_plan = (mlx_data.w_width / 2) / tan(fov_angle / 2);
	wall_3d.pro_wall_hie =
		(tile_size / wall_3d.wal_3d_distance) * wall_3d.distance_pro_plan;
	wall_3d.wall_strip_hie = (int)wall_3d.pro_wall_hie;
	wall_3d.wal_top =
		(mlx_data.w_height / 2) - (wall_3d.wall_strip_hie / 2);
	wall_3d.wal_top = wall_3d.wal_top < 0 ? 0 : wall_3d.wal_top;
	wall_3d.wal_bot =
		(mlx_data.w_height / 2) + (wall_3d.wall_strip_hie / 2);
	wall_3d.wal_bot = wall_3d.wal_bot > mlx_data.w_height
		? mlx_data.w_height : wall_3d.wal_bot;
}

void	draw_walls(int y, int i)
{
	int distance_from_top;

	distance_from_top =
		y + (wall_3d.wall_strip_hie / 2) - (mlx_data.w_height / 2);
	txt.y = (int)((distance_from_top * txt.tile) / wall_3d.wall_strip_hie);
	if (ray[i].vertical_hit && ray[i].face_right)
		mlx_data.addr[i + y * mlx_data.w_width] =
			txt.txt[0][txt.x + (txt.tile * txt.y)];
	else if (ray[i].vertical_hit && ray[i].face_left)
		mlx_data.addr[i + y * mlx_data.w_width] =
			txt.txt[1][txt.x + (txt.tile * txt.y)];
	else if (!ray[i].vertical_hit && ray[i].face_up)
		mlx_data.addr[i + y * mlx_data.w_width] =
			txt.txt[2][txt.x + (txt.tile * txt.y)];
	else if (!ray[i].vertical_hit && ray[i].face_down)
		mlx_data.addr[i + y * mlx_data.w_width] =
			txt.txt[3][txt.x + (txt.tile * txt.y)];
}

void	render_3d_walls(int i, int y)
{
	while (i < mlx_data.w_width)
	{
		init_3d(i);
		txt.x = ray[i].vertical_hit == 1 ? fmod(ray[i].wall_hity, txt.tile)
			: fmod(ray[i].wall_hitx, txt.tile);
		y = 0;
		while (y < wall_3d.wal_top)
		{
			mlx_data.addr[i + y * mlx_data.w_width] = txt.hex_color[1];
			y++;
		}
		y = wall_3d.wal_top;
		while (y < wall_3d.wal_bot)
		{
			draw_walls(y, i);
			y++;
		}
		while (y < mlx_data.w_height)
		{
			mlx_data.addr[i + y * mlx_data.w_width] = txt.hex_color[0];
			y++;
		}
		i++;
	}
}

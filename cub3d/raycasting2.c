/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 13:57:01 by hchorfi           #+#    #+#             */
/*   Updated: 2020/11/03 13:57:02 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	ver_raycast_init(float ray_angle)
{
	g_data.found_ver_wal_hit = 0;
	g_data.ver_wal_hit_x = 0;
	g_data.ver_wal_hit_y = 0;
	g_data.ver_wal_content = 0;
	g_data.x_intercept = floor(g_player.x / TILE_SIZE) * TILE_SIZE;
	g_data.x_intercept += g_data.face_right ? TILE_SIZE : 0;
	g_data.y_intercept = g_player.y + (g_data.x_intercept - g_player.x)
						* tanf(ray_angle);
	g_data.x_step = TILE_SIZE;
	g_data.x_step *= g_data.face_left ? -1 : 1;
	g_data.y_step = TILE_SIZE * tanf(ray_angle);
	g_data.y_step *= (g_data.face_up && g_data.y_step > 0) ? -1 : 1;
	g_data.y_step *= (g_data.face_down && g_data.y_step < 0) ? -1 : 1;
	g_data.next_ver_touch_x = g_data.x_intercept;
	g_data.next_ver_touch_y = g_data.y_intercept;
	return (1);
}

int		wall_collision(float npx, float npy)
{
	if (npx < 0 || npx > g_map_info.width || npy < 0 || npy > g_map_info.height)
		return (1);
	g_map_info.x = floor(npx / TILE_SIZE);
	g_map_info.y = floor(npy / TILE_SIZE);
	if (g_map_info.lines[g_map_info.y][g_map_info.x] - '0' == 0)
		return (0);
	else
		return (1);
}

void	vertical_hit(void)
{
	while (g_data.next_ver_touch_x >= 0 && g_data.next_ver_touch_x
			<= g_map_info.width && g_data.next_ver_touch_y >= 0
			&& g_data.next_ver_touch_y <= g_map_info.height)
	{
		g_data.x_to_check =
			g_data.next_ver_touch_x + (g_data.face_left ? -1 : 0);
		g_data.y_to_check = g_data.next_ver_touch_y;
		if (wall_collision(g_data.x_to_check, g_data.y_to_check))
		{
			g_data.ver_wal_hit_x = g_data.next_ver_touch_x;
			g_data.ver_wal_hit_y = g_data.next_ver_touch_y;
			g_data.ver_wal_content =
				g_map_info.lines[(int)floor(g_data.y_to_check / TILE_SIZE)]
				[(int)floor(g_data.x_to_check / TILE_SIZE)] - '0';
			g_data.found_ver_wal_hit = 1;
			break ;
		}
		else
		{
			g_data.next_ver_touch_x += g_data.x_step;
			g_data.next_ver_touch_y += g_data.y_step;
		}
	}
	g_data.ver_hit_distance = g_data.found_ver_wal_hit ? dbpoints(g_player.x,
	g_player.y, g_data.ver_wal_hit_x, g_data.ver_wal_hit_y) : INT_MAX;
}

int		hor_raycast_init(float ray_angle)
{
	g_data.found_hor_wal_hit = 0;
	g_data.hor_wal_hit_x = 0;
	g_data.hor_wal_hit_y = 0;
	g_data.hor_wal_content = 0;
	g_data.y_intercept = floor(g_player.y / TILE_SIZE) * TILE_SIZE;
	g_data.y_intercept += g_data.face_down ? TILE_SIZE : 0;
	g_data.x_intercept = g_player.x + (g_data.y_intercept - g_player.y)
						/ tanf(ray_angle);
	g_data.y_step = TILE_SIZE;
	g_data.y_step *= g_data.face_up ? -1 : 1;
	g_data.x_step = TILE_SIZE / tanf(ray_angle);
	g_data.x_step *= (g_data.face_left && g_data.x_step > 0) ? -1 : 1;
	g_data.x_step *= (g_data.face_right && g_data.x_step < 0) ? -1 : 1;
	g_data.next_hor_touch_x = g_data.x_intercept;
	g_data.next_hor_touch_y = g_data.y_intercept;
	return (1);
}

void	horizontal_hit(void)
{
	while (g_data.next_hor_touch_x >= 0 && g_data.next_hor_touch_x <=
			g_map_info.width
			&& g_data.next_hor_touch_y >= 0 && g_data.next_hor_touch_y
			<= g_map_info.height)
	{
		g_data.x_to_check = g_data.next_hor_touch_x;
		g_data.y_to_check = g_data.next_hor_touch_y + (g_data.face_up ? -1 : 0);
		if (wall_collision(g_data.x_to_check, g_data.y_to_check))
		{
			g_data.hor_wal_hit_x = g_data.next_hor_touch_x;
			g_data.hor_wal_hit_y = g_data.next_hor_touch_y;
			g_data.hor_wal_content = g_map_info.lines
				[(int)floor(g_data.y_to_check / TILE_SIZE)]
				[(int)floor(g_data.x_to_check / TILE_SIZE)] - '0';
			g_data.found_hor_wal_hit = 1;
			break ;
		}
		else
		{
			g_data.next_hor_touch_x += g_data.x_step;
			g_data.next_hor_touch_y += g_data.y_step;
		}
	}
	g_data.hor_hit_distance = g_data.found_hor_wal_hit ? dbpoints(g_player.x,
	g_player.y, g_data.hor_wal_hit_x, g_data.hor_wal_hit_y) : INT_MAX;
}

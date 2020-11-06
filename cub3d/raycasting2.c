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
	data.found_ver_wal_hit = 0;
	data.ver_wal_hit_x = 0;
	data.ver_wal_hit_y = 0;
	data.ver_wal_content = 0;
	data.x_intercept = floor(player.x / tile_size) * tile_size;
	data.x_intercept += data.face_right ? tile_size : 0;
	data.y_intercept = player.y + (data.x_intercept - player.x)
						* tanf(ray_angle);
	data.x_step = tile_size;
	data.x_step *= data.face_left ? -1 : 1;
	data.y_step = tile_size * tanf(ray_angle);
	data.y_step *= (data.face_up && data.y_step > 0) ? -1 : 1;
	data.y_step *= (data.face_down && data.y_step < 0) ? -1 : 1;
	data.next_ver_touch_x = data.x_intercept;
	data.next_ver_touch_y = data.y_intercept;
	return (1);
}

void	vertical_hit(void)
{
	while (data.next_ver_touch_x >= 0 && data.next_ver_touch_x
			<= map_info.width && data.next_ver_touch_y >= 0
			&& data.next_ver_touch_y <= map_info.height)
	{
		data.x_to_check = data.next_ver_touch_x + (data.face_left ? -1 : 0);
		data.y_to_check = data.next_ver_touch_y;
		if (wall_collision(data.x_to_check, data.y_to_check))
		{
			data.ver_wal_hit_x = data.next_ver_touch_x;
			data.ver_wal_hit_y = data.next_ver_touch_y;
			data.ver_wal_content = map_info.lines[(int)floor(data.y_to_check
				/ tile_size)][(int)floor(data.x_to_check / tile_size)] - '0';
			data.found_ver_wal_hit = 1;
			break ;
		}
		else
		{
			data.next_ver_touch_x += data.x_step;
			data.next_ver_touch_y += data.y_step;
		}
	}
	data.ver_hit_distance = data.found_ver_wal_hit ? dbpoints (player.x, player.y, data.ver_wal_hit_x, data.ver_wal_hit_y)
		: INT_MAX;
}

int		hor_raycast_init(float ray_angle)
{
	data.found_hor_wal_hit = 0;
	data.hor_wal_hit_x = 0;
	data.hor_wal_hit_y = 0;
	data.hor_wal_content = 0;
	data.y_intercept = floor(player.y / tile_size) * tile_size;
	data.y_intercept += data.face_down ? tile_size : 0;
	data.x_intercept = player.x + (data.y_intercept - player.y)
						/ tanf(ray_angle);
	data.y_step = tile_size;
	data.y_step *= data.face_up ? -1 : 1;
	data.x_step = tile_size / tanf(ray_angle);
	data.x_step *= (data.face_left && data.x_step > 0) ? -1 : 1;
	data.x_step *= (data.face_right && data.x_step < 0) ? -1 : 1;
	data.next_hor_touch_x = data.x_intercept;
	data.next_hor_touch_y = data.y_intercept;
	return (1);
}

void	horizontal_hit(void)
{
	while (data.next_hor_touch_x >= 0 && data.next_hor_touch_x <= map_info.width
			&& data.next_hor_touch_y >= 0 && data.next_hor_touch_y
			<= map_info.height)
	{
		data.x_to_check = data.next_hor_touch_x;
		data.y_to_check = data.next_hor_touch_y + (data.face_up ? -1 : 0);
		if (wall_collision(data.x_to_check, data.y_to_check))
		{
			data.hor_wal_hit_x = data.next_hor_touch_x;
			data.hor_wal_hit_y = data.next_hor_touch_y;
			data.hor_wal_content = map_info.lines[(int)floor(data.y_to_check
				/ tile_size)][(int)floor(data.x_to_check / tile_size)] - '0';
			data.found_hor_wal_hit = 1;
			break ;
		}
		else
		{
			data.next_hor_touch_x += data.x_step;
			data.next_hor_touch_y += data.y_step;
		}
	}
	data.hor_hit_distance = data.found_hor_wal_hit ? dbpoints (player.x, player.y, data.hor_wal_hit_x, data.hor_wal_hit_y)
		: INT_MAX;
}

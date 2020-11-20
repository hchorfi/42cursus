/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 13:01:50 by hchorfi           #+#    #+#             */
/*   Updated: 2020/11/03 13:01:52 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		player_update(void)
{
	float npx;
	float npy;
	float n_angle;

	if (g_player.indentation != 0)
	{
		n_angle = g_player.rotation_angle - PI / 2;
		g_player.step = g_player.indentation * g_player.walk_speed;
		npx = g_player.x + cosf(n_angle) * (g_player.step * 5);
		npy = g_player.y + sinf(n_angle) * (g_player.step * 5);
		if (!(wall_collision(npx, npy)) && !(sprite_collision(npx, npy)))
			player_update2(n_angle);
	}
	else
	{
		g_player.rotation_angle += g_player.turn_direction
			* g_player.turn_speed;
		g_player.step = g_player.walk_direction * g_player.walk_speed;
		npx = g_player.x + cosf(g_player.rotation_angle) * (g_player.step);
		npy = g_player.y + sinf(g_player.rotation_angle) * (g_player.step);
		if (!(wall_collision(npx, npy)) && !(sprite_collision(npx, npy)))
			player_update2(g_player.rotation_angle);
	}
	return (0);
}

float	raycast_init(float ray_angle)
{
	ray_angle = normalize(ray_angle);
	g_data.face_down = ray_angle > 0 && ray_angle < PI;
	g_data.face_up = !g_data.face_down;
	g_data.face_right = ray_angle < 0.5 * PI || ray_angle > 1.5 * PI;
	g_data.face_left = !g_data.face_right;
	return (ray_angle);
}

int		stock_raycast_data(float ray_angle, int strip_id)
{
	g_ray[strip_id].face_down = g_data.face_down;
	g_ray[strip_id].face_up = g_data.face_up;
	g_ray[strip_id].face_left = g_data.face_left;
	g_ray[strip_id].face_right = g_data.face_right;
	g_ray[strip_id].angle = ray_angle;
	return (1);
}

void	cast_ray(float ray_angle, int strip_id)
{
	ray_angle = raycast_init(ray_angle);
	hor_raycast_init(ray_angle);
	horizontal_hit();
	ver_raycast_init(ray_angle);
	vertical_hit();
	if (g_data.ver_hit_distance < g_data.hor_hit_distance)
	{
		g_ray[strip_id].distance = g_data.ver_hit_distance;
		g_ray[strip_id].wall_hitx = g_data.ver_wal_hit_x;
		g_ray[strip_id].wall_hity = g_data.ver_wal_hit_y;
		g_ray[strip_id].wall_content = g_data.ver_wal_content;
		g_ray[strip_id].vertical_hit = 1;
	}
	else
	{
		g_ray[strip_id].distance = g_data.hor_hit_distance;
		g_ray[strip_id].wall_hitx = g_data.hor_wal_hit_x;
		g_ray[strip_id].wall_hity = g_data.hor_wal_hit_y;
		g_ray[strip_id].wall_content = g_data.hor_wal_content;
		g_ray[strip_id].vertical_hit = 0;
	}
	stock_raycast_data(ray_angle, strip_id);
}

void	cast_all_rays(void)
{
	float	ray_angle;
	int		strip_id;

	ray_angle = g_player.rotation_angle - (FOV_ANGLE / 2);
	strip_id = 0;
	while (strip_id < g_mlx_data.w_width)
	{
		cast_ray(ray_angle, strip_id);
		ray_angle += FOV_ANGLE / g_mlx_data.w_width;
		strip_id++;
	}
}

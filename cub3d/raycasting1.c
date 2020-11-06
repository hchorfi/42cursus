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

float	raycast_init(float ray_angle)
{
	ray_angle = normalize(ray_angle);
	data.face_down = ray_angle > 0 && ray_angle < PI;
	data.face_up = !data.face_down;
	data.face_right = ray_angle < 0.5 * PI || ray_angle > 1.5 * PI;
	data.face_left = !data.face_right;
	return (ray_angle);
}

int		stock_raycast_data(float ray_angle, int strip_id)
{
	ray[strip_id].face_down = data.face_down;
	ray[strip_id].face_up = data.face_up;
	ray[strip_id].face_left = data.face_left;
	ray[strip_id].face_right = data.face_right;
	ray[strip_id].angle = ray_angle;
	return (1);
}

void	cast_ray(float ray_angle, int strip_id)
{
	ray_angle = raycast_init(ray_angle);
	hor_raycast_init(ray_angle);
	horizontal_hit();
	ver_raycast_init(ray_angle);
	vertical_hit();
	if (data.ver_hit_distance < data.hor_hit_distance)
	{
		ray[strip_id].distance = data.ver_hit_distance;
		ray[strip_id].wall_hitx = data.ver_wal_hit_x;
		ray[strip_id].wall_hity = data.ver_wal_hit_y;
		ray[strip_id].wall_content = data.ver_wal_content;
		ray[strip_id].vertical_hit = 1;
	}
	else
	{
		ray[strip_id].distance = data.hor_hit_distance;
		ray[strip_id].wall_hitx = data.hor_wal_hit_x;
		ray[strip_id].wall_hity = data.hor_wal_hit_y;
		ray[strip_id].wall_content = data.hor_wal_content;
		ray[strip_id].vertical_hit = 0;
	}
	stock_raycast_data(ray_angle, strip_id);
}

void	cast_all_rays(void)
{
	float	ray_angle;
	int		strip_id;

	ray_angle = player.rotation_angle - (fov_angle / 2);
	strip_id = 0;
	while (strip_id < mlx_data.w_width)
	{
		cast_ray(ray_angle, strip_id);
		ray_angle += fov_angle / mlx_data.w_width;
		strip_id++;
	}
}

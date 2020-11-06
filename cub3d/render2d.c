/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render2d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 18:29:49 by hchorfi           #+#    #+#             */
/*   Updated: 2020/11/03 18:29:51 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_square(int square_i, int square_j, int square_color)
{
	int i;
	int j;

	j = 0;
	while (j < map_info.tile)
	{
		i = 0;
		while (i < map_info.tile)
		{
			my_mlx_pixel_put(
							((i + square_i) * minimap_sf),
							((j + square_j) * minimap_sf),
							square_color);
			i++;
		}
		j++;
	}
}

void	render_map(void)
{
	int i;
	int j;
	int square_i;
	int square_j;

	j = 0;
	square_i = 0;
	square_j = 0;
	while (j < map_info.rows)
	{
		i = 0;
		square_i = 0;
		while (i < map_info.cols)
		{
			if (map_info.lines[j][i] - '0' == 1)
				draw_square(square_i, square_j, 0xffffff);
			if (map_info.lines[j][i] - '0' == 0)
				draw_square(square_i, square_j, 0x000000);
			i++;
			square_i += map_info.tile;
		}
		j++;
		square_j += map_info.tile;
	}
}

void	render_all_rays(void)
{
	int	j;
	int i;
	int	k;

	j = 0;
	i = 0;
	k = 0;
	while (k < mlx_data.w_width)
	{
		while (j < ray[k].distance)
		{
			my_mlx_pixel_put(
						((player.x + (i * cosf(ray[k].angle))) * minimap_sf),
						((player.y + (j * sinf(ray[k].angle))) * minimap_sf),
						0xffff00);
			j++;
			i++;
		}
		k++;
		j = 0;
		i = 0;
	}
}

void	render_player(void)
{
	double	x1;
	double	y1;
	double	r;
	double	angle;
	double	minangle;

	r = (map_info.tile / 4) * minimap_sf;
	angle = 0;
	minangle = cos(1 - 1 / r);
	while (r > 0)
	{
		while (angle <= 360)
		{
			x1 = r * cos(angle);
			y1 = r * sin(angle);
			my_mlx_pixel_put(
							(((player.x) + x1) * minimap_sf),
							(((player.y) + y1) * minimap_sf),
							player.color);
			angle += minangle;
		}
		angle = 0;
		r--;
	}
}

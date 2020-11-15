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
	while (j < g_map_info.tile)
	{
		i = 0;
		while (i < g_map_info.tile)
		{
			my_mlx_pixel_put(
							((i + square_i) * MINIMAP_SF),
							((j + square_j) * MINIMAP_SF),
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
	while (j < g_map_info.rows)
	{
		i = 0;
		square_i = 0;
		while (i < g_map_info.cols)
		{
			if (g_map_info.lines[j][i] - '0' == 1)
				draw_square(square_i, square_j, 0xffffff);
			if (g_map_info.lines[j][i] - '0' == 0)
				draw_square(square_i, square_j, 0x000000);
			i++;
			square_i += g_map_info.tile;
		}
		j++;
		square_j += g_map_info.tile;
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
	while (k < g_mlx_data.w_width)
	{
		while (j < g_ray[k].distance)
		{
			my_mlx_pixel_put(
					((g_player.x + (i * cosf(g_ray[k].angle))) * MINIMAP_SF),
					((g_player.y + (j * sinf(g_ray[k].angle))) * MINIMAP_SF),
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

	r = (g_map_info.tile / 4) * MINIMAP_SF;
	angle = 0;
	minangle = cos(1 - 1 / r);
	while (r > 0)
	{
		while (angle <= 360)
		{
			x1 = r * cos(angle);
			y1 = r * sin(angle);
			my_mlx_pixel_put(
							(((g_player.x) + x1) * MINIMAP_SF),
							(((g_player.y) + y1) * MINIMAP_SF),
							g_player.color);
			angle += minangle;
		}
		angle = 0;
		r--;
	}
}

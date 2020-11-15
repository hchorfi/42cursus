/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 20:02:04 by hchorfi           #+#    #+#             */
/*   Updated: 2020/11/02 20:02:06 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		check_sprites_pos(char *c, int x, int y)
{
	*c = '0';
	g_sprite[g_sprite->count].col = x;
	g_sprite[g_sprite->count].row = y;
	g_sprite->count += 1;
	return (1);
}

int		set_sprites(void)
{
	int i;

	i = 0;
	while (i < g_sprite->count)
	{
		g_sprite[i].x = g_sprite[i].col * TILE_SIZE + (TILE_SIZE / 2);
		g_sprite[i].y = g_sprite[i].row * TILE_SIZE + (TILE_SIZE / 2);
		i++;
	}
	return (1);
}

void	draw_sprite(int index, double distance, double height, int color)
{
	int		i;
	int		j;
	int		y_txt;

	i = index;
	while (i <= index + height)
	{
		j = (g_mlx_data.w_height / 2) - (height / 2);
		j = j < 0 ? 0 : j;
		y_txt = 0;
		if (i >= 0 && i < g_mlx_data.w_width && distance < g_ray[i].distance)
		{
			while (j < ((g_mlx_data.w_height + height) / 2) - 1
				&& j < g_mlx_data.w_height)
			{
				color = g_txt.txt[4][(int)(y_txt / height * g_txt.tile) *
					g_txt.tile + (int)((i - index) / height * g_txt.tile)];
				if (color != 0x000000)
					g_mlx_data.addr[i + j * g_mlx_data.w_width] = color;
				j++;
				y_txt++;
			}
		}
		i++;
	}
}

void	sort_sprites(void)
{
	int			i;
	float		tmp;

	i = 0;
	while (i < g_sprite->count)
	{
		g_sprite[i].distence = dbpoints(g_sprite[i].x, g_sprite[i].y,
			g_player.x, g_player.y);
		if (i > 0)
		{
			if (g_sprite[i - 1].distence < g_sprite[i].distence)
			{
				tmp = g_sprite[i].distence;
				g_sprite[i].distence = g_sprite[i - 1].distence;
				g_sprite[i - 1].distence = g_sprite[i].distence;
				tmp = g_sprite[i].x;
				g_sprite[i].x = g_sprite[i - 1].x;
				g_sprite[i - 1].x = tmp;
				tmp = g_sprite[i].y;
				g_sprite[i].y = g_sprite[i - 1].y;
				g_sprite[i - 1].y = tmp;
			}
		}
		i++;
	}
}

void	render_sprite(void)
{
	int			i;

	i = 0;
	sort_sprites();
	while (i < g_sprite->count)
	{
		g_sprite[i].angle = atan2(g_sprite[i].y - g_player.y,
			g_sprite[i].x - g_player.x);
		if (g_ray[0].angle - g_sprite[i].angle > PI)
			g_sprite[i].angle = g_sprite[i].angle + 2 * PI;
		if (g_sprite[i].angle - g_ray[0].angle > PI)
			g_sprite[i].angle = g_sprite[i].angle - 2 * PI;
		g_sprite[i].height = (TILE_SIZE / g_sprite[i].distence) *
							g_wall_3d.distance_pro_plan;
		g_sprite[i].index = (g_sprite[i].angle - g_ray[0].angle)
			/ (FOV_ANGLE / g_mlx_data.w_width) - (g_sprite[i].height / 2);
		draw_sprite(g_sprite[i].index, g_sprite[i].distence,
			g_sprite[i].height, 0);
		i++;
	}
}

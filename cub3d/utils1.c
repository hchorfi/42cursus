/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 20:14:06 by hchorfi           #+#    #+#             */
/*   Updated: 2020/11/02 20:14:07 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	dbpoints(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

int		create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

float	normalize(float angle)
{
	angle = fmod(angle, 2 * PI);
	if (angle < 0)
	{
		angle = (2 * PI) + angle;
	}
	return (angle);
}

int		isalldigit(char *str)
{
	int		i;

	i = 0;
	while (i != -1 && str[i])
	{
		if (ft_isdigit(str[i]))
			i++;
		else
			i = -1;
	}
	if (i == -1)
		return (0);
	return (1);
}

void	init_val(void)
{
	g_player.color = 0xff0000;
	g_player.turn_direction = 0;
	g_player.walk_direction = 0;
	g_player.indentation = 0;
	g_player.walk_speed = 6;
	g_player.turn_speed = 4 * (PI / 180);
	g_map_info.rows = 0;
	g_map_info.cols = 0;
	g_map_info.check_ppose = 0;
	g_map_info.line_list = NULL;
	g_mlx_data.save = 0;
	g_txt.type = 0;
	g_txt.tile = 64;
	g_sprite->count = 0;
	g_key.r = 0;
	g_key.no = 0;
	g_key.so = 0;
	g_key.we = 0;
	g_key.ea = 0;
	g_key.c = 0;
	g_key.f = 0;
	g_key.s = 0;
}

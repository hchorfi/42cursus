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

int		check_sprite_txt(char *line)
{
	while (*line == ' ')
		line++;
	if (ft_strncmp(line, "S ", 2) == 0)
		txt.type = SP;
	else
		return (0);
	return (1);
}

int		stock_sprite_txt(char *line)
{
	char	**tab;
	int		len;

	tab = ft_split(line, ' ');
	len = 0;
	while (tab[len])
		len++;
	if (len == 2)
	{
		txt.file[txt.type] = ft_substr(tab[1], 0, ft_strlen(tab[1]));
		txt.type = -1;
	}
	else
		return (stock_errors(2));
	while(len > 0)
	{
		free(tab[len]);
		len--;
	}
	free(tab);
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
		j = (mlx_data.w_height / 2) - (height / 2);
		j = j < 0 ? 0 : j;
		y_txt = 0;
		if (i >= 0 && i < mlx_data.w_width && distance < ray[i].distance)
		{
			while (j < ((mlx_data.w_height + height) / 2)
						&& j <= mlx_data.w_height)
			{
				color = txt.txt[4][(int)(y_txt / height * txt.tile) * txt.tile +
					(int)((i - index) / height * txt.tile)];
				if (color != 0x000000)
					mlx_data.addr[i + j * mlx_data.w_width] = color;
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
	while (i < sprite->count)
	{
		sprite[i].distence = dbpoints(sprite[i].x, sprite[i].y, player.x, player.y);
		if (i > 0)
		{
			if (sprite[i - 1].distence < sprite[i].distence)
			{
				tmp = sprite[i].distence;
				sprite[i].distence = sprite[i - 1].distence;
				sprite[i - 1].distence = sprite[i].distence;
				tmp = sprite[i].x;
				sprite[i].x = sprite[i - 1].x;
				sprite[i - 1].x = tmp;
				tmp = sprite[i].y;
				sprite[i].y = sprite[i - 1].y;
				sprite[i - 1].y = tmp;
			}
		}
		i++;
	}
}

void	render_sprite(void)
{
	int			i;
	t_sprite	tmp;

	i = 0;
	sort_sprites();
	while (i < sprite->count)
	{
		sprite[i].angle = atan2(sprite[i].y - player.y, sprite[i].x - player.x);
		if (ray[0].angle - sprite[i].angle > PI)
			sprite[i].angle = sprite[i].angle + 2 * PI;
		if (sprite[i].angle - ray[0].angle > PI)
			sprite[i].angle = sprite[i].angle - 2 * PI;
		sprite[i].height = (tile_size / sprite[i].distence) *
							wall_3d.distance_pro_plan;
		sprite[i].index = (sprite[i].angle - ray[0].angle) /
						(fov_angle / mlx_data.w_width) - (sprite[i].height / 2);
		draw_sprite(sprite[i].index, sprite[i].distence, sprite[i].height, 0);
		i++;
	}
}

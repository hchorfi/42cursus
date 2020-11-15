/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readfile3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 13:10:20 by hchorfi           #+#    #+#             */
/*   Updated: 2020/11/08 13:10:21 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		set_player(void)
{
	if (g_map_info.check_ppose == 1)
	{
		if (g_mlx_data.w_width / g_map_info.cols < g_mlx_data.w_height /
			g_map_info.rows)
			g_map_info.tile = g_mlx_data.w_width / g_map_info.cols;
		else
			g_map_info.tile = g_mlx_data.w_height / g_map_info.rows;
		g_player.x = g_player.x * TILE_SIZE + (TILE_SIZE / 2);
		g_player.y = g_player.y * TILE_SIZE + (TILE_SIZE / 2);
	}
	else
		return (mapline_errors(4));
	return (1);
}

int		check_player_pos(char *c, int x, int y)
{
	if (g_map_info.check_ppose == 0)
	{
		if (*c == 'N')
			g_player.rotation_angle = (PI / 2) * 3;
		else if (*c == 'S')
			g_player.rotation_angle = (PI / 2) * 1;
		else if (*c == 'W')
			g_player.rotation_angle = (PI / 2) * 2;
		else
			g_player.rotation_angle = (PI / 2) * 4;
		*c = '0';
		g_player.x = x;
		g_player.y = y;
		g_map_info.check_ppose = 1;
		return (1);
	}
	return (0);
}

int		check_map_line(char *line, int check)
{
	int	i;

	i = 0;
	while (line[i])
	{
		while (line[i] == ' ')
			i++;
		if (char_chr(line[i], "NWSE"))
		{
			if (!(check = check_player_pos(&line[i], i, g_map_info.rows)))
				return (mapline_errors(1));
		}
		else if (char_chr(line[i], "2"))
		{
			if (!(check = check_sprites_pos(&line[i], i, g_map_info.rows)))
				return (mapline_errors(2));
		}
		else if (!(check = char_chr(line[i], "01")))
			return (mapline_errors(3));
		i++;
	}
	g_map_info.rows++;
	return (check);
}

int		stock_map_line(char *line)
{
	t_list	*new_list;
	int		line_len;

	line_len = ft_strlen(line);
	if (line_len > g_map_info.cols)
		g_map_info.cols = line_len;
	new_list = ft_lstnew(line);
	if (g_map_info.line_list == NULL)
		g_map_info.line_list = new_list;
	else
		ft_lstadd_back(&g_map_info.line_list, new_list);
	return (1);
}

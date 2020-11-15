/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 18:33:40 by hchorfi           #+#    #+#             */
/*   Updated: 2020/11/07 18:33:43 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(int x, int y, int color)
{
	char	*dst;

	dst = (char*)g_mlx_data.addr + (y * g_mlx_data.line_length + x
		* (g_mlx_data.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int		exit_cube(void)
{
	mlx_destroy_window(g_mlx_data.mlx_ptr, g_mlx_data.win_ptr);
	exit(0);
}

int		key_pressed(int key)
{
	if (key == W)
		g_player.walk_direction = +1;
	if (key == S)
		g_player.walk_direction = -1;
	if (key == D)
		g_player.indentation = -1;
	if (key == A)
		g_player.indentation = +1;
	if (key == R)
		g_player.turn_direction = +1;
	if (key == L)
		g_player.turn_direction = -1;
	if (key == ESC)
		exit_cube();
	return (key);
}

int		key_released(int key)
{
	if (key == W || key == S)
		g_player.walk_direction = 0;
	if (key == A || key == D)
		g_player.indentation = 0;
	if (key == L || key == R)
		g_player.turn_direction = 0;
	return (key);
}

int		init_win(void)
{
	g_map_info.width = TILE_SIZE * g_map_info.cols;
	g_map_info.height = TILE_SIZE * g_map_info.rows;
	g_mlx_data.mlx_ptr = mlx_init();
	g_mlx_data.win_ptr = mlx_new_window(g_mlx_data.mlx_ptr,
		g_mlx_data.w_width, g_mlx_data.w_height, "cub3D");
	g_mlx_data.img = mlx_new_image(g_mlx_data.mlx_ptr,
		g_mlx_data.w_width, g_mlx_data.w_height);
	g_mlx_data.addr = (int*)mlx_get_data_addr(g_mlx_data.img,
		&g_mlx_data.bits_per_pixel, &g_mlx_data.line_length,
								&g_mlx_data.endian);
	return (1);
}

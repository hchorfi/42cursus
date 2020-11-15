/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 18:15:44 by hchorfi           #+#    #+#             */
/*   Updated: 2020/11/12 18:15:46 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	create_header(void)
{
	g_sshot.header = ft_calloc(54, 1);
	g_bm_ih.bit_count = 24;
	g_bm_ih.width = g_mlx_data.w_width;
	g_bm_ih.height = g_mlx_data.w_height;
	g_sshot.width_in_bytes =
		((g_bm_ih.width * g_bm_ih.bit_count + 31) / 32) * 4;
	g_bm_ih.image_size = g_sshot.width_in_bytes * g_bm_ih.height;
	g_bm_ih.size_header = 40;
	g_bm_fh.offset_bits = 40 + 14;
	g_bm_fh.file_size = g_bm_fh.offset_bits + g_bm_ih.image_size;
	g_bm_ih.planes = 1;
	ft_memcpy(g_sshot.header, "BM", 2);
	ft_memcpy(g_sshot.header + 2, &g_bm_fh.file_size, 4);
	ft_memcpy(g_sshot.header + 10, &g_bm_fh.offset_bits, 4);
	ft_memcpy(g_sshot.header + 14, &g_bm_ih.size_header, 4);
	ft_memcpy(g_sshot.header + 18, &g_bm_ih.width, 4);
	ft_memcpy(g_sshot.header + 22, &g_bm_ih.height, 4);
	ft_memcpy(g_sshot.header + 26, &g_bm_ih.planes, 2);
	ft_memcpy(g_sshot.header + 28, &g_bm_ih.bit_count, 2);
	ft_memcpy(g_sshot.header + 34, &g_bm_ih.image_size, 4);
}

int		*get_colors(int color)
{
	int				*colors;

	colors = malloc(3 * sizeof(int));
	colors[0] = ((color >> 16) & 0xFF);
	colors[1] = ((color >> 8) & 0xFF);
	colors[2] = ((color) & 0xFF);
	return (colors);
}

void	create_image(void)
{
	int				row;
	unsigned int	col;
	int				*colors;

	g_sshot.img = malloc(g_bm_ih.image_size);
	row = g_bm_ih.height - 1;
	while (row > 0)
	{
		col = 0;
		while (col < g_bm_ih.width)
		{
			colors = get_colors(g_mlx_data.addr[(g_bm_ih.height - row)
				* g_bm_ih.width + col]);
			g_sshot.img[row * g_sshot.width_in_bytes + col * 3 + 2] = colors[0];
			g_sshot.img[row * g_sshot.width_in_bytes + col * 3 + 1] = colors[1];
			g_sshot.img[row * g_sshot.width_in_bytes + col * 3 + 0] = colors[2];
			col++;
		}
		row--;
	}
}

int		screenshot(void)
{
	g_sshot.fd = open("./screenshot.bmp",
		O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	create_header();
	create_image();
	write(g_sshot.fd, g_sshot.header, 54);
	write(g_sshot.fd, g_sshot.img, g_bm_ih.image_size);
	free(g_sshot.header);
	free(g_sshot.img);
	g_mlx_data.save = 0;
	exit(0);
}

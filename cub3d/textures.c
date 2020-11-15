/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 11:10:11 by hchorfi           #+#    #+#             */
/*   Updated: 2020/11/08 11:10:12 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_textures(void)
{
	g_txt.type = 0;
	while (g_txt.type < 5)
	{
		if (!(g_txt.img[g_txt.type] =
							mlx_xpm_file_to_image(g_mlx_data.mlx_ptr,
													g_txt.file[g_txt.type],
													&g_txt.tmp[0],
													&g_txt.tmp[1])))
			return (readfile_errors(4));
		g_txt.txt[g_txt.type] =
			(unsigned int *)mlx_get_data_addr(g_txt.img[g_txt.type],
												&g_txt.tmp[2],
												&g_txt.tmp[3],
												&g_txt.tmp[4]);
		free(g_txt.file[g_txt.type]);
		g_txt.type++;
	}
	return (1);
}

int		check_sprite_txt(char *line)
{
	while (*line == ' ')
		line++;
	if (ft_strncmp(line, "S ", 2) == 0)
		g_txt.type = SP;
	else
		return (0);
	return (1);
}

int		check_txt(char *line)
{
	while (*line == ' ')
		line++;
	if (ft_strncmp(line, "NO ", 3) == 0)
		g_txt.type = NO;
	else if (ft_strncmp(line, "SO ", 3) == 0)
		g_txt.type = SO;
	else if (ft_strncmp(line, "WE ", 3) == 0)
		g_txt.type = WE;
	else if (ft_strncmp(line, "EA ", 3) == 0)
		g_txt.type = EA;
	else
		return (0);
	return (1);
}

int		valid_txt(char *file)
{
	int	fd;
	int check;

	check = 1;
	if (file != NULL)
	{
		if (ft_strncmp(file + (ft_strlen(file) - 4), ".xpm", 4) == 0)
		{
			fd = open(file, O_RDONLY);
			if (fd < 0)
				check = 0;
		}
		else
			check = 0;
	}
	else
		check = 0;
	if (check == 0)
		return (stock_errors(3));
	else
		return (1);
}

int		stock_txt(char *line, char **tab, int len)
{
	tab = ft_split(line, ' ');
	while (tab[len])
		len++;
	if (len == 2 && valid_txt(tab[1]))
	{
		g_txt.file[g_txt.type] = ft_substr(tab[1], 0, ft_strlen(tab[1]));
		free_dpointer(tab, len);
		check_double_key(g_txt.type);
	}
	else
	{
		free_dpointer(tab, len);
		return (stock_errors(2));
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readfile2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <hchorfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 11:49:41 by hchorfi           #+#    #+#             */
/*   Updated: 2021/02/10 20:27:25 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		stock_resolution(char *line)
{
	char	**tab;
	int		len;

	tab = ft_split(line, ' ');
	len = 0;
	while (tab[len])
		len++;
	if (len == 3 && isalldigit(tab[1]) && isalldigit(tab[2]))
	{
		if ((g_mlx_data.w_width = ft_atoi(tab[1])) > MAX_W_WIDTH)
			g_mlx_data.w_width = MAX_W_WIDTH;
		if ((g_mlx_data.w_height = ft_atoi(tab[2])) > MAX_W_HEIGHT)
			g_mlx_data.w_height = MAX_W_HEIGHT;
		free_dpointer(tab, len);
		if (g_key.r == 1)
			return (readfile_errors(5));
		g_key.r = 1;
	}
	else
	{
		free_dpointer(tab, len);
		return (stock_errors(1));
	}
	return (1);
}

int		check_color(char *line)
{
	int		l;
	int		i;

	i = 0;
	l = 0;
	while (line[i] != '\0')
	{
		if (line[i] == ',')
			l++;
		i++;
	}
	if (l != 2)
		return (stock_errors(5));
	while (*line == ' ')
		line++;
	if (ft_strncmp(line, "F ", 2) == 0)
		g_txt.color_type = F;
	else if (ft_strncmp(line, "C ", 2) == 0)
		g_txt.color_type = C;
	else
		return (0);
	return (1);
}

int		stock_color(char *line)
{
	char	**tab;
	int		len;

	tab = ft_split(line, ' ');
	len = 0;
	while (tab[len])
		len++;
	if (len == 2 && valid_color(tab[1], 0, 0))
	{
		g_txt.hex_color[g_txt.color_type] =
			create_trgb(0, g_txt.color[0], g_txt.color[1], g_txt.color[2]);
		free_dpointer(tab, len);
		if (g_txt.color_type == C && g_key.c == 0)
			g_key.c = 1;
		else if (g_txt.color_type == F && g_key.f == 0)
			g_key.f = 0;
		else
			return (readfile_errors(5));
	}
	else
	{
		free_dpointer(tab, len);
		return (stock_errors(4));
	}
	return (1);
}

int		valid_color2(int i, char **tab)
{
	int	j;

	if (tab[i] && ft_strlen(tab[i]) <= 3)
	{
		j = 0;
		while (j < ft_strlen(tab[i]))
		{
			if (ft_isdigit(tab[i][j]))
				j++;
			else
				return (stock_errors(5));
		}
	}
	else
		return (stock_errors(5));
	g_txt.color[i] = ft_atoi(tab[i]);
	if (g_txt.color[i] >= 0 && g_txt.color[i] <= 255)
		return (1);
	else
		return (stock_errors(5));
}

int		valid_color(char *str, int len, int i)
{
	char	**tab;

	tab = ft_split(str, ',');
	while (tab[len])
		len++;
	if (len == 3)
	{
		while (i < 3)
		{
			if (valid_color2(i, tab))
				i++;
			else
				return (stock_errors(5));
		}
		free_dpointer(tab, len);
	}
	else
	{
		free_dpointer(tab, len);
		return (stock_errors(4));
	}
	return (1);
}

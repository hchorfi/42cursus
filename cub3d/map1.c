/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 13:34:37 by hchorfi           #+#    #+#             */
/*   Updated: 2020/11/08 13:34:39 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		valid_zero(int i, int j)
{
	if ((g_map_info.lines[i][j + 1] == '0' || g_map_info.lines[i][j + 1] == '1')
	&& (g_map_info.lines[i][j - 1] == '0' || g_map_info.lines[i][j - 1] == '1')
	&& (g_map_info.lines[i + 1][j] == '0' || g_map_info.lines[i + 1][j] == '1')
	&& (g_map_info.lines[i - 1][j] == '0' || g_map_info.lines[i - 1][j] == '1'))
		return (1);
	else
		return (0);
}

int		valid_space(int i, int j)
{
	if ((g_map_info.lines[i][j + 1] == ' ' || g_map_info.lines[i][j + 1] == '1')
	&& (g_map_info.lines[i][j - 1] == ' ' || g_map_info.lines[i][j - 1] == '1')
	&& (g_map_info.lines[i + 1][j] == ' ' || g_map_info.lines[i + 1][j] == '1')
	&& (g_map_info.lines[i - 1][j] == ' ' || g_map_info.lines[i - 1][j] == '1'))
		return (1);
	else
		return (0);
}

int		validmap2(int i, int j)
{
	if (j == 0 || j == g_map_info.cols - 1)
	{
		if (g_map_info.lines[i][j] == '1' || g_map_info.lines[i][j] == ' ')
			j++;
		else
			return (0);
	}
	else
	{
		if (g_map_info.lines[i][j] == '0' && valid_zero(i, j))
			j++;
		else if (g_map_info.lines[i][j] == ' ' && valid_space(i, j))
			j++;
		else if (g_map_info.lines[i][j] == '1')
			j++;
		else
			return (0);
	}
	return (1);
}

int		validmap(int i, int j)
{
	while (i < g_map_info.rows)
	{
		j = 0;
		while (j < g_map_info.cols)
		{
			if (i == 0 || i == (g_map_info.rows - 1))
			{
				if (g_map_info.lines[i][j] == '1'
					|| g_map_info.lines[i][j] == ' ')
					j++;
				else
					return (validmap_errors(2));
			}
			else
			{
				if (validmap2(i, j))
					j++;
				else
					return (validmap_errors(2));
			}
		}
		i++;
	}
	return (1);
}

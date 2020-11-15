/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 11:47:10 by hchorfi           #+#    #+#             */
/*   Updated: 2020/11/08 11:47:11 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		free_dpointer(char **tab, int len)
{
	int		i;

	i = 0;
	while (i < len)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (1);
}

int		check_double_key(int type)
{
	if (type == NO && g_key.no == 0)
		g_key.no = 1;
	else if (type == SO && g_key.so == 0)
		g_key.so = 1;
	else if (type == WE && g_key.we == 0)
		g_key.we = 1;
	else if (type == EA && g_key.ea == 0)
		g_key.ea = 1;
	else if (type == SP && g_key.s == 0)
		g_key.s = 1;
	else
		return (readfile_errors(5));
	return (1);
}

int		char_chr(char c, char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (c == str[i])
			return (1);
		i++;
	}
	return (0);
}

int		sprite_collision(float npx, float npy)
{
	int		i;
	float	distance;

	i = 0;
	while (i < g_sprite->count)
	{
		distance = dbpoints(npx, npy, g_sprite[i].x, g_sprite[i].y);
		if (distance <= 40.0)
			return (1);
		i++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readfile1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 11:26:07 by hchorfi           #+#    #+#             */
/*   Updated: 2020/11/08 11:26:09 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		check_resolution(char *line)
{
	while (*line == ' ')
		line++;
	if (ft_strncmp(line, "R ", 2) == 0)
		return (1);
	return (0);
}

int		check_and_stock(int check, char *line)
{
	if (check_resolution(line))
		check = stock_resolution(line);
	else if (check_txt(line))
		check = stock_txt(line, NULL, 0);
	else if (check_sprite_txt(line))
		check = (stock_txt(line, NULL, 0));
	else if (check_color(line))
		check = (stock_color(line));
	else
		check = 0;
	return (check);
}

int		fill_map(int i, int j, t_list *lst)
{
	if (g_map_info.rows >= 3 && g_map_info.cols >= 3)
	{
		if (!(g_map_info.lines = malloc(g_map_info.rows * sizeof(char*))))
			return (0);
		while (i < g_map_info.rows)
		{
			j = ft_strlen(lst->content);
			if (!(g_map_info.lines[i] =
							malloc((g_map_info.cols + 1) * sizeof(char))))
				return (0);
			ft_strlcpy(g_map_info.lines[i], lst->content, g_map_info.cols + 1);
			free(lst->content);
			while (j < g_map_info.cols)
			{
				g_map_info.lines[i][j] = ' ';
				j++;
			}
			g_map_info.lines[i][g_map_info.cols] = '\0';
			lst = lst->next;
			i++;
		}
	}
	else
		return (validmap_errors(1));
	return (1);
}

int		readfile2(int fd, int empty)
{
	int		gnl_check;
	int		check;
	char	*line;

	gnl_check = 1;
	check = 1;
	while (gnl_check == 1 && check == 1)
	{
		gnl_check = get_next_line(fd, &line);
		if (line[0] == '\0' && g_map_info.rows > 0)
			empty = 1;
		if (line[0] != '\0' && empty == 0)
			if ((check = check_map_line(line, check)))
				check = stock_map_line(line);
		if (line[0] != '\0' && empty == 1)
			return (validmap_errors(2));
		if (line[0] == '\0')
			free(line);
	}
	if (check == 1 && set_player() && set_sprites()
		&& fill_map(0, 0, g_map_info.line_list) && validmap(0, 0))
		check = 1;
	else
		check = 0;
	return (check);
}

int		readfile1(int fd, int n_line, int check)
{
	char	*line;

	while (check == 1 && n_line < 8)
	{
		check = get_next_line(fd, &line);
		if (line[0] != '\0' && check == 1)
		{
			if (check_and_stock(check, line))
				check = 1;
			else
				return (line_prefix_error());
			n_line++;
		}
		free(line);
	}
	if (check == 1 && n_line == 8)
		check = 1;
	return (check);
}

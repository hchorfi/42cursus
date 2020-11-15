/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 17:46:57 by hchorfi           #+#    #+#             */
/*   Updated: 2020/11/03 17:46:59 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		line_prefix_error(void)
{
	ft_putstr_fd("Error\nPlease check the line prefix in map.cub file.\n", 0);
	ft_putstr_fd("the lines befor the map can only start with:\n", 0);
	ft_putstr_fd("spaces,R ,NO ,SO ,WE ,EA ,S ,F ,C .\n", 0);
	exit(0);
}

int		stock_errors(int e)
{
	if (e == 1)
		ft_putstr_fd("Error\nR can have only 2 real numbers\n", 0);
	else if (e == 2)
		ft_putstr_fd("Error\nplease check .xmp texture path\n", 0);
	else if (e == 3)
		ft_putstr_fd("Error\nyou need a valid & exist .xpm file\n", 0);
	else if (e == 4)
		ft_putstr_fd("Error\nplease check the F & C parametrs\n", 0);
	else if (e == 5)
		ft_putstr_fd("Error\nthe color accept only 0-255,0-255,0-255\n", 0);
	exit(0);
}

int		readfile_errors(int e)
{
	if (e == 1)
		ft_putstr_fd("Error\nplease check map.cub path\n", 0);
	else if (e == 2)
		ft_putstr_fd("Error\ncan't close file\n", 0);
	else if (e == 3)
		ft_putstr_fd("Error\nsplit malloc failed\n", 0);
	else if (e == 4)
		ft_putstr_fd("Error\nproblem converting xpm to img\n", 0);
	else if (e == 5)
		ft_putstr_fd("Error\ndouble key\n", 0);
	else if (e == 6)
		ft_putstr_fd("Error\nmessing key\n", 0);
	else if (e == 7)
		ft_putstr_fd("Error\nfile empty or no map\n", 0);
	else if (e == 8)
		ft_putstr_fd("Error\n please check your arguments\n", 0);
	exit(0);
}

int		mapline_errors(int e)
{
	if (e == 1)
		ft_putstr_fd("Error\nyou only have 1 player N | S | W | E\n", 0);
	else if (e == 2)
		ft_putstr_fd("Eror\nplease check your sprite parametres\n", 0);
	else if (e == 3)
		ft_putstr_fd("Eror\nOnly 0,1,2,N,W,S,E accepted in the map\n", 0);
	else if (e == 4)
		ft_putstr_fd("Eror\nPlease set a player position\n", 0);
	exit(0);
}

int		validmap_errors(int e)
{
	if (e == 1)
		ft_putstr_fd("Error\nyou need a min map with 3x3\n", 0);
	else if (e == 2)
		ft_putstr_fd("Eror\ninvalid map\n", 0);
	exit(0);
}

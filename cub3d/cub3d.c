/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <hchorfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 10:45:06 by hchorfi           #+#    #+#             */
/*   Updated: 2020/10/27 14:22:34 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		check_args(int argc, char **argv)
{
	int len;

	if (argc < 2 || argc > 3)
		return (readfile_errors(8));
	if (argc == 2)
	{
		len = ft_strlen(argv[1]);
		if (!(ft_strncmp(argv[1] + (len - 4), ".cub", 4) == 0))
			readfile_errors(8);
	}
	if (argc == 3)
	{
		len = ft_strlen(argv[1]);
		if (!(ft_strncmp(argv[1] + (len - 4), ".cub", 4) == 0)
				|| !(ft_strncmp(argv[2], "--save", 6) == 0))
			readfile_errors(8);
		if ((ft_strncmp(argv[2], "--save", 6) == 0))
			g_mlx_data.save = 1;
	}
	return (1);
}

int		readfile(char **argv)
{
	int fd;

	fd = open(argv[1], O_RDWR);
	if (fd < 0)
		return (readfile_errors(1));
	if (readfile1(fd, 0, 1))
	{
		if (!(readfile2(fd, 0)))
			return (0);
	}
	else
		return (readfile_errors(7));
	if (close(fd) < 0)
		return (readfile_errors(2));
	return (1);
}

/*
** use this functions after cast_all_rays() for 2d
** render_map();
** render_player();
** render_all_rays();
*/

int		update(void)
{
	player_update();
	cast_all_rays();
	render_3d_walls(0, 0);
	render_sprite();
	mlx_clear_window(g_mlx_data.mlx_ptr, g_mlx_data.win_ptr);
	mlx_put_image_to_window(g_mlx_data.mlx_ptr, g_mlx_data.win_ptr,
		g_mlx_data.img, 0, 0);
	return (0);
}

/*
** use this function for leaks ???!!!!
** getchar();
*/

int		main(int argc, char **argv)
{
	init_val();
	if (check_args(argc, argv))
	{
		if (!(readfile(argv)))
			return (0);
	}
	init_win();
	ft_textures();
	if (g_mlx_data.save == 1)
	{
		cast_all_rays();
		render_3d_walls(0, 0);
		render_sprite();
		screenshot();
	}
	mlx_hook(g_mlx_data.win_ptr, 2, (1L << 0), key_pressed, (void*)0);
	mlx_hook(g_mlx_data.win_ptr, 3, (2L << 0), key_released, (void*)0);
	mlx_hook(g_mlx_data.win_ptr, 17, (2L << 0), exit_cube, (void*)0);
	mlx_loop_hook(g_mlx_data.mlx_ptr, update, NULL);
	mlx_loop(g_mlx_data.mlx_ptr);
	return (0);
}

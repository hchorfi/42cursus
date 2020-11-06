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

void	ft_textures()
{	
	txt.type = 0;
	while (txt.type < 5)
	{
		txt.img[txt.type] = mlx_xpm_file_to_image(mlx_data.mlx_ptr, txt.file[txt.type], &txt.tmp[0], &txt.tmp[1]);
		txt.txt[txt.type] = (unsigned int *)mlx_get_data_addr(txt.img[txt.type], &txt.tmp[2], &txt.tmp[3], &txt.tmp[4]);
		txt.type++;
	}
}

int		key_pressed(int key)
{
	if (key == W)
		player.walk_direction = +1;
	if (key == S)
		player.walk_direction = -1;
	if (key == D)
		player.turn_direction = +1;
	if (key == A)
		player.turn_direction = -1;
	if (key == R)
		player.turn_direction = +1;
	if (key == L)
		player.turn_direction = -1;
	return (key);
}

int		key_released(int key)
{
	if (key == W || key == S)
		player.walk_direction = 0;
	if (key == L || key == R || key == A || key == D)
		player.turn_direction = 0;
	return (key);
}

void            my_mlx_pixel_put(int x, int y, int color)
{
    char   *dst;

    dst = (char*)mlx_data.addr + (y * mlx_data.line_length + x * (mlx_data.bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int		check_resolution(char *line)
{
	while (*line == ' ')
		line++;
	if (ft_strncmp(line, "R ", 2) == 0)
		return (1);
	return (0);
}

int		check_player_pos(char *c, int x, int y)
{
	if (map_info.check_ppose == 0)
	{
		printf("Player posetion : %c @ (%d,%d) \n", *c, x+1, y+1);
		if (*c == 'N')
			player.rotation_angle = (PI / 2) * 3;
		else if (*c == 'S')
			player.rotation_angle = (PI / 2) * 1;
		else if (*c == 'W')
			player.rotation_angle = (PI / 2) * 2;
		else
			player.rotation_angle = (PI / 2) * 4;
		*c = '0';
		player.x = x;
		player.y = y;
		map_info.check_ppose = 1;
		return (1);
	}
	return (0);
}

int		char_chr(char c,char *str)
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

int		stock_map_line(char *line)
{
	t_list 	*new_list;
	int 	line_len;
	
	line_len = ft_strlen(line);
	if (line_len > map_info.cols)
		map_info.cols = line_len;
	new_list = ft_lstnew(line);
	if (map_info.line_list == NULL)
		map_info.line_list = new_list;
	else
		ft_lstadd_back(&map_info.line_list, new_list);
	printf("line-list    : %d | %s\n", map_info.rows, ft_lstlast(map_info.line_list)->content);
	return 1;
}

int		check_sprites_pos(char *c, int x, int y)
{
	*c = '0';
	sprite[sprite->count].col = x;
	sprite[sprite->count].row = y;
	sprite->count+=1;
	return (1);
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
			if (!(check = check_player_pos(&line[i],i,map_info.rows)))
				return (mapline_errors(1));
		}
		else if (char_chr(line[i], "2"))
		{
			if (!(check = check_sprites_pos(&line[i], i, map_info.rows)))
				return (mapline_errors(2));
		}
		else if (!(check = char_chr(line[i], "01")))
			return (mapline_errors(3));
		i++;
	}
	map_info.rows++;
	return (check);
}

int		stock_resolution(char *line)
{
	char	**tab;
	int		len;

	tab = ft_split(line, ' ');
	len = 0;
	while(tab[len])
		len++;
	if (len == 3 && isalldigit(tab[1]) && isalldigit(tab[2]))
	{
		if ((mlx_data.w_width = ft_atoi(tab[1])) > max_w_width )
			mlx_data.w_width = max_w_width;
		if ((mlx_data.w_height = ft_atoi(tab[2])) > max_w_height )
			mlx_data.w_height = max_w_height;
	}
	else
		return (stock_errors(1));
	while(len > 0)
	{
		free(tab[len]);
		len--;
	}
	free(tab);
	return (1);
}

int		check_args(int argc, char **argv)
{
	if (argc < 2 || argc > 3)
	{
		perror("Error\n please check your arguments\n");
		return (0);
	}
	return (1);
}

int		fill_map()
{
	int		i;
	int		j;
	char 	*str;

	i = 0;
	if (map_info.rows >= 3 && map_info.cols >= 3)
	{	
		if (!(map_info.lines = malloc(map_info.rows * sizeof(char*))))
			return (0);
		while (map_info.line_list)
		{
			j = ft_strlen(map_info.line_list->content);
			if (!(map_info.lines[i] = malloc((map_info.cols + 1) * sizeof(char))))
				return (0);
			ft_strlcpy(map_info.lines[i], map_info.line_list->content, map_info.cols + 1);
			while (j < map_info.cols)
			{
				map_info.lines[i][j] = ' ';
				j++;
			}
			map_info.lines[i][map_info.cols] = '\0';
			map_info.line_list = map_info.line_list->next;
			i++;
		}
	}
	else
		return (validmap_errors(1));
	return 1;
}

int		valid_zero(int i, int j)
{
	if ((map_info.lines[i][j + 1] == '0' || map_info.lines[i][j + 1] == '1') && (map_info.lines[i][j - 1] == '0' || map_info.lines[i][j - 1] == '1') && (map_info.lines[i + 1][j] == '0' || map_info.lines[i + 1][j] == '1') && (map_info.lines[i - 1][j] == '0' || map_info.lines[i - 1][j] == '1'))
		return (1);
	else
		return (0);
}

int		valid_space(int i, int j)
{
	if ((map_info.lines[i][j + 1] == ' ' || map_info.lines[i][j + 1] == '1') && (map_info.lines[i][j - 1] == ' ' || map_info.lines[i][j - 1] == '1') && (map_info.lines[i + 1][j] == ' ' || map_info.lines[i + 1][j] == '1') && (map_info.lines[i - 1][j] == ' ' || map_info.lines[i - 1][j] == '1'))
		return (1);
	else
		return (0);
}

int		validmap(void)
{
	int i;
	int	j;

	i = 0;
	while (i < map_info.rows)
	{
		j = 0;
		while (j < map_info.cols)
		{
			if (i == 0 || i == (map_info.rows - 1))
			{	if (map_info.lines[i][j] == '1' || map_info.lines[i][j] == ' ')
					j++;
				else 
					return (validmap_errors(2));
			}
			else
			{
				if (j == 0 || j == map_info.cols - 1)
				{
					if (map_info.lines[i][j] == '1' || map_info.lines[i][j] == ' ')
						j++;
					else
						return (validmap_errors(3));
				}
				else
				{
					if (map_info.lines[i][j] == '0' && valid_zero(i, j))
						j++;
					else if (map_info.lines[i][j] == ' ' && valid_space(i, j))
						j++;
					else if (map_info.lines[i][j] == '1')
						j++;
					else
					{
						printf ("%d : %d", i,j);	
						return (validmap_errors(4));
					}
				}
			}
		}
		printf(" : %d\n", i);
		i++;
	}
	return (1);
}

int		set_player()
{
	if (map_info.check_ppose == 1)
	{
		if (mlx_data.w_width / map_info.cols < mlx_data.w_height / map_info.rows)
			map_info.tile = mlx_data.w_width / map_info.cols;
		else
			map_info.tile = mlx_data.w_height / map_info.rows;
		player.x = player.x * tile_size + (tile_size / 2);
		player.y = player.y * tile_size + (tile_size / 2);
		printf("player x : %f player y : %f tile : %d\n", player.x, player.y , tile_size);
	}
	else
		return (mapline_errors(4));
	return (1);
}

int		set_sprites()
{
	int i;

	i = 0;
	while (i < sprite->count)
	{
		sprite[i].x = sprite[i].col * tile_size + (tile_size / 2);
		sprite[i].y = sprite[i].row * tile_size + (tile_size / 2);
		printf("sprite %d : %f , %f\n", i, sprite[i].x, sprite[i].y);
		i++;
	}
	printf("sprites : %d\n", sprite->count);
	return (1);
}

int		readfile2(int fd)
{
	int		gnl_check;
	int		check;
	char	*line;
	
	gnl_check = 1;
	check = 1;
	while (gnl_check == 1 && check == 1)
	{
		gnl_check = get_next_line(fd, &line);
		if (line[0] != '\0')
			if ((check = check_map_line(line, check)))
				check = stock_map_line(line);
	}
	printf("check : %d -- gnl : %d\nmap_rows : %d\nmap_cols : %d\n", check, get_next_line(fd, &line), map_info.rows, map_info.cols);
	printf("Resolution : %d %d\n", mlx_data.w_width, mlx_data.w_height);
	
	if (check == 1 && set_player() && set_sprites() && fill_map() && validmap())
		check = 1;
	else
		check = 0;
	return (check);
}

int		check_txt(char *line)
{
	while (*line == ' ')
		line++;
	if (ft_strncmp(line, "NO ", 3) == 0)
		txt.type = NO;
	else if (ft_strncmp(line, "SO ", 3) == 0)
		txt.type = SO;
	else if (ft_strncmp(line, "WE ", 3) == 0)
		txt.type = WE;
	else if (ft_strncmp(line, "EA ", 3) == 0)
		txt.type = EA;
	else
		return (0);
	return (1);
}

int		valid_txt(char	*file)
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

int		stock_txt(char *line)
{
	char	**tab;
	int		len;

	tab = ft_split(line, ' ');
	len = 0;
	while(tab[len])
		len++;
	if (len == 2 && valid_txt(tab[1]))
	{
		txt.file[txt.type] = ft_substr(tab[1], 0, ft_strlen(tab[1]));
		txt.type = -1;
	}
	else
		return (stock_errors(2));
	while(len > 0)
	{
		free(tab[len]);
		len--;
	}
	free(tab);
	return (1);
}

int		check_color(char *line)
{
	while (*line == ' ')
		line++;
	if (ft_strncmp(line, "F ", 2) == 0)
		txt.color_type = F;
	else if (ft_strncmp(line, "C ", 2) == 0)
		txt.color_type = C;
	else
		return (0);
	return (1);
}

int		valid_color(char *str)
{
	char	**tab;
	int		len;
	int		i;
	int		j;

	tab = ft_split(str, ',');
	len = 0;
	i = 0;
	while (tab[len])
		len++;
	if (len == 3)
	{
		while (i < 3)
		{
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
			if ((txt.color[i] = ft_atoi(tab[i])) >= 0 && (txt.color[i] = ft_atoi(tab[i])) <= 255)
				i++;
			else 
				return (stock_errors(5));
		}
	}
	else
		return (stock_errors(5));
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
	if (len == 2 && valid_color(tab[1]))
	{
		txt.hex_color[txt.color_type] = 
			create_trgb(0, txt.color[0], txt.color[1], txt.color[2]);
		printf("%X\n", txt.hex_color[0]);
	}
	else
		return (stock_errors(4));
	while(len > 0)
	{
		free(tab[len]);
		len--;
	}
	free(tab);
	return (1);
}

int		readfile1(int fd)
{
	int		check;
	char	*line;
	int		n_line;

	n_line	= 0;
	check	= 1;
	while (check == 1 && n_line < 8)
	{
		check = get_next_line(fd, &line);
		while (check == 1 && line[0] == '\0')
			check = get_next_line(fd, &line);
		if (line[0] != '\0' && check == 1)
		{
			if (check_resolution(line))
				check = stock_resolution(line);
			else if (check_txt(line))
				check = stock_txt(line);
			else if (check_sprite_txt(line))
				check = (stock_txt(line));
			else if (check_color(line))
				check = (stock_color(line));
			else
				return (line_prefix_error());
		}
		n_line++;
		free(line);
	}
	if (check == 1 && n_line == 8)
		check = 1;
	return (check);
}

int		readfile(char **argv)
{
	int fd;
	
	fd = open(argv[1], O_RDWR);
	if (fd > 0)
	{
		if (!(ft_strncmp(argv[1], "map.cub", 7) == 0))
			return (readfile_errors(1));
	}
	else
		return (readfile_errors(1));
	if (readfile1(fd))
	{
		if (!(readfile2(fd)))
			return (0);
	}
	if (close(fd) < 0)
		return (readfile_errors(2));
	return (1);
}

void init_val(void)
{
	player.color = 0xff0000;
	player.turn_direction = 0;
	player.walk_direction = 0;
	player.walk_speed = 6;
	player.turn_speed = 4 * (PI / 180);
	map_info.rows = 0;
	map_info.cols = 0;
	map_info.check_ppose = 0;
	map_info.line_list = NULL;
	txt.type = -1;
	txt.tile = 64;
	sprite->count = 0;
}

int    render()
{
	render_3d_walls(0, 0);
	render_sprite();
    //render_map();
	//render_player();
	//render_all_rays();
	return 0;
}

int		wall_collision(float npx, float npy)
{
	//printf("npx %f: npy %f\n", npx, npy);
	if (npx < 0 || npx > map_info.width || npy < 0 || npy > map_info.height)
		return (1);
	map_info.x = floor(npx / tile_size);
	map_info.y = floor(npy / tile_size);
	//printf("%d : %d = '%d'\n", map_info.y,map_info.x,map_info.lines[map_info.y][map_info.x]);
	if (map_info.lines[map_info.y][map_info.x] - '0' == 0)
		return (0);
	else
		return (1);
}

int		sprite_collision(float npx, float npy)
{
	int i;

	i = 0;
	if (npx < 0 || npx > map_info.width || npy < 0 || npy > map_info.height)
		return (1);
	map_info.x = floor(npx / tile_size);
	map_info.y = floor(npy / tile_size);
	if (map_info.lines[map_info.y][map_info.x] - '0' == 2)
		return (0);
	else
		return (1);
	
}

int		player_update()
{
	float npx;
	float npy;
	
	player.rotation_angle += player.turn_direction * player.turn_speed;
	
	player.step = player.walk_direction * player.walk_speed;

	npx = player.x + cosf(player.rotation_angle) * player.step;
	npy = player.y + sinf(player.rotation_angle) * player.step;
	if (!(wall_collision(npx, npy)) || !(sprite_collision(npx, npy)))
	{
		player.x = npx;
		player.y = npy;
	}
	return (0);
}

int		update()
{
	player_update();
	cast_all_rays();
	render();
	mlx_clear_window (mlx_data.mlx_ptr, mlx_data.win_ptr);
	mlx_put_image_to_window(mlx_data.mlx_ptr, mlx_data.win_ptr, mlx_data.img, 0, 0);
	return (0);
}

int 	init_win()
{
	map_info.width = tile_size * map_info.cols;
	map_info.height = tile_size * map_info.rows;
	mlx_data.mlx_ptr = mlx_init();
    mlx_data.win_ptr = mlx_new_window(mlx_data.mlx_ptr, mlx_data.w_width, mlx_data.w_height, "Cub 3D");
	mlx_data.img = mlx_new_image(mlx_data.win_ptr, mlx_data.w_width, mlx_data.w_height);
	mlx_data.addr = (int*)mlx_get_data_addr(mlx_data.img, &mlx_data.bits_per_pixel, &mlx_data.line_length,
                                 &mlx_data.endian);												
	return (1);
}

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
	mlx_hook(mlx_data.win_ptr, 2, (1L << 0), key_pressed, (void*)0);
	mlx_hook(mlx_data.win_ptr, 3, (2L << 0), key_released, (void*)0);
	mlx_loop_hook(mlx_data.mlx_ptr, update, NULL);
	mlx_loop(mlx_data.mlx_ptr);
	return (0);
}
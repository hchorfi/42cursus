/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <hchorfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 20:28:25 by hchorfi           #+#    #+#             */
/*   Updated: 2020/10/23 19:11:58 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*mlx_ptr;
void	*win_ptr;

/*const   int map[map_rows][map_cols] = {
    {5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1},
    {1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1},
    {1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1},
    {1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1},
    {1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 3, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};*/

void            my_mlx_pixel_put(int x, int y, int color)
{
    char   *dst;

    dst = (char*)mlx_data.addr + (y * mlx_data.line_length + x * (mlx_data.bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void	blackscreen()
{
	int y = 0;
	int x;
	while (y < mlx_data.w_height)
	{
		x = 0;
		while (x < mlx_data.w_width)
		{
			my_mlx_pixel_put(x,y,0x000000);
			x++;
		}
		y++;
	}
}

void    draw_square(int square_i, int square_j, int square_color)
{
    int i;
    int j;

    j = 0;
    while (j < map_info.tile)
    {
        i = 0;
        while (i < map_info.tile)
        {
            my_mlx_pixel_put(
						 ((i + square_i) * minimap_sf),
						 ((j + square_j) * minimap_sf),
						 square_color);
            i++;
        }
        j++;
    }
}


void    draw_player()
{
	//int	j ;
	//int i;

	//j = 0;
	//i = 0;
  
    double x1, y1;
	double r;
	double angle ;
	r = 4;
	angle = 0;
    double minAngle = cos(1 - 1/r);

    while (r > 0)
	{
		while ( angle <= 360)
    	{
        	x1 = r * cos(angle);
        	y1 = r * sin(angle);
        	my_mlx_pixel_put(
						 (((player.x) + x1) * minimap_sf),
						 (((player.y) + y1) * minimap_sf),
						 player.color);
			angle += minAngle;
    	}
		angle = 0;
		r--;
	}
}

void	ft_textures()
{	
	void	*img7;
	int		tab[5];
	char 	*file;
	file = "brick.xpm";
	
	img7 = mlx_xpm_file_to_image(mlx_ptr, file, &tab[0], &tab[1]);
	txt.txt_1 = (unsigned int *)mlx_get_data_addr(img7, &tab[2], &tab[3], &tab[4]);
}

void	render_3d_walls()
{
	int i;
	int y;
	i = 0;
	
	while (i < mlx_data.w_width)
	{
		wall_3d.wal_3d_distance = ray[i].distance * cosf(ray[i].angle - player.rotation_angle);
		wall_3d.distance_pro_plan = (mlx_data.w_width / 2) / tan(fov_angle / 2);
		wall_3d.pro_wall_hie = (map_info.tile / wall_3d.wal_3d_distance) * wall_3d.distance_pro_plan;

		wall_3d.wall_strip_hie =(int)wall_3d.pro_wall_hie;

		wall_3d.wal_top = (mlx_data.w_height / 2) - (wall_3d.wall_strip_hie / 2);
		wall_3d.wal_top = wall_3d.wal_top < 0 ? 0: wall_3d.wal_top;
	
		wall_3d.wal_bot = (mlx_data.w_height / 2) + (wall_3d.wall_strip_hie / 2);
		wall_3d.wal_bot = wall_3d.wal_bot > mlx_data.w_height ? mlx_data.w_height : wall_3d.wal_bot;
		txt.x = ray[i].vertical_hit == 1 ? fmod(ray[i].wall_hity,map_info.tile) : fmod(ray[i].wall_hitx,map_info.tile);
		y = 0;
		while (y < wall_3d.wal_top)
		{
			mlx_data.addr[i + y * mlx_data.w_width] = 0x73c2fb;
			y++;
		}
		while (y < wall_3d.wal_bot)
		{
			int distance_from_top = y + ( wall_3d.wall_strip_hie / 2) - (mlx_data.w_height / 2);
			txt.y = (int)((distance_from_top * map_info.tile) / wall_3d.wall_strip_hie);
			mlx_data.addr[i + y * mlx_data.w_width] = txt.txt_1[txt.x + (map_info.tile * txt.y)];
			y++;
		}
		while (y < mlx_data.w_height)
		{
			mlx_data.addr[i + y * mlx_data.w_width] = 0x300e1c;
			y++;
		}
		i++;
	}
}



float	normalize(float angle)
{
	angle = fmod (angle, 2 * PI);
	if (angle < 0)
	{
		angle = (2 * PI) + angle;
	}
	return (angle);
}

float distanceBetweenPoints(float x1, float y1, float x2, float y2) 
{
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

int		wall_collision(float npx, float npy)
{
	if (npx < 0 || npx > mlx_data.w_width || npy < 0 || npy > mlx_data.w_height)
		return (1);
	map_info.x = (int)(npx / map_info.tile);
	map_info.y = (int)(npy / map_info.tile);
	return (map_info.lines[map_info.y][map_info.x] == 1 ? 1 : 0);
}

void	cast_ray(float ray_angle, int strip_id)
{
	
	ray_angle = normalize(ray_angle);
	data.face_down = ray_angle > 0 && ray_angle < PI;
	data.face_up = !data.face_down;
	data.face_right = ray_angle < 0.5 * PI || ray_angle > 1.5 * PI;
	data.face_left = !data.face_right;
	
	/////////////////////////
	//horizonale intersection
	/////////////////////////

	data.found_hor_wal_hit = 0;
	data.hor_wal_hit_x = 0;
	data.hor_wal_hit_y = 0;
	data.hor_wal_content = 0;


	data.y_intercept = floor(player.y / map_info.tile) * map_info.tile;
	data.y_intercept += data.face_down ? map_info.tile : 0;
	
	data.x_intercept =	player.x + (data.y_intercept - player.y) / tanf(ray_angle);

	data.y_step = map_info.tile;
	data.y_step *= data.face_up ? -1 : 1;

	data.x_step = map_info.tile / tanf(ray_angle);
	data.x_step *= (data.face_left && data.x_step > 0) ? -1 : 1;
	data.x_step *= (data.face_right && data.x_step < 0) ? -1 : 1;

	data.next_hor_touch_x = data.x_intercept;
	data.next_hor_touch_y = data.y_intercept;

	// increment xstep and ystep until we find a wall	
	while (data.next_hor_touch_x >= 0 && data.next_hor_touch_x <= mlx_data.w_width && data.next_hor_touch_y >= 0 && data.next_hor_touch_y <= mlx_data.w_height)
	{
		data.x_to_check = data.next_hor_touch_x;
		data.y_to_check = data.next_hor_touch_y + (data.face_up ? -1 : 0);

		if (wall_collision(data.x_to_check, data.y_to_check)) {
            // found a wall hit
            data.hor_wal_hit_x = data.next_hor_touch_x;
            data.hor_wal_hit_y = data.next_hor_touch_y;
            //data.hor_wal_content = map_info.lines[(int)floor(data.y_to_check / map_info.tile)][(int)floor(data.x_to_check / map_info.tile)];
            data.found_hor_wal_hit = 1;
            break;
        } else {
            data.next_hor_touch_x += data.x_step;
            data.next_hor_touch_y += data.y_step;
        }
	}

	/////////////////////////
	//verticel intersection
	/////////////////////////

	data.found_ver_wal_hit = 0;
	data.ver_wal_hit_x = 0;
	data.ver_wal_hit_y = 0;
	data.ver_wal_content = 0;


	data.x_intercept = floor(player.x / map_info.tile) * map_info.tile;
	data.x_intercept += data.face_right ? map_info.tile : 0;
	
	data.y_intercept =	player.y + (data.x_intercept - player.x) * tanf(ray_angle);

	data.x_step = map_info.tile;
	data.x_step *= data.face_left ? -1 : 1;

	data.y_step = map_info.tile * tanf(ray_angle);
	data.y_step *= (data.face_up && data.y_step > 0) ? -1 : 1;
	data.y_step *= (data.face_down && data.y_step < 0) ? -1 : 1;

	data.next_ver_touch_x = data.x_intercept;
	data.next_ver_touch_y = data.y_intercept;
	
	// increment xstep and ystep until we find a wall
	while (data.next_ver_touch_x >= 0 && data.next_ver_touch_x <= mlx_data.w_width && data.next_ver_touch_y >= 0 && data.next_ver_touch_y <= mlx_data.w_height)
	{
		data.x_to_check = data.next_ver_touch_x + (data.face_left ? -1 : 0);
		data.y_to_check = data.next_ver_touch_y;

		if (wall_collision(data.x_to_check, data.y_to_check)) {
            // found a wall hit
            data.ver_wal_hit_x = data.next_ver_touch_x;
            data.ver_wal_hit_y = data.next_ver_touch_y;
			//printf("%c\n", map_info.lines[(int)floor(data.y_to_check / map_info.tile)][(int)floor(data.x_to_check / map_info.tile)]);
            //data.ver_wal_content = map_info.lines[(int)floor(data.y_to_check / map_info.tile)][(int)floor(data.x_to_check / map_info.tile)];
            data.found_ver_wal_hit = 1;
            break;
        } else {
            data.next_ver_touch_x += data.x_step;
            data.next_ver_touch_y += data.y_step;
        }
	}
	
	// Calculate both horizontal and vertical hit distances and choose the smallest one
    data.hor_hit_distance = data.found_hor_wal_hit
        ? distanceBetweenPoints(player.x, player.y, data.hor_wal_hit_x, data.hor_wal_hit_y)
        : INT_MAX;
    data.ver_hit_distance = data.found_ver_wal_hit
        ? distanceBetweenPoints(player.x, player.y, data.ver_wal_hit_x, data.ver_wal_hit_y)
        : INT_MAX;

    if (data.ver_hit_distance < data.hor_hit_distance) {
        ray[strip_id].distance = data.ver_hit_distance;
        ray[strip_id].wall_hitx = data.ver_wal_hit_x;
        ray[strip_id].wall_hity = data.ver_wal_hit_y;
        ray[strip_id].wall_content = data.ver_wal_content;
        ray[strip_id].vertical_hit = 1;
    } else {
        ray[strip_id].distance = data.hor_hit_distance;
        ray[strip_id].wall_hitx = data.hor_wal_hit_x;
        ray[strip_id].wall_hity = data.hor_wal_hit_x;
        ray[strip_id].wall_content = data.hor_wal_content;
        ray[strip_id].vertical_hit = 0;
    }
    ray[strip_id].face_down = data.face_down;
    ray[strip_id].face_up = data.face_up;
    ray[strip_id].face_left = data.face_left;
    ray[strip_id].face_right = data.face_right;
	ray[strip_id].angle = ray_angle;
	//printf("%f", ray_angle);
}

void	cast_all_rays()
{	
	float	ray_angle;
	int		strip_id;
	
	ray_angle = player.rotation_angle - (fov_angle / 2);
	strip_id = 0;
	while (strip_id < 1)
	{
		cast_ray(ray_angle, strip_id);
		ray_angle += fov_angle / mlx_data.w_width;
		strip_id++;
		
	}
	
}

void    render_map()
{   
    int i;
    int j;
    int square_i;
    int square_j;

    j = 0;
    square_i = 0;
    square_j = 0;
    while (j < map_info.rows)
    {
        i = 0;
        square_i = 0;
        while (i < map_info.cols)
        {
			//printf("%c", map_info.lines[j][i]);
            if (map_info.lines[j][i] == '1')
                draw_square(square_i, square_j, 0xffffff);
            if (map_info.lines[j][i] == '0' || map_info.lines[j][i] == 3)
                draw_square(square_i, square_j, 0x000000);
            i++;
            square_i += map_info.tile;
        }
		//printf("\n");
        j++;
        square_j += map_info.tile;
    }
	//printf("\nmap_info.tile = %d\n", map_info.tile);
}

int   	render_player()
{
    draw_player();
	return 0;
}

void	render_all_rays()
{

	int	j;
	int i;
	int	k;

	j = 0;
	i = 0;
	k = 0;
	while (k < 1)
	{
		while (j < ray[k].distance)
		{
			my_mlx_pixel_put(
						((player.x + (i * cosf(ray[k].angle))) * minimap_sf),
						((player.y + (j * sinf(ray[k].angle))) * minimap_sf),
						0xffff00);
			j++;
			i++;
		}
		k++;
		j = 0;
		i = 0;
	}
	
}

int    render()
{
	//blackscreen();
	render_3d_walls();
    render_map();
	render_player();
	render_all_rays();
	return 0;
}

int		player_update()
{
	float npx;
	float npy;
	
	player.rotation_angle += player.turn_direction * player.turn_speed;
	
	player.step = player.walk_direction * player.walk_speed;

	npx = player.x + cosf(player.rotation_angle) * player.step;
	npy = player.y + sinf(player.rotation_angle) * player.step;
	
	if (!(wall_collision(npx, npy)))
	{
		player.x = npx;
		player.y = npy;
	}
	return (0);
}

int		key_released(int key)
{
	if (key == W || key == S)
		player.walk_direction = 0;
	if (key == L || key == R || key == A || key == D)
		player.turn_direction = 0;
	return (key);
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
	//ft_printf("%d\n", key);
	return (key);
}

int		update()
{
	//mlx_hook(win_ptr, 2, (1L << 0), key_pressed, (void*)0);
	//mlx_hook(win_ptr, 3, (2L << 0), key_released, (void*)0);
	player_update();
	//cast_all_rays();
	render();
	mlx_clear_window (mlx_ptr, win_ptr);
	mlx_put_image_to_window(mlx_ptr, win_ptr, mlx_data.img, 0, 0);
	return (0);
}

int 	init_win()
{
	/*if (!(ray = malloc(mlx_data.w_width * sizeof (struct s_ray))))
		return (0);
	printf("%d\n", ray[1].wall_content);*/
	map_info.tile = mlx_data.w_width / map_info.cols;
	mlx_ptr = mlx_init();
    win_ptr = mlx_new_window(mlx_ptr, mlx_data.w_width, mlx_data.w_height, "Cub 3D");
	mlx_data.img = mlx_new_image(mlx_ptr, mlx_data.w_width, mlx_data.w_height);
	mlx_data.addr = (int*)mlx_get_data_addr(mlx_data.img, &mlx_data.bits_per_pixel, &mlx_data.line_length,
                                 &mlx_data.endian);												
	return (1);
}
void 	setup()
{
	int j;
    int i;

    j = 0;
    while (j < map_rows)
    {
        i = 0;
        while (i < map_cols)
        {
            if (map_info.lines[j][i] == 118)
            {
				player.x = i * map_info.tile + (map_info.tile / 2);
				player.y = j * map_info.tile + (map_info.tile / 2);
			}
            i++;
        }
        j++;
    }
}

void		ft_putstr(char *s)
{
	int i;

	i = 0;
	while (s[i])
		write(1, &s[i++], 1);
}

int args_err(void)
{
	ft_putstr("Error\nBad Args\n");
	return (0);
}

int		check_args(int ac)
{
	if (ac < 2 || ac > 3)
		return (args_err());
	return (1);
}

int		invalide_path(void)
{
	ft_putstr("Error\nInvalid map file path\n");
	return (0);
}

int		check_resolution(char *line)
{
	if (ft_strncmp(line, "R ", 2) == 0)
		return (1);
	else
		return (0);
}

int		isalldigit(char *str)
{
	int		i;

	i = 0;
	while(i != -1 && str[i])
	{
		if (ft_isdigit(str[i]))
			i++;
		else
			i = -1;
	}
	if (i == -1)
		return (0);
	return (1);
}

int		stock_resolution(char *line)
{
	char	**tab;
	int		len;

	tab = ft_split(line, ' ');
	len =0;
	while(tab[len])
		len++;
	if (len == 3 && isalldigit(tab[1]) && isalldigit(tab[2]))
	{
		if ((mlx_data.w_width = ft_atoi(tab[1])) > max_w_width )
			mlx_data.w_width = max_w_width;
		if ((mlx_data.w_height = ft_atoi(tab[2])) > max_w_height )
			mlx_data.w_height = max_w_height;
		//ft_printf("Resolution : %d %d\n", mlx_data.w_width, mlx_data.w_height);
	}
	else
	{
		ft_putstr("Error\nPlease check your resolution config");
		return (0);
	}
	while(len > 0)
	{
		free(tab[len]);
		len--;
	}
	free(tab);
	return (1);
}

int		err_print(char *str)
{
	ft_putstr("Error\n");
	ft_putstr(str);
	ft_putstr("\n");
	return 0;
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

int		set_player(char c, int x, int y)
{
	if (map_info.check_pose == 0)
	{
		printf("Player posetion : %c @ (%d,%d) \n", c, x+1, y+1);
		player.x = x * map_info.tile + (map_info.tile / 2);
		player.y = y * map_info.tile + (map_info.tile / 2);
		map_info.check_pose = 1;
		return (1);
	}
	return (0);
}

int		check_map_line(char *line, int check)
{
	int		i;
	
	i = 0;
	while (line[i])
	{
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if (char_chr(line[i], "NWSE"))
		{
			if (!(check = set_player(line[i],i,map_info.rows)))
			{
				perror("Error\none player allowed");
				return (0);
			}
		}
		else if (!(char_chr(line[i], "01")))
		{
			return (err_print("Only 0,1,2,N,W,S,E character accepted in he map"));
		}
		i++;
	}
	map_info.rows++;
	return (check);
}

int		stock_map_line(char *line)
{
	t_list 	*new_list;
	int 	line_len;
	
	line_len = ft_strlen(line);
	new_list = ft_lstnew(line);
	if (map_info.line_list == NULL)
		map_info.line_list = new_list;
	else
		ft_lstadd_back(&map_info.line_list, new_list);
	if (line_len > map_info.cols)
		map_info.cols = line_len;
	printf("line-list    : %d | %s\n", map_info.rows, ft_lstlast(map_info.line_list)->content);
	return 1;
}

int		fill_map()
{
	int		i;
	int		j;
	char 	*str;
	int 	len;

	i = 0;
	if (!(map_info.lines = malloc(map_info.rows * sizeof(int*))))
		return (0);
	while (i < map_info.rows)
	{
		j = 0;
		str = map_info.line_list->content;
		len = ft_strlen(str);
		if (!(map_info.lines[i] = malloc((map_info.cols) * sizeof(int))))
			return (0);
		while (j < len)
		{
			map_info.lines[i][j] = (int)str[j];
			j++;
		}
		while (j < map_info.cols)
		{
			map_info.lines[i][j] = ' ';
			j++;
		}
		//map_info.lines[i][j] = '\0';
		printf("%d\n", ft_strlen(str));
		printf("line %d : j= %d cols= %d len= %d", i , j, map_info.cols, len);
		map_info.line_list = map_info.line_list->next;
		i++;
	}
	
	i = 0;
	j = 0;
	while (i < map_info.rows)
	{
		while (j < map_info.cols)
		{
			printf("%c", map_info.lines[i][j]);
			j++;
		}
		printf("\n");
		i++;
		j = 0;
	}
	return 1;
}

int		readfile2(int fd, char *line, int check)
{
	int gnl_check = 1;
	while (gnl_check == 1 && check == 1)
	{
		gnl_check = get_next_line(fd, &line);
		if (line[0] != '\0')
			if ((check = check_map_line(line, 1)))
				check = stock_map_line(line);
	}
	printf("check : %d -- gnl : %d\nmap_rows : %d\nmap_cols : %d\n", check, get_next_line(fd, &line), map_info.rows, map_info.cols);
	if (check == 1)
		check = fill_map();
	return (check);
}

int		readfile(char **av)
{
	int 	fd;
	int		check;
	char	*line;
	int		n_line;
	
	n_line	= 0;
	check	= 1;
	if ((fd = open(av[1], O_RDWR)) < 0)
		return (invalide_path());
	while (check == 1 && n_line < 8)
	{
		check = get_next_line(fd, &line);
		if (line[0] != '\0' && check == 1)
			if (check_resolution(line))
				check = stock_resolution(line);
		n_line++;
		free(line);
	}
	if (check == 1 && n_line == 8)
		check = readfile2(fd, NULL,1);
	return (check);
}

void init_val(void)
{
	player.color = 0xff0000;
	player.turn_direction = 0;
	player.walk_direction = 0;
	player.rotation_angle = (PI / 2)*3;
	player.walk_speed = 10;
	player.turn_speed = 5 * (PI / 180);
	map_info.rows = 0;
	map_info.cols = 0;
	map_info.check_pose = 0;
	map_info.line_list = NULL;
}

int     main(int ac,char **av)
{
	init_val();
	if (!check_args(ac))
		return (0);
	if (!readfile(av))
		return (0);
	init_win();
    setup();
	ft_textures();
	mlx_hook(win_ptr, 2, (1L << 0), key_pressed, (void*)0);
	mlx_hook(win_ptr, 3, (2L << 0), key_released, (void*)0);
	mlx_loop_hook(mlx_ptr, update, NULL);
	mlx_loop(mlx_ptr);
    return (0);
}


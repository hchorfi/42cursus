/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <hchorfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 20:52:51 by hchorfi           #+#    #+#             */
/*   Updated: 2020/10/27 14:11:18 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./mlx/mlx.h"
# include "get_next_line.h"
# include "./libft/libft.h"
# include <stdio.h>
# include <math.h>
# include <limits.h>

#define tile_size 64
//#define map_cols 29
//#define map_rows 14
#define	max_w_width 1920
#define	max_w_height 1080
#define win_width 1920
#define num_rays win_width
#define PI 3.1415926535
#define	fov_angle 60 * (PI / 180)
#define minimap_sf 1
#define	NO 0
#define SO 1
#define WE 2
#define EA 3
#define SP 4

#ifdef __linux__
	#define W 119
	#define A 97
	#define D 100
	#define	S 115
	#define L 65361
	#define	R 65363
#endif
#ifdef __APPLE__
	#define W 13
	#define A 0
	#define D 2
	#define	S 1
	#define L 123
	#define	R 124
#endif

typedef struct {
	float	x;
	float	y;
	float		r;
	int		turn_direction;
	int		walk_direction;
	float	rotation_angle;
	float	walk_speed;
	float	turn_speed;
	int		color;
	float	step;
}			t_player;
t_player	player;

typedef struct {
	float 	angle;
	float	wall_hitx;
	float	wall_hity;
	float	distance;
	int		vertical_hit;
	int		face_up;
	int		face_down;
	int		face_left;
	int		face_right;
	int		wall_content;
	int		strip_id;
}			t_ray;
t_ray		ray[num_rays];

typedef struct s_map_info{
	t_list	*line_list;
	char	**lines;
	int		x;
	int		y;
	int		tile;
	int		cols;
	int		rows;
	int		width;
	int		height;
	int		check_pose;
}			t_map;
t_map		map_info;

typedef struct {
    void	*img;
    int     *addr;
	void	*mlx_ptr;
	void	*win_ptr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
	int		w_width;
	int		w_height;
}               t_mlx_data;
t_mlx_data		mlx_data;

typedef struct  s_texture {
    unsigned int	*txt[5];
	char			*file[5];
	void			*img[5];
	int				tmp[5];
	int				tile;
	int				type;
	int				x;
	int				y;
}               t_texture;
t_texture		txt;

typedef struct {
	int		    face_up;
	int		    face_down;
	int		    face_left;
	int		    face_right;
	float	    x_intercept;
	float	    y_intercept;
	float	    x_step;
	float	    y_step;
	int		    found_hor_wal_hit;
	int		    found_ver_wal_hit;
	float	    hor_wal_hit_x;
	float	    hor_wal_hit_y;
	int		    hor_wal_content;
	float	    next_hor_touch_x;
	float	    next_hor_touch_y;
	float	    ver_wal_hit_x;
	float	    ver_wal_hit_y;
	int		    ver_wal_content;
	float	    next_ver_touch_x;
	float	    next_ver_touch_y;
	float	    x_to_check;
	float	    y_to_check;
	float	    hor_hit_distance;
	float	    ver_hit_distance;
}			    t_data;
t_data		    data;

typedef struct  s_wall_3d
{
    float       wal_3d_distance;
	float       distance_pro_plan;
	float       pro_wall_hie;
	int         wall_strip_hie;
	int         wal_top;
	int         wal_bot;
}               t_wall_3d;
t_wall_3d       wall_3d;

typedef	struct 	s_sprite
{
	int			count;
	int			col;
	int			row;
	float		distence;
	float		angle;
	float		height;
	float		index;
	float		x;
	float		y;
}				t_sprite;
t_sprite		sprite[1000];


#endif

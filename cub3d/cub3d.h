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

# include <mlx.h>
# include "get_next_line.h"
# include "./libft/libft.h"
# include <stdio.h>
# include <math.h>
# include <limits.h>

# define TILE_SIZE 64
# define NUM_RAYS MAX_W_WIDTH
# define PI 3.1415926535
# define FOV_ANGLE 60 * (PI / 180)
# define MINIMAP_SF 1
# define ESC 53
# define NO 0
# define SO 1
# define WE 2
# define EA 3
# define SP 4
# define F 0
# define C 1
# define W 13
# define A 0
# define D 2
# define S 1
# define L 123
# define R 124

/*
**# ifdef __linux__
**# define W 119
**# define A 97
**# define D 100
**# define S 115
**# define L 65361
**# define R 65363
**# endif
*/

typedef struct		s_player
{
	float			x;
	float			y;
	float			r;
	int				indentation;
	int				turn_direction;
	int				walk_direction;
	float			rotation_angle;
	float			walk_speed;
	float			turn_speed;
	int				color;
	float			step;
}					t_player;
t_player			g_player;

typedef struct		s_ray
{
	float			angle;
	float			wall_hitx;
	float			wall_hity;
	float			distance;
	int				vertical_hit;
	int				face_up;
	int				face_down;
	int				face_left;
	int				face_right;
	int				wall_content;
	int				strip_id;
}					t_ray;
t_ray				g_ray[NUM_RAYS];

typedef struct		s_map_info
{
	t_list			*line_list;
	char			**lines;
	int				x;
	int				y;
	int				tile;
	int				cols;
	int				rows;
	int				width;
	int				height;
	int				check_ppose;
}					t_map;
t_map				g_map_info;

typedef struct		s_mlx_data
{
	void			*img;
	int				*addr;
	void			*mlx_ptr;
	void			*win_ptr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				w_width;
	int				w_height;
	int				save;
}					t_mlx_data;
t_mlx_data			g_mlx_data;

typedef struct		s_texture
{
	unsigned int	*txt[5];
	char			*file[5];
	void			*img[5];
	int				tmp[5];
	int				color[3];
	int				hex_color[2];
	int				tile;
	int				type;
	int				color_type;
	int				x;
	int				y;
}					t_texture;
t_texture			g_txt;

typedef struct		s_data
{
	int				face_up;
	int				face_down;
	int				face_left;
	int				face_right;
	float			x_intercept;
	float			y_intercept;
	float			x_step;
	float			y_step;
	int				found_hor_wal_hit;
	int				found_ver_wal_hit;
	float			hor_wal_hit_x;
	float			hor_wal_hit_y;
	int				hor_wal_content;
	float			next_hor_touch_x;
	float			next_hor_touch_y;
	float			ver_wal_hit_x;
	float			ver_wal_hit_y;
	int				ver_wal_content;
	float			next_ver_touch_x;
	float			next_ver_touch_y;
	float			x_to_check;
	float			y_to_check;
	float			hor_hit_distance;
	float			ver_hit_distance;
}					t_data;
t_data				g_data;

typedef struct		s_wall_3d
{
	float			wal_3d_distance;
	float			distance_pro_plan;
	float			pro_wall_hie;
	int				wall_strip_hie;
	int				wal_top;
	int				wal_bot;
}					t_wall_3d;
t_wall_3d			g_wall_3d;

typedef struct		s_sprite
{
	int				count;
	int				col;
	int				row;
	float			distence;
	float			angle;
	float			height;
	float			index;
	float			x;
	float			y;
}					t_sprite;
t_sprite			g_sprite[1000];

typedef struct		s_key
{
	int				r;
	int				no;
	int				so;
	int				we;
	int				ea;
	int				s;
	int				f;
	int				c;
}					t_key;
t_key				g_key;

typedef	struct		s_bm_file_header
{
	unsigned char	type[2];
	int				file_size;
	short			reserved1;
	short			reserved2;
	unsigned int	offset_bits;
}					t_bm_file_header;
t_bm_file_header	g_bm_fh;

typedef struct		s_bm_image_header
{
	unsigned int	size_header;
	unsigned int	width;
	unsigned int	height;
	short int		planes;
	short int		bit_count;
	unsigned int	compression;
	unsigned int	image_size;
	unsigned int	ppm_x;
	unsigned int	ppm_y;
	unsigned int	clr_used;
	unsigned int	clr_important;
}					t_bm_image_header;
t_bm_image_header	g_bm_ih;

typedef	struct		s_screenshot
{
	char			*header;
	int				width_in_bytes;
	char			*img;
	int				fd;
}					t_screenshot;
t_screenshot		g_sshot;

/*
** textures.c functions
*/

int					ft_textures(void);
int					check_txt(char *line);
int					valid_txt(char *file);
int					stock_txt(char *line, char **tab, int len);
int					check_sprite_txt(char *line);

/*
** readfile1.c functions
*/

int					readfile1(int fd, int n_line, int check);
int					readfile2(int fd, int empty);
int					check_and_stock(int check, char *line);
int					check_resolution(char *line);
int					fill_map(int i, int j, t_list *lst);

/*
** readfile2.c functions
*/

int					stock_resolution(char *line);
int					check_color(char *line);
int					stock_color(char *line);
int					valid_color(char *str, int len, int i);
int					valid_color2(int i, char **tab);

/*
** readfile3.c functions
*/

int					stock_map_line(char *line);
int					check_map_line(char *line, int check);
int					check_player_pos(char *c, int x, int y);
int					set_player(void);

/*
** map1.c functions
*/

int					validmap2(int i, int j);
int					validmap(int i, int j);
int					valid_zero(int i, int j);
int					valid_space(int i, int j);

/*
** mlx_utils.c functions
*/

void				my_mlx_pixel_put(int x, int y, int color);
int					exit_cube(void);
int					key_pressed(int key);
int					key_released(int key);
int					init_win(void);

/*
** sprite.c functions
*/

void				render_sprite(void);
void				sort_sprites(void);
void				draw_sprite(int index, double distance,
								double height, int color);
int					check_sprites_pos(char *c, int x, int y);
int					set_sprites(void);

/*
** raycasting1.c functions
*/

float				raycast_init(float ray_angle);
int					stock_raycast_data(float ray_angle, int strip_id);
void				cast_ray(float ray_angle, int strip_id);
void				cast_all_rays(void);
int					player_update(void);

/*
** raycasting2.c functions
*/

float				ver_raycast_init(float ray_angle);
void				vertical_hit(void);
int					hor_raycast_init(float ray_angle);
void				horizontal_hit(void);
int					wall_collision(float npx, float npy);

/*
** utils1.c functions
*/

float				dbpoints(float x1, float y1, float x2, float y2);
float				normalize(float angle);
int					isalldigit(char *str);
int					create_trgb(int t, int r, int g, int b);
void				init_val(void);

/*
** utils2.c functions
*/

int					free_dpointer(char **tab, int len);
int					char_chr(char c, char *str);
int					sprite_collision(float npx, float npy);
int					check_double_key(int type);

/*
** error.c functions
*/

int					line_prefix_error(void);
int					stock_errors(int e);
int					readfile_errors(int e);
int					mapline_errors(int e);
int					validmap_errors(int e);

/*
** render2d.c functions
*/

void				render_player(void);
void				render_all_rays(void);
void				render_map(void);
void				draw_square(int square_i, int square_j, int square_color);

/*
** render3d.c functions
*/

void				render_3d_walls(int i, int y);
void				init_3d(int i);
void				draw_walls(int y, int i);

/*
** screenshot.c functions
*/

int					screenshot(void);
void				create_image(void);
int					*get_colors(int color);
void				create_header(void);

#endif

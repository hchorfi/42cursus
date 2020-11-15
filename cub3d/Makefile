# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hchorfi <hchorfi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/31 20:36:35 by hchorfi           #+#    #+#              #
#    Updated: 2020/10/24 19:12:13 by hchorfi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

LIBFT_PATH = ./libft
LIBFT_LIB = ft

MLX_PATH = /usr/local/lib
MLX_LIB = mlx

SRCS = cub3d.c readfile1.c readfile2.c readfile3.c sprite.c raycasting1.c \
		raycasting2.c utils1.c utils2.c error.c render2d.c render3d.c \
		mlx_utils.c textures.c map1.c get_next_line.c get_next_line_utils.c \
		screenshot.c

OBJS = $(SRCS:.c=.o)

WIDTH = $(shell osascript -e 'tell application "Finder" to get bounds of \
			window of desktop' | cut -d ',' -f3 | tr -d ' ')

HEIGHT = $(shell osascript -e 'tell application "Finder" to get bounds of \
			window of desktop' | cut -d ',' -f4 | tr -d ' ')

FLAGS = -Werror -Wextra -Wall

ASAN = -g -fsanitize=address

$(NAME) :
	gcc $(FLAGS) -D MAX_W_WIDTH=$(WIDTH) -D MAX_W_HEIGHT=$(HEIGHT) -c $(SRCS)
	make -C $(LIBFT_PATH)
	gcc $(OBJS) -L $(MLX_PATH) -l$(MLX_LIB) -L $(LIBFT_PATH) -l$(LIBFT_LIB) \
	-framework OpenGL -framework AppKit -o $(NAME)
	
all: $(NAME)

clean:
	rm -rf $(OBJS)
	make clean -C $(LIBFT_PATH)

fclean:
	rm -rf $(NAME) $(OBJS)
	make fclean -C $(LIBFT_PATH)

re: fclean all
	
#Render the project
rlinux:
	gcc $(FLAGS) -c $(SRCS)
	make -C $(LIBFT_PATH)
	gcc -I /usr/local/include $(OBJS) -L $(MLX_PATH) -l$(MLX_LIB) -L $(LIBFT_PATH) -l$(LIBFT_LIB) -lm -lbsd -lX11 -lXext -g -fsanitize=address
	#gcc -g -I /usr/local/include *.c -L. -lftprintf -lft -L /usr/local/lib -lmlx -lm -lbsd -lX11 -lXext

rmac:
	gcc -g -I /usr/local/include *.c -L. -lftprintf -lft -L /usr/local/lib -lmlx -framework OpenGL -framework Appkit

 
##cc -g -I /user/local/inclue main.c -L /usr/local/lib/ -lmlx -framework OpenGL \
	-framework Appkit -fsanitize=address
leaks:
	./compile.sh 2 LC cub3d.c gcc readfile1.c screenshot.c readfile2.c readfile3.c sprite.c raycasting1.c raycasting2.c utils1.c utils2.c error.c render2d.c render3d.c mlx_utils.c textures.c map1.c get_next_line.c get_next_line_utils.c libft/*.c -o cub3d -L $(MLX_PATH) -lmlx -framework OpenGL -framework AppKit

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

NAME = cub3d

LIBFT_PATH = ../libft
LIBFT_LIB = ft

MLX_PATH = /usr/local/lib
MLX_LIB = mlx

SRCS = cub3d.c get_next_line.c get_next_line_utils.c

OBJS = $(SRCS:.c=.o)

FLAGS = 

$(NAME) :
	gcc $(FLAGS) -c $(SRCS)
	make -C $(LIBFT_PATH)
	gcc -I /usr/local/include $(OBJS) -L $(MLX_PATH) -l$(MLX_LIB) -L $(LIBFT_PATH) -l$(LIBFT_LIB) -framework OpenGL -framework AppKit -g -fsanitize=address

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
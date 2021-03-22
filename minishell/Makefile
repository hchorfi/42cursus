
NAME = minishell

LIBFT_PATH = ./libft
LIBFT_LIB = ft

SRCS = main.c get_next_line.c get_next_line_utils.c export.c env.c unset.c pwd.c cd.c bin.c parse/split.c echo.c exit.c

FLAGS = -Werror -Wextra -Wall

ASAN = #-g -fsanitize=address
$(NAME) :
	#make -C $(LIBFT_PATH)
	#gcc -g $(SRCS) -L $(LIBFT_PATH) -l$(LIBFT_LIB) -o $(NAME)
	gcc -g $(ASAN) $(SRCS) libft.a ../ft_printf/libftprintf.a -o $(NAME)
	
all: $(NAME)

clean:
	#make clean -C $(LIBFT_PATH)

fclean:
	rm -rf $(NAME)
	#make fclean -C $(LIBFT_PATH)

re: fclean all
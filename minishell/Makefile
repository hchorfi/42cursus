
NAME = minishell

LIBFT_PATH = ./libft
LIBFT_LIB = ft

SRCS = main.c\
		get_next_line.c\
		get_next_line_utils.c\
		export.c\
		export_utils.c\
		export_utils2.c\
		env.c\
		unset.c\
		pwd.c\
		cd.c\
		bin.c\
		bin_utils.c\
		parse/split.c\
		echo.c\
		exit.c\
		term.c\
		utils1.c\
		utils2.c\
		redirections.c\
		redirections_utils.c\
		builtin_utils.c\
		tockens.c

FLAGS = -Werror -Wextra -Wall

ASAN =  -g #-fsanitize=address
$(NAME) :
	#make -C $(LIBFT_PATH)
	#gcc -g $(SRCS) -L $(LIBFT_PATH) -l$(LIBFT_LIB) -o $(NAME)
	gcc -g $(ASAN) $(SRCS) libft/libft.a ft_printf/libftprintf.a -lncurses -o $(NAME)
	
all: $(NAME)

rebuild:
	make re -C libft ; make re -C ft_printf ; make re

clean:
	#make clean -C $(LIBFT_PATH)

fclean:
	rm -rf $(NAME)
	#make fclean -C $(LIBFT_PATH)

re: fclean all
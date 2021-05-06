
NAME = minishell

LIBFT_PATH = ./libft
LIBFT_LIB = ft

SRCS = main.c\
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
		parse/split_utils1.c\
		parse/split_utils2.c\
		parse/split_utils3.c\
		parse/split_utils4.c\
		parse/split_utils5.c\
		parse/split_utils6.c\
		echo.c\
		exit.c\
		term.c\
		term_keys.c\
		term_utils.c\
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
NAME = philo_one

SRCS = main.c\
		error.c\
		utils.c

FLAGS = -Werror -Wextra -Wall

ASAN =  -g -fsanitize=address
$(NAME) :
	gcc -g $(ASAN) $(SRCS) -o $(NAME)
	
all: $(NAME)

clean:

fclean:
	rm -rf $(NAME)

re: fclean all

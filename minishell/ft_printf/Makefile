# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hchorfi <hchorfi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/17 21:38:33 by hchorfi           #+#    #+#              #
#    Updated: 2019/12/07 23:03:13 by hchorfi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = libftprintf.a

TEST = hakuna_matata

SRC = ft_fill_width.c ft_fill_zeros.c ft_init_flags.c ft_isdigit.c ft_itoa.c\
		ft_memset.c ft_printf.c ft_type_u.c ft_putchar.c ft_type_x.c\
		ft_putstr.c ft_strdup.c ft_strjoin.c ft_strlen.c ft_substr.c\
		ft_type_c.c ft_type_d.c ft_type_p.c ft_type_percent.c ft_type_s.c\
		ft_chk_cnv.c

FLAGS = -Werror -Wextra -Wall

all: $(NAME)

OBG = ft_fill_width.o ft_fill_zeros.o ft_init_flags.o ft_isdigit.o ft_itoa.o\
		ft_memset.o ft_printf.o ft_type_u.o ft_type_x.o ft_putchar.o\
		ft_putstr.o ft_strdup.o ft_strjoin.o ft_strlen.o ft_substr.o\
		ft_type_c.o ft_type_d.o ft_type_p.o ft_type_percent.o ft_type_s.o\
		ft_chk_cnv.o

$(NAME) :
	gcc $(FLAGS) -c $(SRC)
	ar rc $(NAME) $(OBG)
	ranlib $(NAME)

test:
	gcc $(FLAGS) -o $(TEST) $(TEST).c -L. -lft

norme:
	norminette -R CheckForbiddenSourceHeader $(SRC) $(BSRC)

bonus:

clean:
	/bin/rm -f $(OBG)

fclean:
	/bin/rm -f $(NAME) $(OBG)

re: fclean all

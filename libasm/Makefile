# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hchorfi <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/14 16:47:38 by hchorfi           #+#    #+#              #
#    Updated: 2020/12/14 16:47:42 by hchorfi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libasm.a

SRCS = ft_strlen.s ft_strcpy.s ft_strcmp.s ft_read.s ft_write.s ft_strdup.s

OBGS = $(SRCS:.s=.o)

all: $(NAME)

$(NAME) :
	nasm -f macho64 ft_strlen.s -o ft_strlen.o
	nasm -f macho64 ft_strcpy.s -o ft_strcpy.o
	nasm -f macho64 ft_strcmp.s -o ft_strcmp.o
	nasm -f macho64 ft_write.s -o ft_write.o
	nasm -f macho64 ft_read.s -o ft_read.o
	nasm -f macho64 ft_strdup.s -o ft_strdup.o
	ar rc $(NAME) $(OBGS)
	ranlib $(NAME)

clean:
	/bin/rm -f $(OBGS)

fclean:
	/bin/rm -f $(NAME) $(OBGS)

re: fclean all

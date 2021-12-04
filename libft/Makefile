# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: viporten <viporten@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/23 20:57:36 by laclide           #+#    #+#              #
#    Updated: 2021/12/04 03:13:36 by viporten         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = libft.a

SRC = 	atoi.c		\
		itoa.c		\
		memalloc.c	\
		memset.c	\
		str_new.c	\
		strcat.c	\
		strcpy.c	\
		strdup.c	\
		strjoin.c	\
		strlen.c	\
		strncmp.c	\
		strsplit.c	\
		strsub.c	\
		true_atoi.c

OBJ = *.o

HEAD = ./includes

all : $(NAME)

$(NAME):
	clang -Wall -Wextra -Werror -c $(SRC) -I $(HEAD) && ar rc $(NAME) $(OBJ)

clean:
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY : all re clean fclean
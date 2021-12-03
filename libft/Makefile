# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: viporten <viporten@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/23 20:57:36 by laclide           #+#    #+#              #
#    Updated: 2021/12/04 00:21:52 by viporten         ###   ########.fr        #
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
	@echo "Compiling libft.."
	@clang -Wall -Wextra -Werror -c $(SRC) -I $(HEAD) && ar rc $(NAME) $(OBJ)
	@echo "libft Done !"

clean:
	@echo "Remove libft *.o  ..."
	@/bin/rm -f $(OBJ)
	@echo "Done !"

fclean: clean
	@echo "Remove lib ..."
	@/bin/rm -f $(NAME)
	@echo "Done !" 

re: fclean all

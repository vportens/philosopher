NAME = philo

NAME_B = philo_bonus

MAC =

MAC_B =

LIBFT = libft

FLAGS 	= -g -Wall -Wextra

LIB =  -L/usr/include

SRCS =		main.c						\
			go_to_life.c				\
			init.c						\
			destroy_all.c

SRCS_BONUS =


CC 		= gcc
OBJ 	= ${SRCS:.c=.o}
OBJS 	= *.o
OBJ_B = ${SRCS_BONUS:.c=.o}
OBJS_B = *.o


all :
	@make -C $(LIBFT)
	@make $(NAME)

.c.o:
	${CC} ${FLAGS} -c $< -o ${<:.c=.o} -I include/


$(NAME)	: $(OBJ)
	$(CC) $(FLAGS) -I libft/includes/ -I include/. $(OBJ) libft/libft.a -o $(NAME) $(LIB)

$(NAME_B) : $(OBJ_B)
	$(CC) $(FLAGS) -I libft/includes/ -I include/. $(OBJ_B) libft/libft.a -o $(NAME_B)

clean :
		@make clean -C $(LIBFT)
		@rm -rf $(OBJ)
		@rm -rf $(OBJ_B)

fclean : clean
		@rm -rf libft.a
		@make fclean -C $(LIBFT)
		@rm -rf $(OBJS)
		@rm -rf $(OBJS_B)
		@rm -rf $(NAME)
		@rm -rf $(NAME_B)

relinux : fclean LINUX

re : fclean all

bonus :
		@make -C $(LIBFT)
		@make ${NAME_B}

rebonus : fclean bonus

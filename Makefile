NAME = philo

NAME_B = philo_bonus

MAC =

MAC_B =-fsanitize=thread

LIBFT = libft

FLAGS 	= -g3 -Wall -Wextra #-lpthread #-fsanitize=thread

LIB =  -L/usr/include

SRCS =		srcs/main.c						\
			srcs/go_to_life.c				\
			srcs/init.c						\
			srcs/destroy_all.c				\
			srcs/utils.c						\
			srcs/waiting_fonction.c

SRCS_BONUS =


CC 		= clang
OBJ 	= ${SRCS:.c=.o}
OBJS 	= *.o
OBJ_B = ${SRCS_BONUS:.c=.o}
OBJS_B = *.o


all :
	@make -C $(LIBFT)
	@make $(NAME)

.c.o:
	${CC} ${FLAGS}  -o ${<:.c=.o} -c $< -I include/ -pthread


$(NAME)	: $(OBJ)
	$(CC) $(FLAGS) -I libft/includes/ -I include/. $(OBJ) libft/libft.a -o $(NAME) $(LIB) -lpthread

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

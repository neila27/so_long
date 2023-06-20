NAME		= so_long
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -g3 #-fsanitize=address
RM			= rm -rf

OBJ			= $(SRC:.c=.o)

SRC =	main.c \
		utils.c \
		utils2.c \
		utils3.c \
		utils4.c \
		utils5.c \

all:	$(NAME)

%.o : %.c
	${CC} -c -o $@ $^ -I./libft ${CFLAGS} -Imlx
	
$(NAME):	$(OBJ) 
			${MAKE} -C libft 
			${MAKE} -C mlx	
			$(CC) ${CFLAGS} -o ${NAME} ${OBJ} -Lmlx -lmlx -framework OpenGL -framework AppKit -L./libft -lft

libft:
			${MAKE} -C libft

clean:
			$(RM) $(OBJ)
			$(MAKE) -C libft clean
			$(MAKE) -C mlx clean

fclean:		clean
			$(RM) $(NAME)
			$(MAKE) -C libft fclean
			$(MAKE) -C mlx clean

re:			fclean all

.PHONY:		all libft clean fclean re

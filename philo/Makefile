NAME 		=	philo
CFLAGS 		= -Wall -Wextra -Werror
NORMFLAG 	= -R CheckForbiddenSourceHeader
SRC_DIR		= src
FILES		= philosophers.c
SRCS		= $(addprefix $(SRC_DIR)/, $(FILES))
OBJS 		= $(SRCS:.c=.o)

all: 		$(NAME)

$(NAME):	$(OBJS)
			gcc $(CFLAGS) $(SRCS) -o $(NAME)

%.o:		%.c
			gcc $(CFLAGS) -c $< -o $@

clean:
			rm $(OBJS)

fclean:		clean
			rm $(NAME)

re: 		fclean all

norm: 		norminette $(NORMFLAG) src

.PHONY:		all clean fclean re norm
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdomingu <jdomingu@student.42malaga.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/06 02:30:18 by jdomingu          #+#    #+#              #
#    Updated: 2023/04/06 04:10:17 by jdomingu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= philo
CFLAGS 		= -Wall -Wextra -Werror -pthread
NORMFLAG 	= -R CheckForbiddenSourceHeader
SRC_DIR		= src
FILES		= philosophers.c validation.c parser.c routine.c control_status.c free.c
SRCS		= $(addprefix $(SRC_DIR)/, $(FILES))
OBJS 		= $(SRCS:.c=.o)

all: 		$(NAME)

$(NAME):	$(OBJS)
			gcc $(CFLAGS) $(SRCS) -o $(NAME)

%.o:		%.c
			gcc $(CFLAGS) -c $< -o $@

clean:
			rm -f $(OBJS)

fclean:		clean
			rm -f $(NAME)

re: 		fclean all

norm:
			norminette $(NORMFLAG) src

.PHONY:		all clean fclean re norm

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdomingu <jdomingu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/06 02:30:18 by jdomingu          #+#    #+#              #
#    Updated: 2023/04/29 20:58:03 by jdomingu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= philo
CFLAGS 		= -Wall -Wextra -Werror -pthread -g
NORMFLAG 	= -R CheckForbiddenSourceHeader
SRC_DIR		= src
FILES		= philosophers.c validation.c parser.c routine.c control_status.c free.c list_utils.c
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

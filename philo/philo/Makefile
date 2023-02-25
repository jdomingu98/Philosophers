# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdomingu <jdomingu@student.42malaga.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/20 20:09:35 by jdomingu          #+#    #+#              #
#    Updated: 2023/02/25 18:35:06 by jdomingu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo
CFLAGS	= -Wall -Wextra -Werror #-g
SRCS	= src/philosophers.c src/libft_functions.c src/free_data.c src/routine.c \
		src/philo_utils.c
OBJS	= $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	gcc $(CFLAGS) $(SRCS) -o $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY:  all clean fclean re

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdomingu <jdomingu@student.42malaga.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/20 20:09:35 by jdomingu          #+#    #+#              #
#    Updated: 2023/02/20 20:18:20 by jdomingu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo
CFLAGS	= -Wall -Wextra -Werror
SRCS	= src/philosophers.c
OBJS	= $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c
	$(GCC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(GCC) $(CFLAGS) $(SRCS) -o $(NAME)

clean:
	$(RM) -rf $(OBJS)

fclean: clean
	$(RM) -rf $(NAME)

re: fclean all

.PHONY:  all clean fclean re

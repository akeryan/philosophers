# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akeryan <akeryan@student.42abudhabi.ae>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/08 19:39:51 by akeryan           #+#    #+#              #
#    Updated: 2024/03/09 10:44:02 by akeryan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo 

CC = cc# -pthreads
FLAGS = -Wall -Wextra -Werror

MANDATORY = philo.c \
			main.c \
			parsing.c \
			utils.c

OBJ = $(patsubst %.c, %.o, $(MANDATORY))

%.o: %.c 
	$(CC) $(FLAGS) -o $@ -c $< 


$(NAME): $(OBJ)
	$(CC) -o $@ $^

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
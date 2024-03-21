# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akeryan <akeryan@student.42abudhabi.ae>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/08 19:39:51 by akeryan           #+#    #+#              #
#    Updated: 2024/03/21 21:26:34 by akeryan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo 

CC = cc

FLAGS = -Wall -Wextra -Werror -g -fsanitize=address -pthread

MANDATORY = run.c \
			main.c \
			parsing.c \
			utils_0.c \
			utils_1.c \
			actions_0.c \
			actions_1.c \
			init.c 

OBJ = $(patsubst %.c, %.o, $(MANDATORY))

%.o: %.c 
	$(CC) $(FLAGS) -o $@ -c $< 


$(NAME): $(OBJ)
	$(CC) -fsanitize=address -pthread -o $@ $^

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
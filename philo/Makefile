# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/20 10:50:57 by jodone            #+#    #+#              #
#    Updated: 2026/02/02 14:51:48 by jodone           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=cc
NAME=philo

SRC_DIR= sources/
BONUS_DIR= philo_bonus/

SRC= $(SRC_DIR)philo.c

INCLUDES=-I includes/

OBJECT=$(SRC:.c=.o)
CFLAGS=-Wall -Wextra -Werror -g 

all: $(NAME)

$(NAME): $(OBJECT) 
		@$(CC) $(CFLAGS) $(OBJECT) -o $(NAME)
		@echo "Compil Success"

%.o: %.c
		@$(CC) $(CFLAGS) $(INCLUDES) $(CFLAGS) -c $< -o $@

clean:
		@rm -f $(OBJECT)
		@echo "clean success"

fclean: clean
		@rm -f $(NAME)
		@echo "fclean success"
		
re: fclean all

.PHONY: all clean fclean re bonus philo

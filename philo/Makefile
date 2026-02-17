# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jimbow <jimbow@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/20 10:50:57 by jodone            #+#    #+#              #
#    Updated: 2026/02/17 01:20:30 by jimbow           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=cc
NAME=philo

# COLOR
GREEN		:= \033[32m
RESET		:= \033[0m

# DIR
SRC_DIR		= sources/
UTILS		= $(SRC_DIR)utils/
BONUS_DIR	= philo_bonus/
OBJ_DIR		= objects

SRC			= $(SRC_DIR)philo.c \
			$(UTILS)ft_atoi.c \
			$(UTILS)get_time.c \
			$(UTILS)init.c

INCLUDES	=-I includes/

OBJECT		=$(SRC:%.c=$(OBJ_DIR)/%.o)
CFLAGS		=-Wall -Wextra -Werror -g 

all: $(NAME)

$(NAME): $(OBJECT) 
		@$(CC) $(CFLAGS) $(OBJECT) -o $(NAME)
		@echo "${GREEN}====   $(NAME)   ==== : >>>>>SUCCESS<<<<<${RESET}"

$(OBJ_DIR)/%.o: %.c
			@mkdir -p $(dir $@)
			@$(CC) $(CFLAGS) $(INCLUDES) $(CFLAGS) -c $< -o $@

clean:
		@if ls $(OBJECT) >/dev/null 2>&1; then \
		echo "${GREEN}====   $(NAME)   ==== : >>>OBJ CLEANED<<<${RESET}"; \
		fi
		@rm -f $(OBJECT)
		@rm -rf $(OBJ_DIR)

fclean: clean
		@if ls $(OBJECT) >/dev/null 2>&1; then \
		echo "${GREEN}====   $(NAME)   ==== : >>>ALL CLEANED<<<${RESET}"; \
		fi
		@rm -f $(NAME)
		
re: fclean all

.PHONY: all clean fclean re bonus

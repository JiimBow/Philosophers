# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/20 10:50:57 by jodone            #+#    #+#              #
#    Updated: 2026/02/19 14:22:49 by jodone           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=cc
NAME=philo

# COLOR
RED     := \033[31m
GREEN   := \033[1;38;5;46m
RESET   := \033[0m

# DIR
SRC_DIR		= sources/
UTILS		= $(SRC_DIR)utils/
PARSING		= $(SRC_DIR)parsing/
BASIC_FUNC	= $(UTILS)basic_func/
MONITOR		= $(SRC_DIR)monitor/
PHIL_TREAD	= $(SRC_DIR)phil_thread/
BONUS_DIR	= philo_bonus/
OBJ_DIR		= objects

SRC			= $(SRC_DIR)main.c \
			$(UTILS)get_time.c \
			$(UTILS)init.c \
			$(UTILS)clean.c \
			$(PARSING)parser.c \
			$(BASIC_FUNC)ft_atoi.c \
			$(BASIC_FUNC)ft_atol.c \
			$(BASIC_FUNC)check_digit.c \
			$(PHIL_TREAD)routine_process.c \
			$(MONITOR)monitor_routine.c

INCLUDES	=-I includes/

OBJECT		=$(SRC:%.c=$(OBJ_DIR)/%.o)
CFLAGS		=-Wall -Wextra -Werror -fsanitize=thread -g

all: $(NAME)

$(NAME): $(OBJECT) 
		@$(CC) $(CFLAGS) $(OBJECT) -o $(NAME)
		@printf "${GREEN}\r[▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬] SUCCESS 100%%${RESET}\n"

TOTAL := $(words $(SRC))
COUNT := 0

$(OBJ_DIR)/%.o: %.c
			@mkdir -p $(dir $@)
			@$(CC) $(CFLAGS) $(INCLUDES) $(CFLAGS) -c $< -o $@
			@$(eval COUNT=$(shell echo $$(($(COUNT)+1))))
			@PERCENT=$$(($(COUNT)*99/$(TOTAL))) ; \
			BAR=$$(($(COUNT)*39/$(TOTAL))) ; \
			if [ $$PERCENT -lt 33 ]; then \
				COLOR_CODE=196; \
			elif [ $$PERCENT -lt 66 ]; then \
				COLOR_CODE=208; \
			else \
				COLOR_CODE=226; \
			fi ; \
			printf "\033[38;5;%sm\r[" $$COLOR_CODE ; \
			i=1; while [ $$i -le $$BAR ]; do printf "▬"; i=$$((i+1)); done ; \
			while [ $$i -le 40 ]; do printf " "; i=$$((i+1)); done ; \
			printf "] LOADING %3d%%\033[0m" $$PERCENT ; \
			printf " made by mgarnier"

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

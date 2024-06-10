# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ddel-bla <ddel-bla@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/06 12:41:03 by ddel-bla          #+#    #+#              #
#    Updated: 2024/06/10 16:26:05 by ddel-bla         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo_bonus
CC		= gcc
RM		= rm -rf
CFLAGS	= -g -O3 -Wall -Werror -Wextra -pthread -lpthread
NORM 	= norminette

INCLUDE	= -L -lft 

OBJS_D	= objs/
SRCS	=  main_bonus.c src_actions_bonus.c src_philo_bonus.c src_world_bonus.c \
		utils_scan_bonus.c utils_err_bonus.c utils_sem_bonus.c utils_strings.c \
		utils_time_bonus.c

OBJS 	= $(addprefix $(OBJS_D), $(SRCS:.c=.o))

all: $(OBJS_D) $(NAME)

$(OBJS_D)%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(INCLUDE) 
	@echo "$(BLUE)philo - Compiled!$(RESET)"

$(OBJS_D):
	mkdir -p $(OBJS_D)

clean:
	$(RM) $(OBJS_D) 

fclean: clean
	$(RM) $(NAME)

norm :
	@$(NORM) $(SRCS)

valgrind_race: re
	@echo "\033[1;33m\nChecking for race conditions with valgrind...\033[0m"
	valgrind --tool=helgrind -s ./$(NAME) 10 1000 200 200 2

valgrind_leaks: re
	@echo "\033[1;33m\n Valrind Memory leaks with valgrind...\033[0m"
	valgrind --leak-check=full ./$(NAME) 10 1000 200 200 2

re: fclean all

.PHONY: all re clean fclean debug 
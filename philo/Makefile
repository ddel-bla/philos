# **************************************************************************** #
#																			  #
#														 :::	  ::::::::	#
#	Makefile										   :+:	  :+:	:+:	#
#													 +:+ +:+		 +:+	  #
#	By: ddel-bla <ddel-bla@student.42madrid.com	+#+  +:+	   +#+		 #
#												 +#+#+#+#+#+   +#+			#
#	Created: 2024/05/10 20:24:57 by ddel-bla		  #+#	#+#			  #
#	Updated: 2024/05/20 08:26:53 by ddel-bla		 ###   ########.fr		#
#																			  #
# **************************************************************************** #
 
NAME	= philo
CC		= gcc
RM		= rm -rf
CFLAGS	= -g -O3 -Wall -Werror -Wextra -pthread #-lpthread
NORM 	= norminette

INCLUDE	= -L -lft 
#DEBUG	= -fsanitize=address,leak 
DEBUG	= -fsanitize=thread

OBJS_D	= objs/
SRCS	= init_parse.c init_philo.c init_threads.c init_world.c main.c \
			utils_locks.c utils_time.c syncro.c utils.c
OBJS 	= $(addprefix $(OBJS_D), $(SRCS:.c=.o))

all: $(OBJS_D) $(NAME)

$(OBJS_D)%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(INCLUDE) 
	@echo "$(BLUE)philo - Compiled!$(RESET)"

$(OBJS_D):
	mkdir -p $(OBJS_D)

debug: CFLAGS += $(DEBUG)
debug: all

clean:
	$(RM) $(OBJS_D) 

fclean: clean
	$(RM) $(NAME)

norm :
	@$(NORM) $(SRCS)

valgrind_race: re
	@echo "\033[1;33m\nChecking for race conditions with valgrind...\033[0m"
	valgrind --tool=helgrind ./$(NAME) 5 50000 200 200 5

valgrind_leaks: re
	@echo "\033[1;33m\n Valrind Memory leaks with valgrind...\033[0m"
	valgrind --leak-check=full ./$(NAME) 5 50000 200 200 5

re: fclean all

.PHONY: all re clean fclean debug 
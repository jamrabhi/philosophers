# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jamrabhi <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/22 03:58:02 by jamrabhi          #+#    #+#              #
#    Updated: 2022/05/22 03:58:04 by jamrabhi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

CC = gcc

CFLAGS = -Wall -Wextra -Werror -pthread

SRC = src/main.c \
		src/parsing/parsing.c \
		src/utils/exit_fail.c src/utils/ft_atoi.c src/utils/ft_atol.c \
		src/philosophers/philo.c src/philosophers/case_one.c src/utils/timer.c \
		src/philosophers/mutex_utils.c src/philosophers/activity.c \
		src/philosophers/check_alive.c

OBJ = $(SRC:.c=.o)

INCDIR = include/

MAKEFLAGS += --no-print-directory

all: $(NAME)

$(NAME) : $(OBJ)
	@echo "Compiling philo ..."
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "DONE"

.c.o:
	@${CC} ${CFLAGS} -I $(INCDIR) -c $< -o $@

clean:
	@echo "Deleting philo objects files ..."
	@rm -f $(OBJ)
	@echo "DONE"

fclean: clean
	@echo "Deleting philo's binary ..."
	@rm -f $(NAME)
	@echo "DONE"

re: fclean all

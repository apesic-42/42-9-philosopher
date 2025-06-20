# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apesic <apesic@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/20 10:21:11 by apesic            #+#    #+#              #
#    Updated: 2025/06/20 10:23:58 by apesic           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



NAME	=	philo

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror
AR		=	ar

PHILO_DIR = .
PHILO_SRC =		main\
				init\
				init_utils\
				simulation\
				simulation_utils\


PHILO_DS = $(addprefix $(PHILO_DIR)/, $(addsuffix .c, $(PHILO_SRC)))
OBJS = $(PHILO_DS:.c=.o)


all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o:%.c
	$(CC) $(FLAGS) -I./ -c $< -o $@

clean:
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all




.PHONY: all clean fclean re

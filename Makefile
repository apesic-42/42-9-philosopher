

NAME	=	philo

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror
AR		=	ar

PHILO_DIR = .
PHILO_SRC =		main\
				init\
				simulation\


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

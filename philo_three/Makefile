NAME	=	philo_three
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror

SRCS	=	./srcs/main.c \
			./srcs/monitor.c \
			./srcs/life_of_cadet.c \
			./srcs/utils.c 

INCS	=	-I ./srcs
OBJS	=	$(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(SRCS) $(INCS)

.c.o :
	$(CC) $(CFLAGS) -c $< -o $@ $(INCS)

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all
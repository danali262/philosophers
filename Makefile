NAME = philo

SRC = \
	main.c \
	input.c\
	threads.c\
	utilities.c

OBJS = $(SRC:.c=.o)
CFLAGS = -Wall -Werror -Wextra -O0 -g 

CC = gcc

all: $(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -lpthread

%.o:	%.c
			$(CC) $(CFLAGS) -c $< -o $@

clean:
			rm -f $(OBJS)

fclean: 	clean
			rm -f $(NAME)

re: fclean all 
    
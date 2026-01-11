NAME = philo

CC = cc

CFLAGS = -Wall -Werror -Wextra -pthread

LIB = libphilo.a

DEBUGFLAG = -g

SRC = main.c routine.c utils.c calc_time_now.c ft_atoi.c ft_calloc.c monitor.c create_philos.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(LIB)
	$(CC) $(CFLAGS) -L. $(LIB) -o $(NAME)

$(LIB) : $(OBJ)
	ar rcs $(LIB) $(OBJ)

clean:
	rm -rf $(OBJ) $(LIB)

fclean: clean
	rm -rf $(NAME)
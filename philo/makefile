NAME = philo

CC = cc

CFLAGS = -Wall -Werror -Wextra -pthread -g3

LIB = libphilo.a

DEBUGFLAG = -g

SRC = main.c routine.c data_init.c calc_time_now.c ft_atoi.c ft_calloc.c monitor.c create_philos.c \
put_err.c validation.c ft_strlen.c data_free.c routine_utils.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

debug: $(LIB)
	$(CC) $(CFLAGS) $(DEBUGFLAG) -L. $(LIB) -o $(NAME)
$(NAME): $(LIB)
	$(CC) $(CFLAGS) -L. $(LIB) -o $(NAME)

$(LIB) : $(OBJ)
	ar rcs $(LIB) $(OBJ)

clean:
	rm -rf $(OBJ) $(LIB)

fclean: clean
	rm -rf $(NAME)

re: fclean all

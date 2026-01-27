NAME = philo

CC = cc

CFLAGS = -Wall -Werror -Wextra -pthread 

LIB = libphilo.a

DEBUGFLAG = -g3

SRC = main.c routine.c data_init.c calc_time_now.c ft_atoi.c ft_calloc.c monitor.c create_philos.c \
put_err.c validation.c ft_strlen.c data_free.c routine_utils.c eat.c is_all_num.c \
init_malloced_mutex.c

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

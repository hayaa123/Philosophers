NAME = philo

CC = cc

CFLAGS = -Wall -Werror -Wextra -pthread

LIB = libphilo.a

DEBUGFLAG = -g

SRC = main.c routine.c utils.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(LIB)
	$(CC) $(CFLAGS) -L. $(LIB) -o $(NAME)

$(LIB) : $(OBJ)
	ar rcs $(LIB) $(OBJ)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)
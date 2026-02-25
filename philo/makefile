NAME = philo

CC = cc

CFLAGS = -Wall -Werror -Wextra -pthread -I./includes

DEBUGFLAG = -g3

SRC_DIR = src
SRC = main.c routine.c data_init.c calc_time_now.c ft_atoi.c ft_calloc.c monitor.c create_philos.c \
put_err.c validation.c ft_strlen.c data_free.c routine_utils.c eat.c is_all_num.c \
init_malloced_mutex.c

OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

all: $(NAME)

debug: $(OBJ)
	$(CC) $(CFLAGS) $(DEBUGFLAG) $(OBJ) -o $(NAME)
	
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
		mkdir -p $(OBJ_DIR)
		$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(LIB)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean all re debug
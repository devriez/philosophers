NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
LFLAG = -lpthread

SRC_DIR = src/
INCLUDES_DIR = includes/

SRCS = $(SRC_DIR)main.c \
		$(SRC_DIR)free_and_error.c \
		$(SRC_DIR)init.c \
		$(SRC_DIR)observer.c \
		$(SRC_DIR)routine.c \
		$(SRC_DIR)routine_utils.c \
		$(SRC_DIR)utils.c \

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) $(LFLAGS) -I $(INCLUDES_DIR) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I $(INCLUDES_DIR) -c $< -o $@

clean:
		rm -f $(OBJS)

fclean: clean
		rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re

test1: 
		./philo 5 800 200 200
test2: 
		./philo 5 800 200 200 2
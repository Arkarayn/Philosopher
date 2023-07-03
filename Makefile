NAME = philo

RM_DIR = rm -rf

CC = clang

CFLAGS = -Wall -Wextra -Werror -g -pthread

HEADER_1 = headers/philo.h

SRCS_DIR = srcs/

OBJ_DIR = obj/

SRCS_FILES = main.c error_handling.c init.c utils.c philo.c

SRCS = $(addprefix $(SRCS_DIR), $(SRCS_FILES))

O_SRCS = $(addprefix $(OBJ_DIR), $(SRCS_FILES:.c=.o))

$(OBJ_DIR)%.o : $(SRCS_DIR)%.c $(HEADER_1)
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

BARS := "▰▱▱▱▱▱▱▱▱▱▱ 1%" "▰▰▱▱▱▱▱▱▱▱▱ 17%" "▰▰▰▱▱▱▱▱▱▱▱ 23%" "▰▰▰▰▱▱▱▱▱▱▱ 38%" "▰▰▰▰▰▱▱▱▱▱▱ 42%" \
	"▰▰▰▰▰▰▱▱▱▱▱ 51%" "▰▰▰▰▰▰▰▱▱▱▱ 65%" "▰▰▰▰▰▰▰▰▱▱▱ 79%" "▰▰▰▰▰▰▰▰▰▱▱ 87%" "▰▰▰▰▰▰▰▰▰▰ 94%" \
	"▰▰▰▰▰▰▰▰▰▰ 100%"

all: $(NAME)
	clear
	@for bar in $(BARS); do \
		echo "\n\n\t\033[1;31m$$bar\033[0m"; \
		sleep 0.1; \
		clear; \
	done



$(NAME): $(SRCS) $(O_SRCS)
	clear
	$(CC) $(CFLAGS) $(O_SRCS) -o $(NAME)
	clear

clean:
	$(RM_DIR) $(OBJ_DIR)
	$(RM) $(O_SRCS)
	clear

fclean: clean 
	$(RM) $(NAME)
	clear

re: fclean all
	clear

norm:
	norminette *

.PHONY: all clean fclean re push norm

FLAGS = -Wall -Wextra -Werror

NAME =	utils.a

CC = cc

SRC = ft_atoi.c ft_putchar_fd.c ft_bzero.c ft_calloc_e.c ft_strlen.c ft_power.c ft_putnbr_fd.c ft_putendl_fd.c ft_putstr_fd.c ft_strchr.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)

%.o: %.c utils.h
	@$(CC) $(FLAGS) -c $<

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re

FLAGS = -Wall -Wextra -Werror

CC = cc

NAME = client

NAME2 = server

UTILS = utils/utils.a

UTILS2 = utils/ft_atoi.c utils/ft_putstr_fd.c utils/ft_putnbr_fd.c utils/ft_putendl_fd.c utils/ft_putchar_fd.c utils/ft_power.c utils/ft_calloc_e.c utils/ft_bzero.c utils/ft_strchr.c utils/ft_strlen.c


INCLUDE = utils/utils.h

all: $(NAME) $(NAME2)

$(NAME) $(NAME2): $(UTILS) $(INCLUDE) $(UTILS2) client.c server.c minitalk.h
	@$(CC) $(FLAGS) -c client.c
	@$(CC) $(FLAGS) client.c utils/utils.a -o $(NAME)
	@$(CC) $(FLAGS) -c server.c
	@$(CC) $(FLAGS) server.c utils/utils.a -o $(NAME2)

$(UTILS) :
	@cd utils && make

clean:
	@cd utils && make clean
	@rm -f $(NAME2)
	@rm -f server.o
	@rm -f $(NAME)
	@rm -f client.o

fclean: clean
	@cd utils && make fclean

re: fclean all

.PHONY: all clean fclean re

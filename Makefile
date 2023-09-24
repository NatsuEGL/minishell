NAME = minishell
CC = cc
FLAGS =   -Wall -Wextra -Werror -g -fsanitize=address
LIBFT_A = libft/libft.a
LIBFT = libft/

SRC = SRC/main.c SRC/parsing.c SRC/utils.c SRC/check_input.c SRC/erorr_hundle.c SRC/quotes_hundle.c SRC/env.c SRC/str_utils.c SRC/export.c SRC/lst_utils.c SRC/unset.c SRC/expand.c SRC/expand2.c \
	SRC/echo.c SRC/execution.c
		
OBJ = $(SRC:.c=.o)

all : $(NAME)

%.o : %.c SRC/minishell.h libft/libft.h
	$(CC) $(FLAGS) -c $< -o $@

$(NAME) : $(OBJ) SRC/minishell.h libft/libft.h
	@make -s -C $(LIBFT) 
	$(CC) $(FLAGS) $(OBJ) -lreadline $(LIBFT_A) $(LDFLAGS) -o $(NAME)


clean :
	@rm -rf libft/*.o
	@rm -rf libftprintf/*.o
	@rm -rf $(OBJ)

fclean : clean
	@rm -rf $(LIBFT_A)
	@rm -rf $(NAME)

re : clean fclean all
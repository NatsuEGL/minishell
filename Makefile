NAME = minishell
CC = cc 
FLAGS =   -Wall -Wextra -Werror #-g -fsanitize=address
LIBFT_A = libft/libft.a
LIBFT = libft/

SRC = main.c parsing.c utils.c check_input.c erorr_hundle.c quotes_hundle.c env.c str_utils.c export.c lst_utils.c unset.c expand.c expand2.c \
	echo.c execution.c cd.c pwd.c execution_utiles.c signals.c execution2.c execution3.c execution4.c execution5.c exit.c \
	cd2.c cd3.c check_input_norm.c exec_norm1.c expand3.c expand4.c exec_norm2.c exec_norm3.c exec_norm4.c exec_norm5.c env_norm.c export_norm.c  export_parsing.c export_parsing2.c
		 
OBJ = $(SRC:.c=.o)

all : $(NAME)

%.o : %.c minishell.h libft/libft.h
	$(CC) $(FLAGS) $(CPPFLAGS)  -c $< -o $@

$(NAME) : $(OBJ) minishell.h libft/libft.h
	@make -s -C $(LIBFT) 
	$(CC) $(FLAGS) $(OBJ) -lreadline $(LDFLAGS) $(LIBFT_A) $(LDFLAGS) -o $(NAME)


clean :
	@rm -rf libft/*.o
	@rm -rf libftprintf/*.o
	@rm -rf $(OBJ)

fclean : clean
	@rm -rf $(LIBFT_A)
	@rm -rf $(NAME)

re : clean fclean all
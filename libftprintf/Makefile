# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aamhal <aamhal@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/15 10:05:38 by aamhal            #+#    #+#              #
#    Updated: 2022/11/16 09:22:57 by aamhal           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SOURCE = ft_putchar.c \
			ft_putstr.c \
			ft_putnbr.c \
			ft_puthexa.c \
			ft_putunbr.c \
			ft_putadress.c \
			ft_printf.c
			
NAME = libftprintf.a

Cp = cc

FLAGS = -Wall -Wextra -Werror

RM = rm -f

OBJECTS    = $(SOURCE:.c=.o)

%.o : %.c ft_printf.h
	$(CC) $(FLAGS) -c $<

$(NAME) : $(OBJECTS)
	ar rc $(NAME) $(OBJECTS)
    
all: $(NAME)
    
clean:
	$(RM) $(OBJECTS) 

fclean: clean
	$(RM) $(NAME) 

re: fclean all
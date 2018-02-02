# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afokin <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/02 14:43:27 by afokin            #+#    #+#              #
#    Updated: 2018/02/02 14:43:30 by afokin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =	main.c
		
OBG = $(SRC:.c=.o)

FLAG = -Wextra -Werror -Wall

HED = ./

NAME = fractol

.PHONY : all clean fclean re

all: $(NAME)

$(NAME): $(OBG)
	@gcc -lmlx -framework OpenGL -framework AppKit $(FLAG) -I$(HED) $(OBG) -o $(NAME)

%.o: %.c
	@gcc $(FLAG) -I$(HED) -o $@ -c $<

clean:
	@rm -f $(OBG)
fclean: clean
	@rm -f $(NAME)

re: fclean all

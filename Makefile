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

NAME =		fractol

OBJ_DIR =	./bin/
SRC_DIR =	./src/
INC_DIR =	./inc/

SRC =		main.c img_funk.c event_hooks.c check_input.c fract_funk.c \
			mandelbrot_julia.c 

OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

FLAG = -Wextra -Werror -Wall

.PHONY : all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	gcc -lmlx -framework OpenGL -framework AppKit $(FLAG) -I$(INC_DIR) $(OBJ) -o $(NAME)

$(OBJ_DIR)%.o: %.c
	gcc $(FLAG) -c $< -o $@ -I $(INC_DIR)

clean:
	rm -f $(OBJ)
fclean: clean
	rm -f $(NAME)

re: fclean all

vpath %.c $(SRC_DIR)

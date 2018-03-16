# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sbrochar <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/15 17:13:45 by sbrochar          #+#    #+#              #
#    Updated: 2018/03/16 09:44:59 by ygaude           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

INC_DIR = ./include
SRC_DIR = ./src
OBJ_DIR = ./obj

LIB_DIR = ./libft
LIB_INC = $(LIB_DIR)

SRC = get_pipes.c \
	  get_rooms.c \
	  main.c \
	  output.c \
	  parsing_antfarm.c \
	  solver.c \
	  visu.c \
	  visu_debug.c \
	  visu_event.c \
	  visu_init.c \
	  visu_utils.c \
	  visu_put.c \
	  visu_update.c \
	  free_antfarm.c

OBJ = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC))

CC = clang
CFLAGS = -g -c -Wall -Wextra -Werror -I$(INC_DIR) -I$(LIB_INC) `sdl2-config --cflags`
LFLAGS = -L$(LIB_DIR) -lft `sdl2-config --libs` -lSDL2_gfx -lSDL2_ttf -lm

$(NAME): $(OBJ)
	make -C $(LIB_DIR)
	$(CC) -o $@ $^ $(LFLAGS)

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	make -C $(LIB_DIR) clean
	rm -f $(OBJ)

fclean: clean
	make -C $(LIB_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sbrochar <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/15 17:13:45 by sbrochar          #+#    #+#              #
#    Updated: 2018/03/22 10:35:00 by ygaude           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

INC_DIR = ./include
SRC_DIR = ./src
OBJ_DIR = ./obj

LIB_DIR = ./libft
LIBFT = $(LIB_DIR)/libft.a

SRC =	check_conflict.c find_shortest.c free_antfarm.c get_pipes.c get_rooms.c\
		handle_conflict.c lock_path.c main.c output.c parsing_antfarm.c\
		solver.c visu.c visu_debug.c visu_event.c visu_init.c visu_put.c\
		visu_update.c visu_utils.c

OBJ = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC))

CC = gcc
CFLAGS = -c -Wall -Wextra -Werror -I$(INC_DIR) -I$(LIB_DIR) `sdl2-config --cflags`
LFLAGS = -L$(LIB_DIR) -lft `sdl2-config --libs` -lSDL2_gfx -lSDL2_ttf -lm

all: $(LIBFT) $(NAME)

$(NAME): $(OBJ)
	@$(CC) -o $@ $^ $(LFLAGS)
	@printf "$(CC) -o $@ $^ $(LFLAGS)\n"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -o $@ $^
	@printf "Compiling... %-21s => %-21s\r" $^ $@

$(LIBFT):
	make -C $(LIB_DIR)

clean:
	make -C $(LIB_DIR) clean
	rm -f $(OBJ)

fclean: clean
	make -C $(LIB_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

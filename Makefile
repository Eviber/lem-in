# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/08/20 14:41:19 by vsporer           #+#    #+#              #
#    Updated: 2018/03/12 14:07:21 by gcollett         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 				lem-in
LIBFT =				libft/libft.a

C_RESET =			\033[0m
C_OK =				\033[32m
C_DEL =				\033[31m

PATH_LIBFT =		libft/
PATH_SRC =			src/
PATH_OBJ =			objs/
PATH_PARS =			$(PATH_SRC)parser/
PATH_VISU =			$(PATH_SRC)visu/
PATH_ALGO =			$(PATH_SRC)algo/
PATH_TOOLS =		$(PATH_SRC)tools/
PATH_SOLV =			$(PATH_SRC)solver/

CC =				gcc -g -Wall -Werror -Wextra
INC =				-I include/ -I libft/includes/ `sdl2-config --cflags`

SRC =				$(PATH_SRC)lem_in.c\
					$(PATH_SRC)lem_in_error.c

TOOLS =				$(PATH_TOOLS)del_strtab.c\
					$(PATH_TOOLS)del_strtab_except.c\
					$(PATH_TOOLS)del_room.c\
					$(PATH_TOOLS)get_room_index.c\
					$(PATH_TOOLS)clean_venv.c\
					$(PATH_TOOLS)search_room.c\
					$(PATH_TOOLS)create_string.c \
					$(PATH_TOOLS)memalloc_exit.c \


PARSER =			$(PATH_PARS)read_map.c\
					$(PATH_PARS)check_in.c\
					$(PATH_PARS)add_pipe.c\
					$(PATH_PARS)new_room.c

VISU =				$(PATH_VISU)lem_in_visu.c\
					$(PATH_VISU)default_zoom.c\
					$(PATH_VISU)draw_anthill.c\
					$(PATH_VISU)help_display_init.c\
					$(PATH_VISU)step_display_init.c\
					$(PATH_VISU)display_ants.c\
					$(PATH_VISU)get_rooms_name.c\
					$(PATH_VISU)reset_pos_map.c\
					$(PATH_VISU)move_step.c\
					$(PATH_VISU)get_step.c\
					$(PATH_VISU)event_manager.c

SOLVER = 			$(PATH_SOLV)search_path.c\
					$(PATH_SOLV)solver_tool.c\
					$(PATH_SOLV)send_ant.c

OBJ =				$(patsubst $(PATH_SRC)%.c, $(PATH_OBJ)%.o, $(SRC))\
					$(patsubst $(PATH_TOOLS)%.c, $(PATH_OBJ)%.o, $(TOOLS))\
					$(patsubst $(PATH_PARS)%.c, $(PATH_OBJ)%.o, $(PARSER))\
					$(patsubst $(PATH_VISU)%.c, $(PATH_OBJ)%.o, $(VISU))\
					$(patsubst $(PATH_SOLV)%.c, $(PATH_OBJ)%.o, $(SOLVER))

.PHONY: all clean fclean libft

all: libft $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@echo "Compiling $@ ...\033[K"
	@$(CC) $(INC) $^ -o $@ `sdl2-config --cflags --libs` -lSDL2_gfx -lSDL2_ttf
	@echo "$(C_OK)Done !$(C_RESET)"

$(LIBFT): libft

libft:
	@cd $(PATH_LIBFT) && $(MAKE)

$(PATH_OBJ)%.o: $(PATH_SRC)%.c
	@echo "Compiling $@\033[K\033[1A\r"
	@mkdir -p $(@D)
	@$(CC) $(INC) -c $< -o $@

$(PATH_OBJ)%.o: $(PATH_PARS)%.c
	@echo "Compiling $@\033[K\033[1A\r"
	@mkdir -p $(@D)
	@$(CC) $(INC) -c $< -o $@

$(PATH_OBJ)%.o: $(PATH_SOLV)%.c
	@echo "Compiling $@\033[K\033[1A\r"
	@mkdir -p $(@D)
	@$(CC) $(INC) -c $< -o $@
#
$(PATH_OBJ)%.o: $(PATH_VISU)%.c
	@echo "Compiling $@\033[K\033[1A\r"
	@mkdir -p $(@D)
	@$(CC) $(INC) -c $< -o $@

$(PATH_OBJ)%.o: $(PATH_TOOLS)%.c
	@echo "Compiling $@\033[K\033[1A\r"
	@mkdir -p $(@D)
	@$(CC) $(INC) -c $< -o $@

clean:
	@rm -rf $(PATH_OBJ)
	@cd $(PATH_LIBFT) && $(MAKE) clean
	@echo "$(C_DEL)Object files removed.$(C_RESET)"

fclean: clean
	@rm -f $(NAME)
	@rm -f $(LIBFT)
	@echo "$(C_DEL)$(NAME) and $(LIBFT) removed.$(C_RESET)"

test: all
	@echo "\\/\\/\\/\\/\\/\\/\\/BEGIN TEST\\/\\/\\/\\/\\/\\/\\/"
	@echo ""
	@./$(NAME) < map_test.txt
	@echo ""
	@echo "/\\/\\/\\/\\/\\/\\/\\END TEST/\\/\\/\\/\\/\\/\\/\\"

re: fclean all

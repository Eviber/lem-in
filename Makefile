# Flags

MODE = prod
CFLAGS = -Wall -Wextra -Werror -g
ifeq ($(MODE), dev)
CFLAGS =
endif
LDFLAGS += -I $(DIR_INC)
LDFLAGS += -I $(DIR_LIBFT)/inc
CFLAGS += -fsanitize=address
CLIBS 	+= -L $(DIR_LIBFT) -lft

#Directories
DIR_SRC = src
DIR_INC = include
DIR_OBJ = obj
DIR_LIBFT = libft

#Files

NAME = lem-in
LIBFT = $(DIR_LIBFT)/libft.a

SRC = $(addprefix $(DIR_SRC)/,$(SRC_F))
INC = $(addprefix $(DIR_INC)/,$(INC_F))
OBJ = $(subst $(DIR_SRC),$(DIR_OBJ),$(subst .c,.o,$(SRC)))


SRC_F	+= main.c
SRC_F	+= parser.c
SRC_F 	+= room.c
SRC_F	+= resolve.c

#SRC_F	+= xfunc.c

INC_F	+= cookielem_in.h


#Regles

all: $(NAME)

$(NAME): $(LIBFT) $(DIR_OBJ) $(OBJ)
	gcc -o $@ $(CLIBS) $(OBJ) $(CFLAGS) $(LIBFT)
	echo "lem-in compilation done"

$(DIR_OBJ)/%.o: $(DIR_SRC)/%.c $(INC)
	@clang -o $@ -c $< $(CFLAGS) $(LDFLAGS)

clean:
	@rm -f $(OBJ)
	@rm -rf $(DIR_OBJ)
	@make -C $(DIR_LIBFT) clean

fclean: clean
	@rm -f $(NAME)
	@make -C $(DIR_LIBFT) fclean

re: fclean all

$(LIBFT):
	@make -C $(DIR_LIBFT)
	@make -C $(DIR_LIBFT) clean

$(DIR_OBJ):
	@mkdir $(DIR_OBJ)
# Supp
dev:
	@make MODE=dev

.PHONY: all clean fclean re

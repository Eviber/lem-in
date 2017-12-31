# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vsporer <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/15 15:51:49 by vsporer           #+#    #+#              #
#    Updated: 2017/12/12 19:19:00 by vsporer          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 			libft.a

INCLUDES =		includes/
PATH_BASE =		src/
PATH_OBJ =		obj/
PATH_GNL =		$(PATH_BASE)get_next_line/
PATH_FTPF_SRC =	$(PATH_BASE)ft_printf/
PATH_FTPF_ATT =	$(PATH_FTPF_SRC)attribute/
PATH_FTPF_CNV =	$(PATH_FTPF_SRC)conv_fcn/
PATH_FTPF_PF =	$(PATH_FTPF_SRC)prec_field/

SRC_GNL =		$(PATH_GNL)get_next_line.c

SRC_FTPF =		$(PATH_FTPF_SRC)ft_printf.c\
				$(PATH_FTPF_SRC)ft_parser_printf.c\
				$(PATH_FTPF_SRC)ft_printf_clear_flag.c\
				$(PATH_FTPF_SRC)ft_printf_lenmod.c\
				$(PATH_FTPF_SRC)ft_printf_load_struct.c\
				$(PATH_FTPF_SRC)ft_printf_search_conv.c\
				$(PATH_FTPF_SRC)ft_printf_search_prec.c\
				$(PATH_FTPF_SRC)ft_printf_search_field.c\
				$(PATH_FTPF_SRC)ft_printf_switch.c\
				$(PATH_FTPF_SRC)ft_printf_tolst.c\
				$(PATH_FTPF_SRC)ft_printf_list.c\
				$(PATH_FTPF_SRC)ft_printf_tools.c

FTPF_ATT =		$(PATH_FTPF_ATT)ft_printf_get_minus.c\
				$(PATH_FTPF_ATT)ft_printf_get_zero.c\
				$(PATH_FTPF_ATT)ft_printf_attribute.c\
				$(PATH_FTPF_ATT)ft_printf_attribute_zero.c

FTPF_PF =		$(PATH_FTPF_PF)ft_printf_prec.c\
				$(PATH_FTPF_PF)ft_printf_field.c

FTPF_CONV =		$(PATH_FTPF_CNV)ft_conv_c.c\
				$(PATH_FTPF_CNV)ft_conv_di.c\
				$(PATH_FTPF_CNV)ft_conv_o.c\
				$(PATH_FTPF_CNV)ft_conv_b.c\
				$(PATH_FTPF_CNV)ft_conv_s.c\
				$(PATH_FTPF_CNV)ft_conv_u.c\
				$(PATH_FTPF_CNV)ft_conv_lc_cup.c\
				$(PATH_FTPF_CNV)ft_conv_ls_sup.c\
				$(PATH_FTPF_CNV)ft_conv_xp_xup.c\
				$(PATH_FTPF_CNV)ft_conv_percent.c\
				$(PATH_FTPF_CNV)ft_conv_p.c\
				$(PATH_FTPF_CNV)ft_conv_not_valid.c

SRCS =			$(PATH_BASE)ft_atoi.c\
				$(PATH_BASE)ft_atoull.c\
				$(PATH_BASE)ft_bzero.c\
				$(PATH_BASE)ft_isalnum.c\
				$(PATH_BASE)ft_isalpha.c\
				$(PATH_BASE)ft_isascii.c\
				$(PATH_BASE)ft_isdigit.c\
				$(PATH_BASE)ft_isprint.c\
				$(PATH_BASE)ft_memalloc.c\
				$(PATH_BASE)ft_memccpy.c\
				$(PATH_BASE)ft_memchr.c\
				$(PATH_BASE)ft_memcmp.c\
				$(PATH_BASE)ft_memcpy.c\
				$(PATH_BASE)ft_memdel.c\
				$(PATH_BASE)ft_memmove.c\
				$(PATH_BASE)ft_memset.c\
				$(PATH_BASE)ft_putchar.c\
				$(PATH_BASE)ft_putnbr.c\
				$(PATH_BASE)ft_putstr.c\
				$(PATH_BASE)ft_strcat.c\
				$(PATH_BASE)ft_strchr.c\
				$(PATH_BASE)ft_strclr.c\
				$(PATH_BASE)ft_strcmp.c\
				$(PATH_BASE)ft_strcpy.c\
				$(PATH_BASE)ft_strdel.c\
				$(PATH_BASE)ft_strdup.c\
				$(PATH_BASE)ft_strequ.c\
				$(PATH_BASE)ft_striter.c\
				$(PATH_BASE)ft_striteri.c\
				$(PATH_BASE)ft_strjoin.c\
				$(PATH_BASE)ft_strlcat.c\
				$(PATH_BASE)ft_strlen.c\
				$(PATH_BASE)ft_strmap.c\
				$(PATH_BASE)ft_strmapi.c\
				$(PATH_BASE)ft_strncat.c\
				$(PATH_BASE)ft_strncmp.c\
				$(PATH_BASE)ft_strncpy.c\
				$(PATH_BASE)ft_strnequ.c\
				$(PATH_BASE)ft_strnew.c\
				$(PATH_BASE)ft_strnstr.c\
				$(PATH_BASE)ft_strrchr.c\
				$(PATH_BASE)ft_strstr.c\
				$(PATH_BASE)ft_strsub.c\
				$(PATH_BASE)ft_strtrim.c\
				$(PATH_BASE)ft_tolower.c\
				$(PATH_BASE)ft_toupper.c\
				$(PATH_BASE)ft_strsplit.c\
				$(PATH_BASE)ft_itoa.c\
				$(PATH_BASE)ft_putendl.c\
				$(PATH_BASE)ft_putchar_fd.c\
				$(PATH_BASE)ft_putstr_fd.c\
				$(PATH_BASE)ft_putendl_fd.c\
				$(PATH_BASE)ft_putnbr_fd.c\
				$(PATH_BASE)ft_lstadd.c\
				$(PATH_BASE)ft_lstdel.c\
				$(PATH_BASE)ft_lstdelone.c\
				$(PATH_BASE)ft_lstiter.c\
				$(PATH_BASE)ft_lstmap.c\
				$(PATH_BASE)ft_lstnew.c\
				$(PATH_BASE)ft_ulltoa_base.c\
				$(PATH_BASE)ft_strjoin_free.c\
				$(PATH_BASE)ft_strsubstitute.c\
				$(PATH_BASE)ft_countchar.c\
				$(PATH_BASE)ft_wcharlen.c\
				$(PATH_BASE)ft_wcrtomb.c\
				$(PATH_BASE)ft_wcsrlen.c\
				$(PATH_BASE)ft_wcsrtombs.c\
				$(PATH_BASE)ft_putstr_minlen.c\
				$(PATH_BASE)ft_putstr_minlen_fd.c\
				$(PATH_BASE)ft_strstr_minlen.c\
				$(PATH_BASE)ft_lstaddback.c\
				$(PATH_BASE)ft_nbrlen.c\
				$(PATH_BASE)ft_split_whitespaces.c\
				$(PATH_BASE)ft_strtablen.c\
				$(PATH_BASE)ft_strtabadd.c\
				$(PATH_BASE)ft_error.c\
				$(PATH_BASE)ft_swap_ptr.c

OBJ =			$(patsubst $(PATH_BASE)%.c, $(PATH_OBJ)%.o, $(SRCS))\
				$(patsubst $(PATH_GNL)%.c, $(PATH_OBJ)%.o, $(SRC_GNL))\
				$(patsubst $(PATH_FTPF_SRC)%.c, $(PATH_OBJ)%.o, $(SRC_FTPF))\
				$(patsubst $(PATH_FTPF_ATT)%.c, $(PATH_OBJ)%.o, $(FTPF_ATT))\
				$(patsubst $(PATH_FTPF_PF)%.c, $(PATH_OBJ)%.o, $(FTPF_PF))\
				$(patsubst $(PATH_FTPF_CNV)%.c, $(PATH_OBJ)%.o, $(FTPF_CONV))

CC =			gcc -Wall -Wextra -Werror
CCI =			-I includes/

all: $(NAME)

$(NAME) : $(OBJ)
	@echo "Compiling libft.a ...\033[K"
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo "\033[32mDone !\033[0m"

$(PATH_OBJ)%.o : $(PATH_BASE)%.c
	@mkdir -p $(@D)
	@echo "\033[36mCompiling $@\033[0m\033[K\033[1A\r"
	@$(CC) $(CCI) -c $< -o $@

$(PATH_OBJ)%.o : $(PATH_GNL)%.c
	@mkdir -p $(@D)
	@echo "\033[1;34mCompiling $@\033[0m\033[K\033[1A\r"
	@$(CC) $(CCI) -c $< -o $@

$(PATH_OBJ)%.o : $(PATH_FTPF_SRC)%.c
	@mkdir -p $(@D)
	@echo "\033[33mCompiling $@\033[0m\033[K\033[1A\r"
	@$(CC) $(CCI) -c $< -o $@

$(PATH_OBJ)%.o : $(PATH_FTPF_ATT)%.c
	@mkdir -p $(@D)
	@echo "\033[33mCompiling $@\033[0m\033[K\033[1A\r"
	@$(CC) $(CCI) -c $< -o $@

$(PATH_OBJ)%.o : $(PATH_FTPF_PF)%.c
	@mkdir -p $(@D)
	@echo "\033[33mCompiling $@\033[0m\033[K\033[1A\r"
	@$(CC) $(CCI) -c $< -o $@

$(PATH_OBJ)%.o : $(PATH_FTPF_CNV)%.c
	@mkdir -p $(@D)
	@echo "\033[33mCompiling $@\033[0m\033[K\033[1A\r"
	@$(CC) $(CCI) -c $< -o $@


.PHONY: clean fclean re

clean:
	@rm -rf $(PATH_OBJ)
	@echo "\033[31mClean all .o : Done\033[0m"

fclean: clean
	@rm -rf $(NAME)
	@echo "\033[31mDelete libft.a : Done\033[0m"

re: fclean all

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mqian <mqian@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/19 14:50:31 by mqian             #+#    #+#              #
#    Updated: 2019/08/20 14:33:00 by mqian            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

C = clang

NAME = libftprintf.a

FLAGS = -Wall -Wextra -Werror -O2

LIBFT = libft

DIR_S = sources

DIR_O = temporary

HEADER = include

SOURCES = ft_printf.c formatters1.c formatters2.c format_c_helpers.c \
	format_f_helpers.c format_f_helpers_2.c format_f_helpers_3.c \
	format_f_helpers_4.c dispatch.c d_helpers.c d_helpers_2.c \
	format_o_helpers.c format_o_helpers_2.c format_p_helpers.c \
	format_p_helpers_2.c format_s_helpers.c format_s_helpers_2.c \
	format_u_helpers.c format_u_helpers_2.c format_x_helpers.c \
	format_x_helpers_2.c format_x_upper_helpers.c format_x_upper_helpers_2.c \
	parse.c struct.c utility_1.c utility_2.c utility_3.c format_p_helpers_3.c

SRCS = $(addprefix $(DIR_S)/,$(SOURCES))

OBJS = $(addprefix $(DIR_O)/,$(SOURCES:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	@make -C $(LIBFT)
	@cp libft/libft.a ./$(NAME)
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)

$(DIR_O)/%.o: $(DIR_S)/%.c
	@mkdir -p temporary
	@$(CC) $(FLAGS) -I $(HEADER) -o $@ -c $<

clean:
	@rm -f $(OBJS)
	@rm -rf $(DIR_O)
	@make clean -C $(LIBFT)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT)

re: fclean all
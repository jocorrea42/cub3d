# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jocorrea <jocorrea@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/05 10:23:35 by jocorrea          #+#    #+#              #
#    Updated: 2024/02/24 16:31:46 by jocorrea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	main.c win.c

OBJS = $(SRCS:.c=.o)

CC = gcc

RM = rm -f

CFLAGS = -Wall -Wextra -Werror -MMD

INCLUDE = -Icub3d.h ./libft/libft.a ./mlx/libmlx.a -framework OpenGL -framework AppKit -framework Cocoa -framework Foundation

NAME = cub3d

DEPS= $(OBJS:.o=.d)

# Metodo implicito
%.o: %.c $(INCLUDE)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@


# Mis metodos
all: $(NAME)

-include $(DEPS)
$(NAME): $(OBJS)
	@ make bonus -C ./libft
	@ make -C ./mlx
	$(CC) $(CFLAGS) $(INCLUDE) $(OBJS) -o $(NAME)

clean:
	@ make clean -C ./libft
	@ make clean -C ./mlx
	@$(RM) $(OBJS) $(DEPS)

fclean: clean
	@$(RM) $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re

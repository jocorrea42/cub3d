# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jocorrea <jocorrea@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/24 12:54:52 by jocorrea          #+#    #+#              #
#    Updated: 2024/02/24 15:17:03 by jocorrea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	main.c win.c img_win.c drawing.c keys.c raycast.c

OBJS = $(SRCS:.c=.o)

CC = gcc

RM = rm -f

CFLAGS = -Wall -Wextra -Werror -MMD

INCLUDE = -Iwin.h ../libft/libft.a ../mlx/libmlx.a -framework OpenGL -framework AppKit -framework Cocoa -framework Foundation

NAME = win

DEPS= $(OBJS:.o=.d)

# Metodo implicito
%.o: %.c $(INCLUDE)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@


# Mis metodos
all: $(NAME)

-include $(DEPS)
$(NAME): $(OBJS)
	@ make bonus -C ../libft
	@ make -C ../mlx
	$(CC) $(CFLAGS) $(INCLUDE) $(OBJS) -o $(NAME)

clean:
	@ make clean -C ../libft
	@ make clean -C ../mlx
	@$(RM) $(OBJS) $(DEPS)

fclean: clean
	@$(RM) $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re

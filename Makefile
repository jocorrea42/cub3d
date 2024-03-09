NAME = cub3d

CC = gcc
CFLAGS = -Wall -Wextra -Werror -MMD

# External libraries
ft = libft/libft.a
mlx = mlx/libmlx.a  

# Folders
SRC_DIR = src
OBJ_DIR = obj
DEP_DIR = dep
INC_DIR = inc

# Source files
SRC = image_utils.c init_game.c key_event.c main.c move_event.c raycast.c square.c utils.c win.c

# Object files
OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))
DEP = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.d))

# Compile SRC files and move to folders
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c cub3d.h
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -Imlx -Ilibft -O3 -c -I. $< -o $@
	@mkdir -p $(DEP_DIR)
	@mv $(OBJ_DIR)/$*.d $(DEP_DIR)/

all: lib libmlx $(NAME)

$(NAME): $(OBJ) $(ft) $(mlx)
	$(CC) $(OBJ) -Llibft -lft -Lmlx -lmlx -L/usr/lib -Imlx -lXext -lX11 -lm -lz -o $(NAME)
	@echo "cub3d compiled!"

lib: 
	make -C libft

libmlx:
	make -C mlx

clean:
	rm -rf $(OBJ_DIR) $(DEP_DIR)
	make clean -C libft

fclean:
	rm -rf $(NAME) $(OBJ_DIR) $(DEP_DIR)
	make fclean -C libft
	make clean -C mlx	

re:	fclean all

-include $(DEP)

.PHONY: all re clean fclean
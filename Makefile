NAME = cub3d

CC = gcc
CFLAGS = -Wall -Wextra -Werror -MMD
LIBS_LINUX = -Lmlx_linux -lmlx -L/usr/lib -lXext -lX11 -lm -lz
LIBS_MACOS = -Lmlx -lmlx -framework OpenGL -framework AppKit

# External libraries
FT = libft/libft.a
ifeq ($(UNAME_S),Linux)
	MLX := mlx_linux/libmlx.a
else
	MLX := mlx/libmlx.a
endif

# Folders
SRC_DIR = src
OBJ_DIR = obj
DEP_DIR = dep
INC_DIR = inc

# Source files
SRC = image_utils.c init_game.c key_event.c main.c move_event.c raycast.c square.c \
	utils.c win.c ft_perror.c safe_allocation.c read_utils.c open_utils.c check_map.c \
	ft_strtok.c check_closed.c clean_utils.c fake_split.c

# Object files
OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))
DEP = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.d))

# Compile SRC files and move to folders
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c cub3d.h
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I. -Imlx -Ilibft -O3 -c $< -o $@
	@mkdir -p $(DEP_DIR)
	@mv $(OBJ_DIR)/$*.d $(DEP_DIR)/

# Determine OS
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
	LIBS := $(LIBS_LINUX)
else
	LIBS := $(LIBS_MACOS)
endif

all: $(NAME)

$(NAME): $(OBJ) $(FT) $(MLX)
	$(CC) $(OBJ) -Llibft $(LIBS) -lft -o $(NAME)
	@echo "Cub3d compiled!"

$(FT): 
	make -C libft

$(MLX):
ifeq ($(UNAME_S),Linux)
	make -C mlx_linux
else
	make -C mlx
endif

clean:
	rm -rf $(OBJ_DIR) $(DEP_DIR)
	make clean -C libft

fclean:
	rm -rf $(NAME) $(OBJ_DIR) $(DEP_DIR)
	make fclean -C libft
ifeq ($(UNAME_S),Linux)
	make clean -C mlx_linux
else
	make clean -C mlx
endif

re:	fclean all

-include $(DEP)

.PHONY: all re clean fclean

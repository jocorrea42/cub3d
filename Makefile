NAME = cub3d
BONUS_NAME = cub3d_bonus

CC = gcc
CFLAGS = -Wall -Wextra -Werror -MMD -g
LIBS = -Lmlx_linux -lmlx -L/usr/lib -lXext -lX11 -lm -lz
MLX = mlx_linux/libmlx.a
MLX_INCLUDE = -Imlx_linux
UNAME_S := $(shell uname -s)

# External libraries
ft = libft/libft.a
ifneq ($(UNAME_S),Linux)
	LIBS := -Lmlx -lmlx -framework OpenGL -framework AppKit
	MLX_INCLUDE := -Imlx
	MLX := mlx/libmlx.a
endif

# Folders
SRC_DIR = src
OBJ_DIR = obj
DEP_DIR = dep
INC_DIR = inc

# Base source files
SRC_BASE = image_utils.c main.c \
	move_event.c utils.c init_data.c \
	win.c ft_perror.c safe_allocation.c read_utils.c \
	open_utils.c check_map.c ft_strtok.c check_closed.c \
	clean_utils.c fake_split.c safe_allocation2.c \
	direction_rays.c invert_image.c

# Mandatory additional source files
SRC_MAND = init_game.c raycast.c draw.c parse_textures.c key_event.c

# Bonus source files
SRC_BONUS = bonus/init_game_bonus.c bonus/raycast_bonus.c bonus/draw_bonus.c \
	bonus/parse_textures_bonus.c bonus/key_event_bonus.c bonus/door_rays_bonus.c

# Combine base and mandatory source files
SRC = $(SRC_BASE) $(SRC_MAND)

# Combine base and bonus source files
SRC_ALL = $(SRC_BASE) $(SRC_BONUS)

# Object files
OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))
OBJ_ALL = $(addprefix $(OBJ_DIR)/,$(SRC_ALL:.c=.o))
DEP = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.d))
DEP_ALL = $(addprefix $(OBJ_DIR)/,$(SRC_ALL:.c=.d))

# Compile SRC files and move to folders
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c cub3d.h keys.h Makefile
	@mkdir -p $(OBJ_DIR)/$(dir $*)
	@$(CC) $(CFLAGS) -I. $(MLX_INCLUDE) -Ilibft -O3 -c $< -o $@
	@mkdir -p $(DEP_DIR)/$(dir $*)
	@mv $(OBJ_DIR)/$*.d $(DEP_DIR)/$(dir $*)

# Determine OS
UNAME_S := $(shell uname -s)

all: lib libmlx $(NAME)

bonus: lib libmlx $(BONUS_NAME)

$(BONUS_NAME): CFLAGS += -DBONUS
$(BONUS_NAME): $(OBJ_ALL) $(ft) $(MLX)
	$(CC) $(OBJ_ALL) -Llibft $(LIBS) -lft -o $(BONUS_NAME)

$(NAME): $(OBJ) $(ft) $(MLX)
	$(CC) $(OBJ) -Llibft $(LIBS) -lft -o $(NAME)

lib:
	make -C libft

libmlx:
	make -C $(dir $(MLX)) 2> /dev/null

clean:
	rm -rf $(OBJ_DIR) $(DEP_DIR)
	make clean -C libft

clean_bonus: clean

fclean:
	rm -rf $(NAME) $(OBJ_DIR) $(DEP_DIR)
	make fclean -C libft
	make clean -C $(dir $(MLX))

fclean_bonus:
	rm -rf $(BONUS_NAME) $(OBJ_DIR) $(DEP_DIR)
	make fclean -C libft
	make clean -C $(dir $(MLX))

re: fclean all

-include $(DEP)
-include $(DEP_ALL)

.PHONY: all re clean fclean clean_bonus fclean_bonus


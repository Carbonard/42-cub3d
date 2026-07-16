.PHONY: all clean fclean bonus

MLX_DIR = ./minilibx-linux

LIBFT_DIR = ./libft

CFLAGS = -Wall -Werror -Wextra -g3 #-fsanitize=address,undefined

LIBS = -lmlx -lXext -lX11 -lm

INCLUDES = -I $(MLX_DIR) -L $(MLX_DIR)

MINILIBX = $(MLX_DIR)/libmlx.a

LIBFT = $(LIBFT_DIR)/libft.a

FILES = main utils read_file load_config\
mlx_utils map_utils\
dyn_arrays math\
map minimap_init minimap\
render_screen render_vertical render_utils\
events_key\
player_mov\
close



SRC_DIR = src

OBJ_DIR = obj

SRC = $(FILES:%=$(SRC_DIR)/ft_cub3d_%.c)

OBJ = $(FILES:%=$(OBJ_DIR)/ft_cub3d_%.o)

NAME = cub3D

$(NAME): $(OBJ) $(MINILIBX) $(LIBFT)
	cc $(CFLAGS) $(INCLUDES) $^ $(LIBS) -o $@

$(OBJ_DIR):
	mkdir $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(SRC_DIR)/ft_cub3d.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@



FILES_BONUS = $(FILES)\
doors mouse_utils raycasting enemies set_config menu

SRC_DIR_BONUS = src_bonus

OBJ_DIR_BONUS = obj_bonus

SRC_BONUS = $(FILES_BONUS:%=$(SRC_DIR_BONUS)/ft_cub3d_%.c)

OBJ_BONUS = $(FILES_BONUS:%=$(OBJ_DIR_BONUS)/ft_cub3d_%.o)

bonus: $(OBJ_BONUS) $(MINILIBX) $(LIBFT)
	cc $(CFLAGS) $(INCLUDES) $^ $(LIBS) -o $(NAME)

$(OBJ_DIR_BONUS):
	mkdir $@

$(OBJ_DIR_BONUS)/%.o: $(SRC_DIR_BONUS)/%.c  $(SRC_DIR_BONUS)/ft_cub3d.h Makefile | $(OBJ_DIR_BONUS)
	$(CC) $(CFLAGS) -c $< -o $@



$(MINILIBX):
	make -C $(MLX_DIR)

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	make -C $(MLX_DIR) clean
	make -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean $(NAME)

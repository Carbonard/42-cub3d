.PHONY: all clean fclean

MLX_DIR = ./minilibx-linux

LIBFT_DIR = ./libft

CFLAGS = -Wall -Werror -Wextra -g3

LIBS = -lmlx -lXext -lX11 -lm

INCLUDES = -I $(MLX_DIR) -L $(MLX_DIR)

MINILIBX = $(MLX_DIR)/libmlx.a

LIBFT = $(LIBFT_DIR)/libft.a

FILES = ft_cub3d_main.c ft_cub3d_utils.c ft_cub3d_read_file.c\
ft_cub3d_mlx_utils.c\
ft_cub3d_dyn_arrays.c ft_cub3d_math.c\
ft_cub3d_map.c ft_cub3d_minimap_init.c ft_cub3d_minimap.c\
ft_cub3d_render_screen.c\
ft_cub3d_events_key.c\
ft_cub3d_player_mov.c\
ft_cub3d_close.c

NAME = cube3D

# %.o: %.c
# 	$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@

# $(NAME): $(OBJ)
# 	$(CC) $(OBJ) -o $(NAME)

$(NAME): $(FILES) $(MINILIBX) $(LIBFT)
	cc $(CFLAGS) $(INCLUDES) $^ $(LIBS) -o $@

$(MINILIBX):
	make -C $(MLX_DIR)

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	make -C $(MLX_DIR) clean
	make -C $(LIBFT_DIR) clean

fclean: clean
	make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

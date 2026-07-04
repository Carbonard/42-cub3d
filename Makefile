# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/07/03 23:21:50 by rselva-2          #+#    #+#              #
#    Updated: 2026/07/04 01:19:30 by rselva-2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean

MLX_DIR = ./minilibx-linux

LIBFT_DIR = ./libft

CFLAGS = -Wall -Werror -Wextra -g3

LIBS = -lmlx -lXext -lX11 -lm

INCLUDES = -I $(MLX_DIR) -L $(MLX_DIR)

MINILIBX = $(MLX_DIR)/libmlx.a

LIBFT = $(LIBFT_DIR)/libft.a

FILES = main utils read_file\
mlx_utils map_utils\
dyn_arrays math\
map minimap_init minimap\
render_screen\
events_key\
player_mov\
close

SRC = $(FILES:%=src/ft_cub3d_%.c)

NAME = cube3D

# %.o: %.c
# 	$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@

# $(NAME): $(OBJ)
# 	$(CC) $(OBJ) -o $(NAME)

$(NAME): $(SRC) $(MINILIBX) $(LIBFT)
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

re: fclean $(NAME)


# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ainthana <ainthana@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/29 12:00:59 by ainthana          #+#    #+#              #
#    Updated: 2025/12/15 13:10:47 by ainthana         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ==========================================================
#                       CONFIGURATION
# ==========================================================
NAME        = cub3d
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g3
MLX_DIR     = minilibx-linux
MLX_LIB     = $(MLX_DIR)/libmlx.a
MLX_LINUX   = $(MLX_DIR)/libmlx_Linux.a
LFLAGS      = $(MLX_LIB) $(MLX_LINUX) -lX11 -lXext

SRC         = srcs/main.c \
              srcs/parsing/parse_cub.c srcs/parsing/parsing_map.c srcs/parsing/parsing_config.c \
			  srcs/parsing/parsing_file.c srcs/parsing/parsing_utils.c srcs/parsing/check_map.c srcs/parsing/map_floodfill.c \
              srcs/utils/utils.c srcs/utils/utils2.c srcs/utils/split.c srcs/utils/atoi.c srcs/utils/error_utils.c \
              get_next_line/get_next_line.c \
              get_next_line/get_next_line_utils.c

OBJ_DIR     = obj
OBJ         = $(SRC:%.c=$(OBJ_DIR)/%.o)

BONUS_SRC   =
BONUS_OBJ   = $(BONUS_SRC:%.c=$(OBJ_DIR)/%.o)

# ==========================================================
#                       RULES
# ==========================================================
all: $(NAME)

$(NAME): $(OBJ) $(MLX_LIB) $(MLX_LINUX)
	$(CC) $(OBJ) $(LFLAGS) -o $(NAME)

# ==========================================================
#                       	COLORS
# ==========================================================
RESET = \033[0m
BOLD = \033[1m
GREEN = \033[32m
RED = \033[31m
CYAN = \033[36m
BLUE = \033[34m

# ==========================================================
# 						Object files
# ==========================================================
$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# ==========================================================
# 						MiniLibX
# ==========================================================
$(MLX_LIB) $(MLX_LINUX):
	$(MAKE) -C $(MLX_DIR)

# ==========================================================
# 						Cleaning
# ==========================================================
clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)

re: fclean all

# ==========================================================
# 						Bonus
# ==========================================================
bonus: $(BONUS_OBJ)
	$(CC) $(OBJ) $(BONUS_OBJ) $(LFLAGS) -o $(NAME)

.PHONY: all clean fclean re bonus

NAME        = cub3D


SRC_DIR     = src
OBJ_DIR     = obj
INC_DIR     = include
MLX_DIR     = minilibx-linux
GNL_DIR     = get_next_line


CC          = gcc
CFLAGS      = -Wall -Wextra -Werror -g3
INCLUDES    = -I$(INC_DIR) -I$(MLX_DIR) -I$(GNL_DIR)
LIBS        = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm


RESET       = \033[0m
BOLD        = \033[1m
RED         = \033[31m
GREEN       = \033[32m
YELLOW      = \033[33m
BLUE        = \033[34m
MAGENTA     = \033[35m
CYAN        = \033[36m


SRC_PARSING = $(SRC_DIR)/parsing/check_map.c \
              $(SRC_DIR)/parsing/map_floodfill.c \
              $(SRC_DIR)/parsing/parse_cub.c \
              $(SRC_DIR)/parsing/parsing_config.c \
              $(SRC_DIR)/parsing/parsing_file.c \
              $(SRC_DIR)/parsing/parsing_map.c \
              $(SRC_DIR)/parsing/parsing_utils.c


SRC_UTILS   = $(SRC_DIR)/utils/atoi.c \
              $(SRC_DIR)/utils/error_utils.c \
              $(SRC_DIR)/utils/split.c \
              $(SRC_DIR)/utils/utils.c \
              $(SRC_DIR)/utils/utils2.c


SRC_GAME    = $(SRC_DIR)/game/init_mlx.c \
			  $(SRC_DIR)/game/init2_mlx.c \
              $(SRC_DIR)/game/raycasting.c \
			  $(SRC_DIR)/game/raycasting2.c \
              $(SRC_DIR)/game/render.c \
			  $(SRC_DIR)/game/render2.c \
              $(SRC_DIR)/game/movement.c \
			  $(SRC_DIR)/game/movement2.c \
              $(SRC_DIR)/game/hooks.c


SRC_MAIN    = $(SRC_DIR)/main.c


SRCS        = $(SRC_PARSING) $(SRC_UTILS) $(SRC_GAME) $(SRC_MAIN)


OBJS        = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)


GNL_SRCS    = $(GNL_DIR)/get_next_line.c \
              $(GNL_DIR)/get_next_line_utils.c
GNL_OBJS    = $(GNL_SRCS:.c=.o)


all: $(MLX_DIR)/libmlx.a $(NAME)
	@echo "$(GREEN)$(BOLD)✓ Compilation terminée avec succès!$(RESET)"


$(MLX_DIR)/libmlx.a:
	@echo "$(CYAN)⚙ Compilation de la MiniLibX...$(RESET)"
	@make -C $(MLX_DIR) > /dev/null 2>&1
	@echo "$(GREEN)✓ MiniLibX compilée$(RESET)"


$(NAME): $(OBJS) $(GNL_OBJS)
	@echo "$(YELLOW)⚙ Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(GNL_OBJS) $(LIBS) -o $(NAME)
	@echo "$(GREEN)$(BOLD)✓ $(NAME) créé!$(RESET)"


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "$(BLUE)⚙ Compilation de $<...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@


%.o: %.c
	@echo "$(BLUE)⚙ Compilation de $<...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@


clean:
	@echo "$(YELLOW)⚠ Nettoyage des fichiers objets...$(RESET)"
	@rm -rf $(OBJ_DIR)
	@rm -f $(GNL_OBJS)
	@make -C $(MLX_DIR) clean > /dev/null 2>&1
	@echo "$(GREEN)✓ Nettoyage terminé$(RESET)"


fclean: clean
	@echo "$(RED)⚠ Suppression de $(NAME)...$(RESET)"
	@rm -f $(NAME)
	@echo "$(GREEN)✓ Nettoyage complet terminé$(RESET)"


re: fclean all

.PHONY: all clean fclean re test valgrind norm help

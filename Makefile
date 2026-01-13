NAME        = cub3D

# Répertoires
SRC_DIR     = src
OBJ_DIR     = obj
INC_DIR     = include
MLX_DIR     = minilibx-linux
GNL_DIR     = get_next_line

# Compilateur et flags
CC          = gcc
CFLAGS      = -Wall -Wextra -Werror -g3
INCLUDES    = -I$(INC_DIR) -I$(MLX_DIR) -I$(GNL_DIR)
LIBS        = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

# Couleurs
RESET       = \033[0m
BOLD        = \033[1m
RED         = \033[31m
GREEN       = \033[32m
YELLOW      = \033[33m
BLUE        = \033[34m
MAGENTA     = \033[35m
CYAN        = \033[36m

# Fichiers sources - Parsing
SRC_PARSING = $(SRC_DIR)/parsing/check_map.c \
              $(SRC_DIR)/parsing/map_floodfill.c \
              $(SRC_DIR)/parsing/parse_cub.c \
              $(SRC_DIR)/parsing/parsing_config.c \
              $(SRC_DIR)/parsing/parsing_file.c \
              $(SRC_DIR)/parsing/parsing_map.c \
              $(SRC_DIR)/parsing/parsing_utils.c

# Fichiers sources - Utilitaires
SRC_UTILS   = $(SRC_DIR)/utils/atoi.c \
              $(SRC_DIR)/utils/error_utils.c \
              $(SRC_DIR)/utils/split.c \
              $(SRC_DIR)/utils/utils.c \
              $(SRC_DIR)/utils/utils2.c

# Fichiers sources - Jeu
SRC_GAME    = $(SRC_DIR)/game/init_mlx.c \
              $(SRC_DIR)/game/raycasting.c \
              $(SRC_DIR)/game/render.c \
              $(SRC_DIR)/game/movement.c \
              $(SRC_DIR)/game/hooks.c

# Fichiers sources - Main
SRC_MAIN    = $(SRC_DIR)/main.c

# Tous les fichiers sources
SRCS        = $(SRC_PARSING) $(SRC_UTILS) $(SRC_GAME) $(SRC_MAIN)

# Fichiers objets
OBJS        = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Get Next Line
GNL_SRCS    = $(GNL_DIR)/get_next_line.c \
              $(GNL_DIR)/get_next_line_utils.c
GNL_OBJS    = $(GNL_SRCS:.c=.o)

# Règle par défaut
all: $(MLX_DIR)/libmlx.a $(NAME)
	@echo "$(GREEN)$(BOLD)✓ Compilation terminée avec succès!$(RESET)"

# Compilation de la MiniLibX
$(MLX_DIR)/libmlx.a:
	@echo "$(CYAN)⚙ Compilation de la MiniLibX...$(RESET)"
	@make -C $(MLX_DIR) > /dev/null 2>&1
	@echo "$(GREEN)✓ MiniLibX compilée$(RESET)"

# Compilation du programme principal
$(NAME): $(OBJS) $(GNL_OBJS)
	@echo "$(YELLOW)⚙ Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(GNL_OBJS) $(LIBS) -o $(NAME)
	@echo "$(GREEN)$(BOLD)✓ $(NAME) créé!$(RESET)"

# Compilation des fichiers objets
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "$(BLUE)⚙ Compilation de $<...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Compilation de Get Next Line
%.o: %.c
	@echo "$(BLUE)⚙ Compilation de $<...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Nettoyage des objets
clean:
	@echo "$(YELLOW)⚠ Nettoyage des fichiers objets...$(RESET)"
	@rm -rf $(OBJ_DIR)
	@rm -f $(GNL_OBJS)
	@make -C $(MLX_DIR) clean > /dev/null 2>&1
	@echo "$(GREEN)✓ Nettoyage terminé$(RESET)"

# Nettoyage complet
fclean: clean
	@echo "$(RED)⚠ Suppression de $(NAME)...$(RESET)"
	@rm -f $(NAME)
	@echo "$(GREEN)✓ Nettoyage complet terminé$(RESET)"

# Recompilation complète
re: fclean all

# Tests
test: $(NAME)
	@echo "$(MAGENTA)$(BOLD)═══════════════════════════════════════$(RESET)"
	@echo "$(MAGENTA)$(BOLD)         TESTS DU PROJET CUB3D         $(RESET)"
	@echo "$(MAGENTA)$(BOLD)═══════════════════════════════════════$(RESET)"
	@echo ""
	@echo "$(CYAN)Test 1: Carte valide minimale$(RESET)"
	@./$(NAME) maps/valid/minimal.cub 2>&1 | head -1 || echo "$(GREEN)✓ Passe$(RESET)"
	@echo ""
	@echo "$(CYAN)Test 2: Carte invalide (pas d'extension)$(RESET)"
	@./$(NAME) maps/invalid/no_extension 2>&1 | grep -q "Error" && echo "$(GREEN)✓ Passe$(RESET)" || echo "$(RED)✗ Échec$(RESET)"
	@echo ""
	@echo "$(CYAN)Test 3: Carte invalide (ouverte)$(RESET)"
	@./$(NAME) maps/invalid/open_map.cub 2>&1 | grep -q "Error" && echo "$(GREEN)✓ Passe$(RESET)" || echo "$(RED)✗ Échec$(RESET)"
	@echo ""
	@echo "$(MAGENTA)$(BOLD)═══════════════════════════════════════$(RESET)"

# Test avec Valgrind
valgrind: $(NAME)
	@echo "$(YELLOW)⚙ Test Valgrind en cours...$(RESET)"
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
		./$(NAME) maps/valid/minimal.cub

# Norminette
norm:
	@echo "$(CYAN)⚙ Vérification de la norme...$(RESET)"
	@norminette $(SRC_DIR) $(INC_DIR) | grep -v "OK!" || echo "$(GREEN)✓ Norme respectée!$(RESET)"

# Affichage de l'aide
help:
	@echo "$(BOLD)$(BLUE)CUB3D - Makefile Help$(RESET)"
	@echo ""
	@echo "$(YELLOW)Commandes disponibles:$(RESET)"
	@echo "  $(GREEN)make$(RESET)          - Compile le projet"
	@echo "  $(GREEN)make clean$(RESET)    - Supprime les fichiers objets"
	@echo "  $(GREEN)make fclean$(RESET)   - Supprime tout (objets + exécutable)"
	@echo "  $(GREEN)make re$(RESET)       - Recompile tout depuis le début"
	@echo "  $(GREEN)make test$(RESET)     - Lance les tests automatiques"
	@echo "  $(GREEN)make valgrind$(RESET) - Test avec Valgrind"
	@echo "  $(GREEN)make norm$(RESET)     - Vérifie la norme"
	@echo "  $(GREEN)make help$(RESET)     - Affiche cette aide"
	@echo ""

.PHONY: all clean fclean re test valgrind norm help

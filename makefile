# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/04 20:34:49 by frromero          #+#    #+#              #
#    Updated: 2025/06/07 17:05:49 by frromero         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ====================================================== #
#                 PROJECT CONFIGURATION                  #
# ====================================================== #

NAME        := cub3D
CC          := cc
RM          := rm -f
MKDIR       := mkdir -p

# ====================================================== #
#                  DIRECTORY STRUCTURE                   #
# ====================================================== #

SRC_DIR     := src
OBJ_DIR     := obj
INC_DIR     := include
LIBFT_DIR   := libft
MLX_DIR     := minilibx-linux

# ====================================================== #
#                  COMPILATION FLAGS                     #
# ====================================================== #

DEBUG_FLAGS := -g3
OPTIM_FLAGS := -O3
WARN_FLAGS  := -Wall -Wextra -Werror
INC_FLAGS   := -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)
CFLAGS      := $(OPTIM_FLAGS) $(DEBUG_FLAGS) $(WARN_FLAGS) $(INC_FLAGS)

# ====================================================== #
#               PLATFORM-SPECIFIC CONFIG                 #
# ====================================================== #

UNAME := $(shell uname)

# macOS (Darwin)
ifeq ($(UNAME), Darwin)
    MLX_LIB     := libmlx.dylib
    FT_LIB      := libft.a
    LIBS        := -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx
    LIBS        += -framework OpenGL -framework AppKit -lm
# Linux
else
    MLX_LIB     := libmlx.a
    FT_LIB      := libft.a
    LIBS        := -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lm -lXext -lX11
endif

# ====================================================== #
#                  SOURCE FILES LIST                     #
# ====================================================== #

SRCS := \
    $(SRC_DIR)/main.c \
    $(SRC_DIR)/initialization/init.c \
    $(SRC_DIR)/errors/error.c \
    $(SRC_DIR)/parse/parse.c \
    $(SRC_DIR)/parse/parse_elements.c \
    $(SRC_DIR)/parse/parse_store_map.c \
    $(SRC_DIR)/parse/parse_colors.c \
    $(SRC_DIR)/parse/parse_map.c \
    $(SRC_DIR)/parse/parse_items_map.c \
    $(SRC_DIR)/parse/parse_validate_map.c \
    $(SRC_DIR)/game/window_init.c \
    $(SRC_DIR)/game/load_textures.c \
    $(SRC_DIR)/game/aux_load_textures.c \
    $(SRC_DIR)/player/game_loop.c \
    $(SRC_DIR)/player/init_orientation.c \
    $(SRC_DIR)/player/init_player.c \
    $(SRC_DIR)/player/key_hooks.c \
    $(SRC_DIR)/player/movement_utils.c \
    $(SRC_DIR)/player/movement_utils2.c \
    $(SRC_DIR)/player/rotation.c \
    $(SRC_DIR)/render/render.c \
    $(SRC_DIR)/render/render_walls.c \
    $(SRC_DIR)/render/compute_wall.c \
    $(SRC_DIR)/render/perform_dda.c \
    $(SRC_DIR)/render/ray_init.c \
    $(SRC_DIR)/render/raycasting.c \
    $(SRC_DIR)/utils/utils.c \
    $(SRC_DIR)/utils/utils_2.c \
    $(SRC_DIR)/exit/free.c

OBJS := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# ====================================================== #
#                     BUILD RULES                        #
# ====================================================== #

all: $(NAME)

$(NAME): $(MLX_DIR)/$(MLX_LIB) $(LIBFT_DIR)/$(FT_LIB) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)
	@echo "\033[32m✔ $(NAME) compiled successfully\033[0m"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(MKDIR) $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT_DIR)/$(FT_LIB):
	@$(MAKE) -C $(LIBFT_DIR) --silent
	@echo "\033[32m✔ libft compiled successfully\033[0m"

$(MLX_DIR)/$(MLX_LIB):
	@$(MAKE) -C $(MLX_DIR) --silent
	@echo "\033[32m✔ MinilibX compiled successfully\033[0m"



# ====================================================== #
#                        VALGRIND                        #
# ====================================================== #

valgrind_e: $(NAME)
	@echo "\033[33m✔ Running with Valgrind...\033[0m"
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./$(NAME) maps/nok/1e.cub


# ====================================================== #
#             VALGRIND & SUPPRESION FILE                 #
# ====================================================== #

VALGRIND_LOG = valgrind.log
SUPPRESSION_FILE = mlx.supp

valgrind: $(NAME) $(SUPPRESSION_FILE)
	@echo "\033[33m✔ Running with Valgrind...\033[0m"
	@valgrind --leak-check=full \
		--suppressions=$(SUPPRESSION_FILE) \
		--log-file=$(VALGRIND_LOG) \
		./$(NAME) maps/ok/10.cub


$(SUPPRESSION_FILE):
	@echo "Creando archivo de supresiones $(SUPPRESSION_FILE)..."
	@echo '{' > $(SUPPRESSION_FILE)
	@echo '   mlx_writev_suppression' >> $(SUPPRESSION_FILE)
	@echo '   Memcheck:Param' >> $(SUPPRESSION_FILE)
	@echo '   writev(vector[0])' >> $(SUPPRESSION_FILE)
	@echo '   fun:writev' >> $(SUPPRESSION_FILE)
	@echo '   obj:*libxcb.so*' >> $(SUPPRESSION_FILE)
	@echo '   obj:*libX11.so*' >> $(SUPPRESSION_FILE)
	@echo '}' >> $(SUPPRESSION_FILE)



# ====================================================== #
#                     UTILITY RULES                      #
# ====================================================== #

clean:
	@$(RM) -r $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean --silent
	@rm -f $(VALGRIND_LOG) $(SUPPRESSION_FILE)
	@echo "\033[33m✔ Object files removed\033[0m"

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(MLX_DIR) clean --silent
	@$(MAKE) -C $(LIBFT_DIR) fclean --silent
	@echo "\033[33m✔ Executable and libraries removed\033[0m"

re: fclean all

.PHONY: all clean fclean re

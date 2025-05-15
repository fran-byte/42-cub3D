# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/04 20:34:49 by frromero          #+#    #+#              #
#    Updated: 2025/05/15 16:13:44 by frromero         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ====================================================== #
#                 PROJECT CONFIGURATION                  #
# ====================================================== #

# Program name
NAME		:= cub3d

# Compiler configuration
CC			:= cc          # C compiler
RM			:= rm -f       # Force remove command
MKDIR		:= mkdir -p    # Create directory command

# ====================================================== #
#                  DIRECTORY STRUCTURE                   #
# ====================================================== #

# Source files directory
SRC_DIR		:= src

# Object files directory (will be created)
OBJ_DIR		:= obj

# Header files directory
INC_DIR		:= include

# External libraries directories
LIBFT_DIR	:= libft       # Libft library
MLX_DIR =	minilibx-linux

# ====================================================== #
#                  COMPILATION FLAGS                     #
# ====================================================== #

# Debug flags
DEBUG_FLAGS	:= -g3			# Generate debug information (level 3)

# Optimization flags
OPTIM_FLAGS	:= -O3			# Maximum optimization level

# Warning flags
#WARN_FLAGS	:= -Wall		# Enable all warnings
#WARN_FLAGS	+= -Wextra		# Enable extra warnings
#WARN_FLAGS	+= -Werror		# Treat warnings as errors

# Include paths for header files
INC_FLAGS	:= -I$(INC_DIR)			# Project headers
INC_FLAGS	+= -I$(LIBFT_DIR)		# Libft headers
INC_FLAGS	+= -I$(MLX_DIR)			# MinilibX headers

# Combine all flags
CFLAGS		:= $(OPTIM_FLAGS) $(DEBUG_FLAGS) $(WARN_FLAGS) $(INC_FLAGS)

# ====================================================== #
#               PLATFORM-SPECIFIC CONFIG                 #
# ====================================================== #

# Detect operating system
UNAME := $(shell uname)

# macOS configuration
ifeq ($(UNAME), Darwin)
	LIBS    := -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx
	LIBS    += -framework OpenGL -framework AppKit -lm
	MLX_LIB := libmlx.dylib
# Linux configuration
else
	LIBS    := -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx
	LIBS    += -lX11 -lXext -lm
	MLX_LIB := libmlx.a
endif

# ====================================================== #
#                  SOURCE FILES LIST                     #
# ====================================================== #

# List all source files with their relative paths
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
	$(SRC_DIR)/debugging/print_grid.c \
	$(SRC_DIR)/debugging/testing.c \
	$(SRC_DIR)/debugging/debug_render.c \
	$(SRC_DIR)/game/window_init.c \
	$(SRC_DIR)/game/load_textures.c \
	$(SRC_DIR)/game/aux_load_textures.c \
	$(SRC_DIR)/player/game_loop.c \
	$(SRC_DIR)/player/init_orientation.c \
	$(SRC_DIR)/player/init_player.c \
	$(SRC_DIR)/player/key_hooks.c \
	$(SRC_DIR)/player/movement_utils.c \
	$(SRC_DIR)/player/rotation.c \
	$(SRC_DIR)/render/render.c \
	$(SRC_DIR)/render/render_walls.c \
	$(SRC_DIR)/utils/utils.c \
	$(SRC_DIR)/utils/utils_2.c \
	$(SRC_DIR)/exit/free.c


# Generate object files list by replacing .c with .o and src with obj
OBJS := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# ====================================================== #
#                     BUILD RULES                        #
# ====================================================== #

# Default target - builds everything
all: $(NAME)

# Main build rule - links everything together
$(NAME): $(MLX_LIB) $(LIBFT_DIR)/libft.a $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)
	@echo "\033[32m✔ $(NAME)    → compiled successfully\033[0m"

# Rule to compile each source file into object file
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(MKDIR) $(dir $@)					# Create directory structure
	@$(CC) $(CFLAGS) -c $< -o $@ -s		# Compile source to object


# Rule to build libft library
$(LIBFT_DIR)/libft.a:
	@$(MAKE) -C $(LIBFT_DIR) --silent			# Build libft silently
	@echo "\033[32m✔ libft    → compiled successfully\033[0m"		# Print success message

# Rule to build MinilibX library
$(MLX_LIB):
	@$(MAKE) -C $(MLX_DIR) --silent				# Build MinilibX silently
	@cp $(MLX_DIR)/$(MLX_LIB) .					# Copy library to root
	@echo "\033[32m✔ MinilibX → compiled successfully\033[0m"	# Print success message


# Rule to run the project with Valgrind (ko map)
valgrind_e: $(NAME)
	@echo "\033[33m✔ Running with Valgrind...\033[0m"
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./$(NAME) maps/nok/1e.cub

# Rule to run the project with Valgrind & Suppresion file (minilibx/x11 errors) (ok map)
VALGRIND_LOG = valgrind.log
SUPPRESSION_FILE = mlx.supp

valgrind: $(SUPPRESSION_FILE)
	@valgrind --leak-check=full \
		--suppressions=$(SUPPRESSION_FILE) \
		--log-file=$(VALGRIND_LOG) \
		./cub3d maps/ok/1.cub

$(SUPPRESSION_FILE):
	@echo "Creando archivo de supresiones $(SUPPRESSION_FILE)..."
	@echo '{' > $(SUPPRESSION_FILE)
	@echo '   mlx_writev_suppression' >> $(SUPPRESSION_FILE)
	@echo '   Memcheck:Param' >> $(SUPPRESSION_FILE)
	@echo '   writev(vector[0])' >> $(SUPPRESSION_FILE)
	@echo '   fun:writev' >> $(SUPPRESSION_FILE)
	@echo '   obj:/usr/lib/x86_64-linux-gnu/libxcb.so.*' >> $(SUPPRESSION_FILE)
	@echo '   obj:/usr/lib/x86_64-linux-gnu/libX11.so.*' >> $(SUPPRESSION_FILE)
	@echo '}' >> $(SUPPRESSION_FILE)


# Clean rule - removes object files
clean:
	@$(RM) -r $(OBJ_DIR)						# Remove objects directory
	@$(MAKE) -C $(LIBFT_DIR) clean --silent		# Clean libft
	@rm -f $(VALGRIND_LOG) $(SUPPRESSION_FILE)
	@echo "\033[33m✔ Object files removed\033[0m"

# Full clean rule - removes everything
fclean: clean
	@$(RM) $(NAME) $(MLX_LIB)					# Remove executable and MLX
	@$(MAKE) -C $(LIBFT_DIR) fclean --silent	# Full clean libft
	@echo "\033[33m✔ Executable and libraries removed\033[0m"

# Rebuild rule - clean and build everything
re: fclean all

# Phony targets (don't represent actual files)
.PHONY: all clean fclean re

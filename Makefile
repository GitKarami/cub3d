# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: kchahmi <kchahmi@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2024/12/22 13:49:31 by kchahmi       #+#    #+#                  #
#    Updated: 2024/12/23 22:09:02 by krim          ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

CC = gcc
CFLAGS = -Wall -Wextra -Werror
MLX_DIR = lib/minilibx
MLXFLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

SRC_DIR = src
SRC =	$(SRC_DIR)/main.c \
		$(SRC_DIR)/init.c \
		$(SRC_DIR)/parser.c \
		$(SRC_DIR)/render.c \
		$(SRC_DIR)/keypress.c \
		$(SRC_DIR)/player.c \
		$(SRC_DIR)/textures.c \
		$(SRC_DIR)/clean.c

OBJ_DIR = obj
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

LIBFT_DIR = lib/libft
LIBFT = $(LIBFT_DIR)/libft.a

# Define colors
GREEN = \033[32m
RED = \033[31m
PURPLE = \033[35m
YELLOW = \033[33m
RESET = \033[0m

all: $(NAME)

$(NAME): $(LIBFT) $(MLX_DIR)/libmlx.a $(OBJ)
	@echo -e "$(PURPLE)"
	@echo "  ____ _     ___ ____  _     _____ ____  "
	@echo " / ___| |   |_ _|  _ \| |   | ____|  _ \ "
	@echo "| |   | |__| | || |_) | |   |  _| | |_) |"
	@echo "| |___|  __  | ||  __/| |___| |___|  _ < "
	@echo " \____|_|  |_|\____/|_____|_____|_| \_\\"
	@echo -e "$(RESET)"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -L$(LIBFT_DIR) -lft $(MLXFLAGS) > /dev/null && \
	echo -e "$(GREEN)Constructing the arena$(RESET)" || (\
	echo -e "$(RED)" ;\
	echo "  ___  _  _   _ _____ ___  ___  ";\
	echo " / _ \| || | | | ____/ _ \| _ \ ";\
	echo "| | | | || |_| |  _|| | | |   / ";\
	echo "| |_| |__   _| |___| |_| | |\ \ ";\
	echo " \___/   |_| |_____|___/|_| \_\\ ";\
	echo -e "$(RESET)";\
	)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c includes/cub3d.h
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I./includes -c $< -o $@

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(MLX_DIR)/libmlx.a:
	@make -C $(MLX_DIR)

%.o: %.c includes/cub3d.h
	@$(CC) $(CFLAGS) -I./includes -c $< -o $@

clean:
	@rm -f $(OBJ)
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean
	@echo -e "$(YELLOW)Cleaned object files and libft.$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@make -C $(MLX_DIR) clean
	@echo -e "$(RED)Cleaned all binaries.$(RESET)"

re: fclean all

.PHONY: all clean fclean re
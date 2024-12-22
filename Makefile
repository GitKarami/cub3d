# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: kchahmi <kchahmi@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2024/12/22 13:49:31 by kchahmi       #+#    #+#                  #
#    Updated: 2024/12/22 15:18:40 by kchahmi       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

CC = gcc
CFLAGS = -Wall -Wextra -Werror
MLXFLAGS = -lmlx -lXext -lX11 -lm

SRC = src/main.c \
      src/init.c \
      src/parser.c \
      src/render.c \
      src/keypress.c \
	  src/clean.c

OBJ_DIR = obj
OBJ = $(SRC:src/%.c=$(OBJ_DIR)/%.o)

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

# Define colors
GREEN = \033[32m
RED = \033[31m
PURPLE = \033[35m
YELLOW = \033[33m
RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
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

$(LIBFT):
	@make -C $(LIBFT_DIR)

%.o: %.c includes/cub3d.h
	@$(CC) $(CFLAGS) -I./includes -c $< -o $@

clean:
	@rm -f $(OBJ)
	@make -C $(LIBFT_DIR) clean
	@echo -e "$(YELLOW)Cleaned object files and libft.$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@echo -e "$(RED)Cleaned all binaries.$(RESET)"

re: fclean all

.PHONY: all clean fclean re
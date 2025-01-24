# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/23 12:11:00 by vbengea           #+#    #+#              #
#    Updated: 2025/01/24 19:11:23 by vbengea          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Wextra -Werror -Ilibft

LIBFT_DIR = ../libft

LIBFT_MAKEFILE = $(LIBFT_DIR)/Makefile

LIBFT_LIB = $(LIBFT_DIR)/libft.a

# SRC_DIR = src

SRC_FILES = tokenize.c \
			add_token.c \
			create_token.c \
			create_word_token.c

OUTPUT = parser

DEBUG_FLAGS = -g -fsanitize=address

all: $(OUTPUT)

$(OUTPUT): $(LIBFT_LIB) $(SRC_FILES)
	$(CC) $(CFLAGS) -o $(OUTPUT) $(SRC_FILES) $(LIBFT_LIB)

sanitize: $(LIBFT_LIB) $(SRC_FILES)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -o $(OUTPUT) $(SRC_FILES) $(LIBFT_LIB)

$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(LIBFT_LIB) $(OUTPUT)

re: fclean clear all

clear:
	clear

.PHONY: re all clean fclean clear sanitize%
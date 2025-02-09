# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/23 12:11:00 by vbengea           #+#    #+#              #
#    Updated: 2025/02/08 20:08:03 by vbengea          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Wextra -Werror -Ilibft -lreadline -g
LDFLAGS = -lreadline
VALGRIND_VALE	:=	/home/vbcvali/Documents/minishell_t/tmp/suppressions/new_suppression.supp
VFLAGS	:=	--leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=$(VALGRIND_VALE)


LIBFT_DIR = ../libft

LIBFT_MAKEFILE = $(LIBFT_DIR)/Makefile

LIBFT_LIB = $(LIBFT_DIR)/libft.a

# SRC_DIR = src

SRC_FILES = ast_build/*.c \
			tokenizer/*.c \
			main.c

OUTPUT = parser

DEBUG_FLAGS = -g -fsanitize=address

all: $(OUTPUT)

$(OUTPUT): $(LIBFT_LIB) $(SRC_FILES)
	$(CC) $(CFLAGS) -o $(OUTPUT) $(SRC_FILES) $(LIBFT_LIB) $(LDFLAGS)

sanitize: $(LIBFT_LIB) $(SRC_FILES)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -o $(OUTPUT) $(SRC_FILES) $(LIBFT_LIB) $(LDFLAGS)

$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(LIBFT_LIB) $(OUTPUT)
	rm tokenizer/*.o

re: fclean clear all

valgrind: 
	valgrind $(VFLAGS) ./parser

clear:
	clear

.PHONY: re all clean fclean clear sanitize%
NAME			:=	minishell

CC				:= 	cc
CFLAGS			:= 	-Wall -Wextra -Werror -I/opt/homebrew/opt/readline/include -g
SFLAGS			:= 	-g3 -fsanitize=address

VALGRIND_PATH	:=	./tmp/suppressions/valgrind.supp
VALGRIND_VALE	:=	./tmp/suppressions/new_suppression.supp
VALGRIND_JUAF	:=	./tmp/suppressions/mac.supp
VFLAGS			:=	--leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=$(VALGRIND_VALE)
LDFLAGS 		:=	-lreadline -L/opt/homebrew/opt/readline/lib

LIBFT_DIR		:= 	./libft
LIBFT			:= 	$(LIBFT_DIR)/libft.a
EXEC_DIR		:=	executor
PARSER_DIR		:=  parser
BUILTINS_DIR	:=  builtins
SIGNALS_DIR		:=  signals
WILDCARD_DIR	:=  wildcard
HISTORY_DIR		:=  history
INCLUDE			:= 	./include/headers.h

SRC				:= 	main.c\
					$(EXEC_DIR)/utils_1.c \
					$(EXEC_DIR)/utils_2.c \
					$(EXEC_DIR)/utils_redis.c \
					$(EXEC_DIR)/execute.c \
					$(EXEC_DIR)/selector.c \
					$(EXEC_DIR)/pipex.c \
					$(EXEC_DIR)/redirect.c \
					$(EXEC_DIR)/parser.c \
					$(EXEC_DIR)/parser_redis.c \
					$(EXEC_DIR)/parser_utils.c \
					$(SIGNALS_DIR)/signals.c \
					$(PARSER_DIR)/tokenizer/tokenize.c \
					$(PARSER_DIR)/tokenizer/add_token.c \
					$(PARSER_DIR)/tokenizer/create_token.c \
					$(PARSER_DIR)/tokenizer/create_word_token.c \
					$(PARSER_DIR)/tokenizer/create_quoted_token.c \
					$(PARSER_DIR)/tokenizer/handle_parens.c \
					$(PARSER_DIR)/tokenizer/handle_double_operators.c \
					$(PARSER_DIR)/tokenizer/handle_single_operator.c \
					$(PARSER_DIR)/tokenizer/count_consecutive_operators.c \
					$(PARSER_DIR)/tokenizer/create_fd_redirection_token.c \
					$(PARSER_DIR)/tokenizer/create_invalid_operator_token.c \
					$(PARSER_DIR)/tokenizer/skip_whitespace.c \
					$(PARSER_DIR)/tokenizer/is_operator.c \
					$(PARSER_DIR)/tokenizer/is_quote.c \
					$(PARSER_DIR)/tokenizer/dispatch_operator.c \
					$(PARSER_DIR)/tokenizer/handle_operator.c \
					$(PARSER_DIR)/tokenizer/free_token.c \
					$(PARSER_DIR)/tokenizer/check_syntax.c \
					$(PARSER_DIR)/ast_build/*.c \
					$(PARSER_DIR)/environment/handle_no_env.c \
					$(BUILTINS_DIR)/cd.c \
					$(BUILTINS_DIR)/echo.c \
					$(BUILTINS_DIR)/env.c \
					$(BUILTINS_DIR)/exit.c \
					$(BUILTINS_DIR)/export.c \
					$(BUILTINS_DIR)/pwd.c \
					$(BUILTINS_DIR)/unset.c \
					$(BUILTINS_DIR)/env_set.c \
					$(BUILTINS_DIR)/expand.c \
					$(WILDCARD_DIR)/ft_wildcard.c \
					$(HISTORY_DIR)/history.c

OBJ 			:= 	$(patsubst $(EXEC_DIR)/%.c, $(EXEC_DIR)/%.o, $(SRC)) \
					$(patsubst $(SIGNALS_DIR)/%.c, $(SIGNALS_DIR)/%.o, $(SRC)) \
					$(patsubst $(PARSER_DIR)/*/%.c, $(PARSER_DIR)/*/%.o, $(SRC)) \
					$(patsubst $(BUILTINS_DIR)/%.c, $(BUILTINS_DIR)/%.o, $(SRC)) \
					$(patsubst $(WILDCARD_DIR)/%.c, $(WILDCARD_DIR)/%.o, $(SRC))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ) $(INCLUDE)
	$(CC) $(CFLAGS) $(SRC) $(LIBFT) -o $(NAME) $(LDFLAGS)

clean:
	make -C $(LIBFT_DIR) clean
	rm -f $(EXEC_DIR)/*.o
	rm -f $(PARSER_DIR)/*/*.o
	rm -f $(BUILTINS_DIR)/*.o
	rm -f $(SIGNALS_DIR)/*.o
	rm -f $(WILDCARD_DIR)/*.o
	rm -rf *.dSYM
	rm -f t0 t1 t2 t3 t4 t5 file1 file2 file3 file4 file5 tmp/__*

fclean: clean
	rm -rf one
	make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)
	rm -f a.out
	rm -f $(NAME).dSYM

re: fclean all

$(LIBFT):
	make -C $(LIBFT_DIR) all

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

norm: fclean
	#norminette $(SRC) $(INCLUDE)

git: norm
	rm -f t1
	rm -f t2
	rm -f infile
	rm -f outfile
	rm -f __tmp__
	rm -rf one
	git add -A
	git commit -am "Norm utils_*.c"
	git config pull.rebase false
	git push

runner: re
	# mkdir one
	# mkdir one/two
	# mkdir one/two/three
	./$(NAME)
	make -C . fclean

runneri: re
	env -i ./$(NAME)
	make -C . fclean

valgrind: re
	valgrind $(VFLAGS) ./$(NAME)

sanitizer: $(LIBFT) $(OBJ) $(INCLUDE)
	$(CC) $(SFLAGS) $(CFLAGS) $(SRC) $(LIBFT) -o $(NAME) $(LDFLAGS)
	./$(NAME)
	make -C . fclean

.PHONY: all clean fclean re norm git runner valgrind sanitizer

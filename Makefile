NAME			:=	minishell

CC				:= 	cc
CFLAGS			:= 	-Wall -Wextra -Werror
SFLAGS			:= 	-g3 -fsanitize=address
LDFLAGS 		:=	-lreadline

LIBFT_DIR		:= 	./libft
LIBFT			:= 	$(LIBFT_DIR)/libft.a
EXEC_DIR		:=	executor
PARSER_DIR		:=  parser
BUILTINS_DIR	:=  builtins
INCLUDE			:= 	./include/headers.h

SRC				:= 	$(EXEC_DIR)/utils.c \
					$(EXEC_DIR)/execute.c \
					$(EXEC_DIR)/selector.c \
					$(EXEC_DIR)/pipex.c \
					$(PARSER_DIR)/tokenize.c \
					$(PARSER_DIR)/add_token.c \
					$(PARSER_DIR)/create_token.c \
					$(PARSER_DIR)/create_word_token.c \
					$(PARSER_DIR)/create_quoted_token.c \
					$(PARSER_DIR)/handle_parens.c \
					$(PARSER_DIR)/handle_double_operators.c \
					$(PARSER_DIR)/handle_single_operator.c \
					$(PARSER_DIR)/count_consecutive_operators.c \
					$(PARSER_DIR)/ast_build/build_ast.c \
					$(PARSER_DIR)/ast_build/create_ast_node.c \
					$(PARSER_DIR)/ast_build/print_ast.c \
					$(PARSER_DIR)/ast_build/free_ast.c \
					$(PARSER_DIR)/ast_build/handle_parentheses.c \
					$(PARSER_DIR)/ast_build/build_operator_node.c \
					$(PARSER_DIR)/ast_build/build_command_node.c \
					$(PARSER_DIR)/ast_build/create_redirect_node.c \
					$(PARSER_DIR)/ast_build/find_matching_paren.c \
					$(PARSER_DIR)/ast_build/find_split_point.c \
					$(BUILTINS_DIR)/cd.c \
					$(BUILTINS_DIR)/echo.c \
					$(BUILTINS_DIR)/env.c \
					$(BUILTINS_DIR)/exit.c \
					$(BUILTINS_DIR)/export.c \
					$(BUILTINS_DIR)/pwd.c \
					$(BUILTINS_DIR)/unset.c \
					main.c

OBJ 			:= 	$(patsubst $(EXEC_DIR)/%.c, $(EXEC_DIR)/%.o, $(SRC)) \
					$(patsubst $(PARSER_DIR)/ast_build/%.c, $(PARSER_DIR)/ast_build/%.o, $(SRC)) \
					$(patsubst $(PARSER_DIR)/%.c, $(PARSER_DIR)/%.o, $(SRC)) \
					$(patsubst $(BUILTINS_DIR)/%.c, $(BUILTINS_DIR)/%.o, $(SRC))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ) $(INCLUDE)
	$(CC) $(CFLAGS) $(SRC) $(LIBFT) -o $(NAME) $(LDFLAGS)

clean:
	make -C $(LIBFT_DIR) clean
	rm -f $(EXEC_DIR)/*.o
	rm -f $(PARSER_DIR)/*.o
	rm -f $(PARSER_DIR)/ast_build/*.o
	rm -f $(BUILTINS_DIR)/*.o
	rm -rf *.dSYM
	rm -f z

fclean: clean
	make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)
	rm -f a.out

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
	git add -A
	git commit -am "$(shell date)"
	git push

runner: all
	./minishell
	make -C . fclean

valgrind: fclean $(LIBFT) $(OBJB) $(INCLUDE)
	$(CC) $(CFLAGS) $(SRC) $(LIBFT) -o minishell
	valgrind -s --tool=memcheck --leak-check=yes ./minishell
	make -C . fclean

sanitizer: fclean $(LIBFT) $(OBJB) $(INCLUDE)
	$(CC) $(CFLAGS) $(SRC) $(LIBFT) $(SFLAGS) -o minishell
	./minishell
	make -C . fclean

.PHONY: all clean fclean re norm git runner valgrind sanitizer

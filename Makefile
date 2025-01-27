NAME		:=	minishell

LIBFT_DIR	:= 	./libft
LIBFT		:= 	$(LIBFT_DIR)/libft.a

CC			:= 	cc
CFLAGS		:= 	-Wall -Wextra -Werror
SFLAGS		:= 	-g3 -fsanitize=address
LFLAGS		:= 	$(LIBFT)
LDFLAGS 	:=	-lreadline
EXEC_DIR	:=	executor
PARSER_DIR	:=  parser
INCLUDE		:= 	./include/headers.h
SRC			:= 	$(EXEC_DIR)/process.c $(EXEC_DIR)/utils.c $(EXEC_DIR)/execute.c \
				$(EXEC_DIR)/binary.c $(EXEC_DIR)/redirection.c $(EXEC_DIR)/bmock.c $(EXEC_DIR)/mock.c \
				$(PARSER_DIR)/tokenize.c \
				$(PARSER_DIR)/add_token.c \
				$(PARSER_DIR)/create_token.c \
				$(PARSER_DIR)/create_word_token.c \
				$(PARSER_DIR)/create_quoted_token.c \
				$(PARSER_DIR)/handle_parens.c \
				$(PARSER_DIR)/handle_double_operators.c \
				$(PARSER_DIR)/handle_single_operator.c \
				$(PARSER_DIR)/count_consecutive_operators.c \
				$(PARSER_DIR)/ast_build/ast_build.c \
				$(PARSER_DIR)/ast_build/build_ast_with_inner.c \
				$(PARSER_DIR)/ast_build/create_ast_node.c \
				main.c

SRCB		:= 	

OBJ 		:= 	$(patsubst $(EXEC_DIR)/%.c, $(EXEC_DIR)/%.o, $(SRC)) \
				$(patsubst $(PARSER_DIR)/ast_build/%.c, $(PARSER_DIR)/ast_build/%.o, $(SRC)) \
				$(patsubst $(PARSER_DIR)/%.c, $(PARSER_DIR)/%.o, $(SRC))
OBJB 		:= 	$(SRCB:.c=.o)

ARGS		:=	""

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ) $(INCLUDE)
	$(CC) $(CFLAGS) $(SRC) $(LFLAGS) -o $(NAME) $(LDFLAGS)

clean:
	make -C $(LIBFT_DIR) clean
	rm -f $(EXEC_DIR)/*.o
	rm -f $(PARSER_DIR)/*.o
	rm -f $(PARSER_DIR)/ast_build/*.o
	rm -rf *.dSYM
	rm -f z

fclean: clean
	make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)
	rm -f a.out
	rm -f bonus

re: fclean all

bonus: $(LIBFT) $(OBJB) $(INCLUDE)
	$(CC) $(CFLAGS) $(SRCB) $(LFLAGS) -o $(NAME)
	touch bonus

$(LIBFT):
	make -C $(LIBFT_DIR) all

%.o: %.c
	rm -f bonus
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
	./minishell $(ARGS)
	make -C . fclean

valgrind: fclean $(LIBFT) $(OBJB) $(INCLUDE)
	$(CC) $(CFLAGS) $(SRC) $(LFLAGS) -o minishell
	valgrind -s --tool=memcheck --leak-check=yes ./minishell $(ARGS1)
	make -C . fclean

sanitizer: fclean $(LIBFT) $(OBJB) $(INCLUDE)
	$(CC) $(CFLAGS) $(SRC) $(LFLAGS) $(SFLAGS) -o minishell
	./minishell $(ARGS1)
	make -C . fclean

.PHONY: all clean fclean re norm git runner valgrind sanitizer

NAME			:=	minishell

RED				:=	\033[1;31m
GREEN			:=	\033[1;32m
NC				:=	\033[0m

CC				:= 	cc
CFLAGS			:= 	-Wall -Wextra -Werror -Iinclude
SFLAGS			:= 	-g3 -fsanitize=address

VALGRIND_PATH	:=	./tmp/suppressions/valgrind.supp
VALGRIND_VALE	:=	./tmp/suppressions/new_suppression.supp
VALGRIND_JUAF	:=	./tmp/suppressions/mac.supp
VFLAGS			:=	--leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --suppressions=$(VALGRIND_VALE) # --trace-children=yes
LDFLAGS 		:=	-lreadline

SRCS_DIR		:=	srcs
LIBFT_DIR		:= 	include/libft
LIBFT			:= 	$(LIBFT_DIR)/libft.a
EXEC_DIR		:=	$(SRCS_DIR)/executor
PARSER_DIR		:=  $(SRCS_DIR)/parser
BUILTINS_DIR	:=  $(SRCS_DIR)/builtins
SIGNALS_DIR		:=  $(SRCS_DIR)/terminal
WILDCARD_DIR	:=  $(SRCS_DIR)/wildcard
HISTORY_DIR		:=  $(SRCS_DIR)/history
INCLUDE_DIR		:= 	include
OBJ_DIR			:=  obj

SRC				:= 	$(SRCS_DIR)/main.c \
					$(EXEC_DIR)/utils_1.c \
					$(EXEC_DIR)/utils_2.c \
					$(EXEC_DIR)/utils_3.c \
					$(EXEC_DIR)/redirect_2.c \
					$(EXEC_DIR)/redirect_3.c \
					$(EXEC_DIR)/redirect_4.c \
					$(EXEC_DIR)/redirect_in.c \
					$(EXEC_DIR)/redirect_out.c \
					$(EXEC_DIR)/execute.c \
					$(EXEC_DIR)/selector_1.c \
					$(EXEC_DIR)/selector_2.c \
					$(EXEC_DIR)/selector_3.c \
					$(EXEC_DIR)/selector_4.c \
					$(EXEC_DIR)/selector_5.c \
					$(EXEC_DIR)/pipex.c \
					$(EXEC_DIR)/pipex_redirect.c \
					$(SIGNALS_DIR)/signals.c \
					$(SIGNALS_DIR)/terminal.c \
					$(SIGNALS_DIR)/tty.c \
					$(SIGNALS_DIR)/utils.c \
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
					$(PARSER_DIR)/tokenizer/check_syntax_utils.c \
					$(PARSER_DIR)/tokenizer/create_env_var_token.c \
					$(PARSER_DIR)/tokenizer/is_env_var_declaration.c \
					$(PARSER_DIR)/tokenizer/process_operator.c \
					$(PARSER_DIR)/tokenizer/process_token.c \
					$(PARSER_DIR)/tokenizer/tokenize_input.c \
					$(PARSER_DIR)/ast_build/add_redirection.c \
					$(PARSER_DIR)/ast_build/build_operator_node.c \
					$(PARSER_DIR)/ast_build/create_ast_node.c \
					$(PARSER_DIR)/ast_build/find_matching_paren.c \
					$(PARSER_DIR)/ast_build/find_split_point.c \
					$(PARSER_DIR)/ast_build/handle_parentheses.c \
					$(PARSER_DIR)/ast_build/is_redirect_token.c \
					$(PARSER_DIR)/ast_build/build_ast/build_ast.c \
					$(PARSER_DIR)/ast_build/build_ast/count_word_tokens.c \
					$(PARSER_DIR)/ast_build/build_ast/disconnect_tokens.c \
					$(PARSER_DIR)/ast_build/build_ast/is_valid_operator.c \
					$(PARSER_DIR)/ast_build/build_ast/reconnect_tokens.c \
					$(PARSER_DIR)/ast_build/build_ast/update_paren_level.c \
					$(PARSER_DIR)/ast_build/build_ast/update_split_point.c \
					$(PARSER_DIR)/ast_build/command_node/allocate_cmd_args.c \
					$(PARSER_DIR)/ast_build/command_node/build_command_node.c \
					$(PARSER_DIR)/ast_build/command_node/count_command_words.c \
					$(PARSER_DIR)/ast_build/command_node/fill_cmd_args.c \
					$(PARSER_DIR)/ast_build/command_node/fill_cmd_args_utils.c \
					$(PARSER_DIR)/ast_build/command_node/free_tab.c \
					$(PARSER_DIR)/ast_build/command_node/get_redirect_type.c \
					$(PARSER_DIR)/ast_build/command_node/handle_env_var_token.c \
					$(PARSER_DIR)/ast_build/command_node/handle_env_var.c \
					$(PARSER_DIR)/ast_build/command_node/handle_redirect_count.c \
					$(PARSER_DIR)/ast_build/command_node/handle_redirection.c \
					$(PARSER_DIR)/ast_build/command_node/handle_word_token.c \
					$(PARSER_DIR)/ast_build/command_node/handle_word.c \
					$(PARSER_DIR)/ast_build/command_node/process_env_tokens.c \
					$(PARSER_DIR)/prompt/get_prompt.c \
					$(PARSER_DIR)/environment/handle_no_env.c \
					$(PARSER_DIR)/prompt/append_prompt_suffix.c \
					$(PARSER_DIR)/prompt/clean_existing_prompt.c \
					$(PARSER_DIR)/prompt/create_base_prompt.c \
					$(PARSER_DIR)/prompt/create_initial_prompt.c \
					$(PARSER_DIR)/prompt/create_path_prompt.c \
					$(PARSER_DIR)/prompt/create_user_host_name.c \
					$(PARSER_DIR)/prompt/get_colored_cwd.c \
					$(PARSER_DIR)/prompt/get_hostname.c \
					$(PARSER_DIR)/prompt/get_user_host.c \
					$(PARSER_DIR)/prompt/get_username.c \
					$(BUILTINS_DIR)/cd.c \
					$(BUILTINS_DIR)/echo.c \
					$(BUILTINS_DIR)/env.c \
					$(BUILTINS_DIR)/exit.c \
					$(BUILTINS_DIR)/export.c \
					$(BUILTINS_DIR)/pwd.c \
					$(BUILTINS_DIR)/unset.c \
					$(BUILTINS_DIR)/env_set.c \
					$(BUILTINS_DIR)/expand.c \
					$(BUILTINS_DIR)/utils.c \
					$(WILDCARD_DIR)/ft_wildcard.c \
					$(HISTORY_DIR)/add_to_both_histories.c \
					$(HISTORY_DIR)/get_history_filepath.c \
					$(HISTORY_DIR)/init_local_history.c \
					$(HISTORY_DIR)/load_history_from_file.c \
					$(HISTORY_DIR)/save_history_to_file.c

OBJ 			:= 	$(patsubst $(SRCS_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ) $(INCLUDE)
	@$(CC) $(CFLAGS) $(SRC) $(LIBFT) -o $(NAME) $(LDFLAGS)
	@echo "${GREEN}Minishell compiled${NC}"

$(OBJ_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean --no-print-directory
	@echo "${RED}Objects removed${NC}"

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean --no-print-directory
	@echo "${RED}Objects and executable removed${NC}"

re: fclean all

$(LIBFT):
	@make -C $(LIBFT_DIR) all --no-print-directory

valgrind: re
	valgrind $(VFLAGS) ./$(NAME)

sanitizer: $(LIBFT) $(OBJ) $(INCLUDE)
	$(CC) $(SFLAGS) $(CFLAGS) $(SRC) $(LIBFT) -o $(NAME) $(LDFLAGS)
	./$(NAME)
	make -C . fclean

.PHONY: all clean fclean re valgrind sanitizer

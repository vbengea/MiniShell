NAME		:=	minishell

LIBFT_DIR	:= 	./libft
LIBFT		:= 	$(LIBFT_DIR)/libft.a

CC			:= 	cc
CFLAGS		:= 	-Wall -Wextra -Werror
SFLAGS		:= 	-g3 -fsanitize=address
LFLAGS		:= 	$(LIBFT)

EXEC_DIR			:=	executor
INCLUDE		:= 	include/executor.h
SRC			:= 	$(EXEC_DIR)/executor.c $(EXEC_DIR)/procecss.c $(EXEC_DIR)/utils.c
SRCB		:= 	exec

OBJ 		:= 	$(patsubst $(EXEC_DIR)/%.c, $(EXEC_DIR)/%.o, $(SRC))
OBJB 		:= 	$(SRCB:.c=.o)

ARGS		:=	""

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ) $(INCLUDE)
	$(CC) $(CFLAGS) $(SRC) $(LFLAGS) -o $(NAME)

clean:
	make -C $(LIBFT_DIR) clean
	rm -f *.o
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

$(EXEC_DIR)/%.o: $(EXEC_DIR)/%.c
	rm -f bonus
	$(CC) $(CFLAGS) -c -o $@ $<

norm: fclean
	norminette $(SRC) $(INCLUDE)

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

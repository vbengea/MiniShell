CC := cc
AFLAGS := crs
CFLAGS := -Wall -Werror -Wextra

SRC		:=	ft_printf.c \
			parser.c parser_delegate.c \
			converter.c converter_delegate.c \
			formatter.c formatter_delegate.c

SRC		:=	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c\
			ft_toupper.c ft_tolower.c ft_atoi.c ft_strdup.c\
			ft_strlen.c ft_strlcpy.c ft_strlcat.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_strnstr.c\
			ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c\
			ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c\
			ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_memchr.c ft_memcmp.c ft_calloc.c\
			get_next_line.c get_next_line_utils.c \
			ft_printf.c \
			parser.c parser_delegate.c \
			converter.c converter_delegate.c \
			formatter.c formatter_delegate.c \
			ft_isspace.c

BSRC	:=	ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c\
			ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c\
			ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c\

OBJ := $(SRC:.c=.o)
BOBJ := $(BSRC:.c=.o)
NAME := libft.a
INCLUDE := libft.h

all: $(NAME)

$(NAME): $(OBJ) $(INCLUDE)
	ar $(AFLAGS) $(NAME) $(OBJ)

bonus: bonus.bonus

bonus.bonus: $(OBJ) $(BOBJ) $(INCLUDE)
	ar $(AFLAGS) $(NAME) $(BOBJ) $(OBJ)
	touch bonus.bonus

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ) $(BOBJ)
	rm -f bonus.bonus

fclean: clean
	rm -f $(NAME)

re: fclean all

runner:
	$(CC) ../main.c *.c *.h && ./a.out && rm -f a.out
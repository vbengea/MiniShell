/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 23:08:22 by juandanielf       #+#    #+#             */
/*   Updated: 2025/01/24 17:48:08 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H

# define LIBFT_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include <fcntl.h>
# include <stdarg.h>
# include <stdbool.h>

void			*ft_memchr(const void *s, int c, size_t n);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
int				ft_isprint(int c);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
char			*ft_strnstr(const char *big, const char *little, size_t len);
int				ft_atoi(const char *nptr);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_itoa(int n);
void			ft_putnbr_fd(int n, int fd);
char			*ft_strtrim(char const *s1, char const *set);
char			**ft_split(char const *s, char c);
void			*ft_calloc(size_t nmemb, size_t size);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_toupper(int c);
int				ft_tolower(int c);
size_t			ft_strlen(const char *s);
size_t			ft_strlcpy(char *dst, const char *src, size_t size);
char			*ft_strdup(const char *s);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void			ft_striteri(char *s, void (*f)(unsigned int, char*));
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
void			*ft_memset(void *s, int c, size_t n);
void			ft_bzero(void *s, size_t n);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_memmove(void *dest, const void *src, size_t n);
void			clear_arr_of_strs(char **sp);
bool			ft_isspace(char c);
char			*ft_strndup(const char *s, size_t n);
char			*ft_strcpy(char *dst, const char *src);


typedef struct splitter
{
	size_t	i;
	size_t	start;
	size_t	end;
	size_t	count;
	size_t	result;
}	t_splitter;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

t_list			*ft_lstnew(void *content);
void			ft_lstadd_front(t_list **lst, t_list *new);
int				ft_lstsize(t_list *lst);
t_list			*ft_lstlast(t_list *lst);
void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstdelone(t_list *lst, void (*del)(void*));
void			ft_lstclear(t_list **lst, void (*del)(void*));
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *), \
	void (*del)(void *));

typedef struct specifier
{
	va_list	*lst;
	char	flags[7];
	char	conversions[10];
	char	conversion;
	char	ch;
	char	sign;

	char	*base;
	char	*str;

	int		precision;

	size_t	flag_pound;
	size_t	flag_zero;
	size_t	flag_minus;
	size_t	flag_space;
	size_t	flag_plus;
	size_t	flag_asterisk;
	size_t	width;
	size_t	is_numeric;
	size_t	is_positive;
	size_t	is_signed;
	size_t	is_precision_dot;
	size_t	count;
}	t_spec;

int				ft_printf(char const *str, ...);
char			*max_negative_to_positive(void);

int				parse_token(char *str, t_spec *sp);
void			numeric_stats(long double n, t_spec *sp);
void			set_str_base(char *str, unsigned long n, int i, \
	char const *base);
int				digits_count_base(unsigned long n, char const *base);
void			set_flag(char c, t_spec *sp);
void			do_asterisk(t_spec *sp);

int				convert_specifier(t_spec *sp, int i);
void			convert_char(t_spec *sp);
void			convert_str(t_spec *sp, char *str);
void			convert_unsigned(unsigned long n, char const *base, t_spec *sp);
void			convert_hex(unsigned long n, int is_up, t_spec *sp);
void			convert_integer(int n, t_spec *sp);

void			pad_str(t_spec *sp);
int				is_zero(char *s);
char			get_pad(t_spec *sp);
void			prepad(t_spec *sp, char *chopped);
int				allow_precision(t_spec *sp, int len);
int				validate(t_spec *sp);

typedef struct descriptor
{
	int					fd;
	char				*buffer;
	struct descriptor	*next;
}	t_descriptor;

char			*get_next_line(int fd);
void			*cap_alloc(char *str, size_t size, char **buffer);
size_t			size_str(char *str);
t_descriptor	*find_fd(t_descriptor *fds, int fd);
void			remove_descriptor(t_descriptor	*fds, t_descriptor *tmp);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10000000
# endif

#endif

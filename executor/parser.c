/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaflore <juaflore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 20:48:23 by jflores           #+#    #+#             */
/*   Updated: 2025/01/25 16:49:17 by juaflore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

char **	args_helper(char *arg1, char *arg2)
{
	char **arr = malloc(sizeof(char *) * 3);
	arr[0] = ft_strdup(arg1);
	arr[1] = ft_strdup(arg2);
	arr[2] = NULL;
	return (arr);
}

static	void	add_segment(char ***elements, char *context, int k, int i)
{
	char *str;

	while (ft_isspace(context[k]))
		k++;
	str = ft_substr(context, k, i - k);
	*elements = add_arr_of_strs(*elements, str);
	free(str);
}

static	int	ff_subcontext(char *context)
{
	int i = 0;
	int p = 0;

	i = 0;
	if (context[i] == '(')
	{
		while (context[i])
		{
			if (context[i] == '(')
				p++;
			else if (context[i] == ')')
				p--;
			if (p == 0)
				break ;
			i++;
		}
	}
	else if (context[i] == 34)
	{
		i++;
		while (context[i] != 34)
			i++;
	}
	else if (context[i] == 39)
	{
		i++;
		while (context[i] != 39)
			i++;
	}
	return (i + 1);
}

static	char **parse_elements(char *context, char *token)
{
	char **elements;
	int	token_len = ft_strlen(token);
	int i = 0;
	int j = 0;
	int k = 0;

	elements = malloc(sizeof(char *) * 2);
	elements[0] = ft_strdup(" ");
	elements[1] = NULL;
	(void) j;
	if (elements)
	{
		while (context[i])
		{
			if (ft_isquote(context[i]) || context[i] == '(')
				i += ff_subcontext((context + i));
			else if (ft_strncmp((context + i), token, token_len) == 0)
			{
				add_segment(&elements, context, k, i);
				j++;
				i += token_len;
				k = i;
				continue ;
			}
			else
				i++;
		}
		add_segment(&elements, context, k, i);
	}
	return (elements);
}

t_redirection	*redlist_new(void *content)
{
	t_redirection	*lst;

	lst = malloc(sizeof(t_redirection));
	if (lst)
	{
		lst->file = content;
		lst->next = NULL;
	}
	return (lst);
}

void	redlist_add(t_redirection **lst, t_redirection *new)
{
	t_redirection	*tmp;

	tmp = *lst;
	*lst = new;
	(*lst)->next = tmp;
}

void	redlist_iter(t_redirection *lst, void (*f)(void *))
{
	while (lst)
	{
		(*f)(lst->file);
		if (lst->next == NULL)
			break ;
		lst = lst->next;
	}
}

static	int	capture_redirection(t_ast_node *ast, char *str)
{
	int				i = 0;
	int				j = 0;
	int				ri = 0;
	int				ro = 0;
	int				prefix = -1;
	int				suffix = -1;
	char			*file;
	t_redirection	*lst;

	if (str[i] == '0' || str[i] == '1' || str[i] == '2')
	{
		prefix = str[i] - '0';
		i++;
	}
	if (str[i] == '<')
	{
		i++;
		ri++;
	}
	else if (str[i] == '>')
	{
		i++;
		ro++;
	}
	if (str[i] == '<')
	{
		i++;
		ri++;
	}
	else if (str[i] == '>')
	{
		i++;
		ro++;
	}
	if (str[i] == '&')
	{
		i++;
		if (str[i] == '1' || str[i] == '2')
		{
			file = ft_strdup(" ");
			suffix = str[i] - '0';
			i++;
		}
		else
		{		
			perror("minishell: syntax error near unexpected token `&'");
			return (0);
		}
	}
	else
	{
		while (str[i] && ft_isspace(str[i]))
			i++;
		j = i;
		while (str[j] && !ft_isspace(str[j]))
			j++;
		if ((j - i) == 0)
			return (0);
		file = ft_substr(str, i, j - i);
		if (!file)
			return (0);
		i = j;
	}
	lst = redlist_new((void *)file);
	redlist_add(&(ast->redirs), lst);
	lst->type = REDIRECT_NONE;
	if (ri == 1)
		lst->type = REDIRECT_IN;
	else if (ri == 2)
		lst->type = REDIRECT_HEREDOC;
	else if (ro == 1)
		lst->type = REDIRECT_OUT;
	else if (ro == 2)
		lst->type = REDIRECT_APPEND;
	if (prefix == 1 && suffix == -1)
		lst->otype = STDOUT_FILE;
	else if (prefix == 2 && suffix == -1)
		lst->otype = STDERR_FILE;
	else if (prefix == 1 && suffix == 2)
		lst->otype = STDOUT_STDERR;
	else if (prefix == 2 && suffix == 1)
		lst->otype = STDERR_STDOUT;
	return (i);
}

static	char *parse_redirections(t_ast_node *ast, char *str)
{
	int		i = 0;
	int		j = 0;
	char	*s;
	char	*p;

	while (str[i])
	{
		j = 0;
		if (str[i] == '<' || str[i] == '>')
		{
			if (i > 0 && (str[i - 1] == '0' || str[i - 1] == '1' || str[i - 1] == '2'))
			{
				p = (str + i - 1);
				j = capture_redirection(ast, p) - 1;
			}
			else
			{
				p = (str + i);
				j = capture_redirection(ast, p);
			}
			if (j > 0 && (str[i - 1] == '0' || str[i - 1] == '1' || str[i - 1] == '2'))
				str[i - 1] = ' ';
			j += i;
			while (i < j)
				str[i++] = ' ';
		}
		i++;
	}
	s = ft_strtrim(str, " ");
	return (s);
}

static	t_ast_node	*create_node_command(char *str)
{
	t_ast_node	*ast;
	char		**elements;
	char		*cmd;
	char		*args;
	int			len;

	ast = create_ast_node(NODE_CMND, args_helper(" ", " "));
	str = parse_redirections(ast, str);
	elements = ft_split(str, ' ');
	cmd = elements[0];
	len = ft_strlen(cmd);
	args = ft_strtrim((str + len), " ");
	ast->args = args_helper(cmd, args);
	clear_arr_of_strs(elements);
	free(args);
	return (ast);
}

static	t_ast_node	*get_node_by_token(char *token)
{
	t_ast_node	*ast;

	ast = NULL;
	if (ft_strcmp(token, "&&") == 0)
		ast = create_ast_node(NODE_AND, NULL);
	else if (ft_strcmp(token, "|") == 0)
		ast = create_ast_node(NODE_PIPE, NULL);
	else if (ft_strcmp(token, "(") == 0)
		ast = create_ast_node(NODE_GROUP, NULL);
	return (ast);
}

static	t_ast_node	*create_and_list(char *context, char *token, int level)
{
	int			i;
	char		**elements;
	char		*str;
	t_ast_node	*ast;
	t_ast_node	*rast;
	t_ast_node	*child;
	int			len;

	ast = NULL;
	rast = NULL;
	elements = parse_elements(context, token);
	len = 0;
	while (elements[len])
		len++;
	i = 1;
	if (ft_strcmp(token, "&&") != 0 && ft_strcmp(token, "|") != 0)
	{
		if(elements[i][0] == '(')
		{
			str = ft_substr(elements[i], 1, ff_subcontext(elements[i]) - 2);
			rast = get_node_by_token("(");
			rast->left = create_and_list(str, "&&", level + 1);
			free(str);
		}
		else
			rast = create_node_command(elements[i]);
	}
	else
	{
		ast = get_node_by_token(token);
		rast = ast;
		i = len - 1;
		while (i > 0)
		{
			if (ft_strcmp(token, "&&") == 0)
				child = create_and_list(elements[i], "|", level + 1);
			else if (ft_strcmp(token, "|") == 0)
				child = create_and_list(elements[i], "\7", level + 1);
			if (len == 2)
				rast = child;
			else if (ast->right)
			{
				if (i == 1)
					ast->left = child;
				else
				{
					ast->left = get_node_by_token(token);
					ast->left->right = child;
					ast = ast->left;
				}
			}
			else
				ast->right = child;
			i--;
		}
	}
	clear_arr_of_strs(elements);
	return (rast);
}

static	void	print_redirs(void *content)
{
	char *str;

	str = (char *) content;
	printf("%s, ", str);
}

static	void	ast_printer(t_ast_node *ast, int level)
{
	int i = 0;

	while (i++ < level)
		printf("  ");
	if (ast->type == NODE_CMND)
	{
		printf("Type: %d, args: %s, %s	R: ", ast->type, ast->args[0], ast->args[1]);
		redlist_iter(ast->redirs, print_redirs);
		printf("\n");
	}
	else
		printf("Type: %d\n", ast->type);
	if (ast->left)
		ast_printer(ast->left, level + 1);
	if (ast->right)
		ast_printer(ast->right, level + 1);
}

t_ast_node	*build_redirect_ast(char *context)
{
	t_ast_node	*ast;
	
	ast = create_and_list(context, "&&", 0);
	ast_printer(ast, 0);
	return (ast);
}

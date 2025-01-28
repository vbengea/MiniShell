/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_functions.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 18:18:52 by vbengea           #+#    #+#             */
/*   Updated: 2025/01/28 18:48:54 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_FUNCTIONS_H
# define TOKENIZER_FUNCTIONS_H

#include "headers.h"

t_token	*create_token(t_token_tpype type, char *value);
void	add_token(t_token **head, t_token *new_token);
void	skip_whitespace(const char *input, int *i);
bool		is_operator(char c);
void	handle_operator(t_token **head, t_token *new_token, \
		const char *input, int *i);
t_token	*tokenize(const char *input, int *i);
t_token	*create_word_token(const char *input, int *i);
bool	is_quote(char c);
t_token	*create_quoted_token(const char *input, int *i);
void	handle_parens(t_token **head, t_token *new_token, char op, int count);
void	handle_double_operators(t_token **head, t_token *new_token, char op);
void	handle_single_operator(t_token **head, t_token *new_token, char op);
int		count_consecutive_operators(const char *input, int *i, char op);
t_ast_node	*create_ast_node(t_node_type type, char **cmd_args);
t_ast_node	*build_ast(t_token *tokens);
void free_ast(t_ast_node *node);
void print_ast(t_ast_node *node, int level);

t_ast_node	*create_ast_node(t_node_type type, char **cmd_args);

t_ast_node	*handle_parentheses(t_token *tokens);
t_token	*find_matching_paren(t_token *tokens);
t_token	*find_split_point(t_token *tokens);


t_ast_node	*build_command_node(t_token *tokens);

t_ast_node	*build_operator_node(t_ast_node *left ,t_token *split_point);

t_ast_node	*create_redirect_node(t_token *token);
t_ast_node	*build_ast(t_token *tokens);
t_ast_node *build_ast_with_inner(t_ast_node *inner, t_token *rest);




/* Nuevas */
void	update_paren_level(int *level, t_token_tpype type);
void	update_split_point(t_token **split, t_token *current, int *min_prec);
int	count_word_tokens(t_token *tokens);
void	disconnect_tokens(t_token *start, t_token *split);
void	reconnect_tokens(t_token *start, t_token *split);
int	is_valid_operator(t_token_tpype type);
int	is_redirect_token(t_token_tpype type);



void free_ast(t_ast_node *node);
void print_ast(t_ast_node *node, int level);




/* TOKENIZE */
void	skip_whitespace(const char *input, int *i);
bool	is_operator(char c);
bool	is_quote(char c);
void dispatch_operator(t_token **head, t_token *new_token, char op, int count);
void handle_operator(t_token **head, t_token *new_token, const char *input, int *i);
t_token *tokenize(const char *input, int *i);
t_token	*tokenize_input(const char *input);
void	free_token(t_token *token);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_functions.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 18:18:52 by vbengea           #+#    #+#             */
/*   Updated: 2025/02/13 20:29:53 by jflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_FUNCTIONS_H
# define TOKENIZER_FUNCTIONS_H

# include "headers.h"

t_token	*create_quoted_token(const char *input, int *i);
t_token	*create_token(t_token_type type, char *value);
t_token	*tokenize(const char *input, int *i);
t_token	*create_word_token(const char *input, int *i);
t_token	*tokenize_input(const char *input);

void	add_token(t_token **head, t_token *new_token);
void	skip_whitespace(const char *input, int *i);
void	handle_double_operators(t_token **head, t_token *new_token, char op);
void	handle_single_operator(t_token **head, t_token *new_token, char op);
void	handle_parens(t_token **head, t_token *new_token, char op, int count);
void	dispatch_operator(t_token **head, t_token *new_token, \
		char op, int count);

void	handle_operator(t_token **head, t_token *new_token, \
		const char *input, int *i);

int		count_consecutive_operators(const char *input, int *i, char op);

bool	is_operator(char c);
bool	is_quote(char c);

void	free_token(t_token *token);

t_token *create_env_var_token(const char *input, int *i);
int is_env_var_declaration(const char *input, int *i);

/* Nuevas */
t_token *create_fd_redirection_token(const char *input, int *i);
t_token *create_invalid_operator_token(const char *input, int *i);


bool	check_syntax(t_token *tokens, t_token *prev);


#endif
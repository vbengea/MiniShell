/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_functions.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 18:18:52 by vbengea           #+#    #+#             */
/*   Updated: 2025/01/25 13:33:06 by vbengea          ###   ########.fr       */
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

#endif
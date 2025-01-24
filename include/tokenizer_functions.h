/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_functions.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 18:18:52 by vbengea           #+#    #+#             */
/*   Updated: 2025/01/24 18:29:09 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_FUNCTIONS_H
# define TOKENIZER_FUNCTIONS_H

#include "headers.h"

t_token	*create_token(t_token_tpype type, char *value);
void	add_token(t_token **head, t_token *new_token);
void	skip_whitespace(const char *input, int *i);
int		is_operator(char c);
void	handle_operator(t_token **head, t_token *new_token, \
		const char *input, int *i);
t_token	*tokenize(const char *input, int *i);


#endif
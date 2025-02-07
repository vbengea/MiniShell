/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_build.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:29:19 by vbengea           #+#    #+#             */
/*   Updated: 2025/02/07 20:37:05 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_BUILD_H
# define AST_BUILD_H

# include "headers.h"

t_ast_node	*build_ast(t_token *tokens);
t_ast_node	*create_ast_node(t_node_type type, char **cmd_args);
t_ast_node	*handle_parentheses(t_token *tokens);
t_ast_node	*build_command_node(t_token *tokens);
t_ast_node	*build_operator_node(t_ast_node *left, t_token *split_point);
t_ast_node	*create_redirect_node(t_token *token);

t_token		*find_matching_paren(t_token *tokens);
t_token		*find_split_point(t_token *tokens);

void		update_paren_level(int *level, t_token_type type);
void		update_split_point(t_token **split, \
			t_token *current, int *min_prec);
void		disconnect_tokens(t_token *start, t_token *split);
void		reconnect_tokens(t_token *start, t_token *split);

int			count_word_tokens(t_token *tokens);
int			is_valid_operator(t_token_type type);
int			is_redirect_token(t_token_type type);

void		free_ast(t_ast_node *node);
void		print_ast(t_ast_node *node, int level);







void add_redirection(t_ast_node *node, t_redirect_type type, t_out_redirect_type otype, char *file);


/* BUILD COMMAND NODE */
int				count_command_words(t_token *tokens);
char			**allocate_cmd_args(int count);
t_redirect_type	get_redirect_type(t_token_type type);
int				handle_redirection(t_ast_node *node, t_token **current);
int				fill_cmd_args(t_token *tokens, char **cmd_args, t_ast_node *node);
t_ast_node		*build_command_node(t_token *tokens);


/* HANDLE PARENTHESES */



#endif

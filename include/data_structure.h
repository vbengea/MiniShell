/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_structure.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:34:39 by vbengea           #+#    #+#             */
/*   Updated: 2025/02/04 23:40:25 by jflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_STRUCTURE_H
# define DATA_STRUCTURE_H

typedef enum e_node_type
{
	NODE_CMND,
	NODE_PIPE,
	NODE_REDIRECT, // This will no longer be a type of node.
	NODE_AND,
	NODE_OR ,
	NODE_GROUP
}	t_node_type;

typedef enum e_redirect_type
{
	REDIRECT_NONE,
	REDIRECT_IN,
	REDIRECT_OUT,
	REDIRECT_APPEND,
	REDIRECT_HEREDOC
}	t_redirect_type;

typedef enum e_out_redirect_type
{
	STDOUT_FILE,
	STDERR_FILE,
	STDOUT_STDERR,
	STDERR_STDOUT
}	t_out_redirect_type;

/* Linked list for redirects */
typedef struct s_redirection
{
	t_redirect_type			type;
	t_out_redirect_type		otype;
	char					*file;
	struct s_redirection	*next;
}	t_redirection;

typedef enum mini_token
{
	AND,
	OR,
	PIPE,
	SUBSHELL,
	COMMAND,
	OTHER
}	t_mini_token;

typedef struct s_redirect_params
{
	int		ri;
	int		ro;
	int		prefix;
	int		suffix;
}	t_redirect_params;

/* Update structure.
	The proposed updates are commented untill they are implemented */
typedef struct s_ast_node
{
	t_node_type			type;
	t_node_type			parent_type;
	t_redirection		*redirs; // Linked list for redirections
	t_redirect_type		redirect_type; // This will no longer go here
	char				*file; // This will no longer go here
	char				**args;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
	struct s_ast_node	*parent;
	int					side;
	int					exit;
}	t_ast_node;

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_structure.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:34:39 by vbengea           #+#    #+#             */
/*   Updated: 2025/01/30 19:01:41 by vbengea          ###   ########.fr       */
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


/* Linked list for redirects */
typedef struct s_redirection
{
	t_redirect_type			type;
	char					*file;
	struct s_redirection	*next;
}	t_redirection;

/* Update structure.
	The proposed updates are commented untill they are implemented */
typedef struct s_ast_node
{
	t_node_type			type;
	t_node_type			parent_type;
	//t_redirection		*redirs; // Linked list for redirections
	t_redirect_type		redirect_type; // This will no longer go here
	char				**args;
	char				*file; // This will no longer go here
	struct s_ast_node	*left;
	struct s_ast_node	*right;
	struct s_ast_node	*parent;
	int					side;
}	t_ast_node;

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_structure.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea <vbengea@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:34:39 by vbengea           #+#    #+#             */
/*   Updated: 2025/02/13 13:36:06 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_STRUCTURE_H
# define DATA_STRUCTURE_H

typedef enum e_node_type
{
	NODE_CMND,
	NODE_PIPE,
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

	//quoted flag
	bool					is_quote;
}	t_redirection;

typedef enum mini_token
{
	COMMAND,
	PIPE,
	AND,
	OR,
	SUBSHELL,
	OTHER
}	t_mini_token;

typedef struct s_redirect_params
{
	int		ri;
	int		ro;
	int		prefix;
	int		suffix;
}	t_redirect_params;

typedef struct s_ast_node
{
	t_node_type			type;
	t_node_type			parent_type;
	t_redirection		*redirs;
	char				**args;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
	struct s_ast_node	*parent;
	int					side;
	int					exit;
	int					in_fd;
	int					out_fd;
	int					nid;
	int					has_group_in_fd;
	int					has_group_out_fd;
	int					discovered;
	bool				env_declare;
	bool				has_env;
	int					expand_flag[200];
	int					has_space[200];
}	t_ast_node;

#endif

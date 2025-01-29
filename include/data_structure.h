/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_structure.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea <vbengea@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:34:39 by vbengea           #+#    #+#             */
/*   Updated: 2025/01/27 12:11:27 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_STRUCTURE_H
# define DATA_STRUCTURE_H

typedef enum e_node_type
{
	NODE_CMND,
	NODE_PIPE,
	NODE_REDIRECT,
	NODE_AND,
	NODE_OR ,
	NODE_GROUP
}	t_node_type;

typedef struct s_ast_node
{
	t_node_type			type;
	t_node_type			parent_type;
	char				**args;
	char				*file;
	int					redirect_type; // ">" (1), "<" (2), ">>" (3).
	struct s_ast_node	*left;
	struct s_ast_node	*right;
	struct s_ast_node	*parent;
	int					side;
}	t_ast_node;

#endif

// Ejemplo de estructura si al final decidimos usar un array de hijos:

// typedef struct s_ast_node
// {
// 	t_node_type			type;
// 	char				**args;
// 	char				*file;
// 	int					redirect_type;
// 	struct s_ast_node	**children;
// 	int					child_count;
// } t_ast_node;

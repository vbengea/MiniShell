/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_structure.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaflore <juaflore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:34:39 by vbengea           #+#    #+#             */
/*   Updated: 2025/01/24 12:45:46 by juaflore         ###   ########.fr       */
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
	NODE_OR
}	t_node_type;

typedef struct s_ast_node
{
	t_node_type			type;
	char				**args;
	char				*file;
	int					redirect_type; // ">" (1), "<" (2), ">>" (3).
	struct s_ast_node	*left;
	struct s_ast_node	*right;
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

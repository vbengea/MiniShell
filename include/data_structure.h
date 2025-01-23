/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_structure.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:34:39 by vbengea           #+#    #+#             */
/*   Updated: 2025/01/23 09:09:13 by vbengea          ###   ########.fr       */
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

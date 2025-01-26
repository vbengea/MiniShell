/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast_with_inner.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 12:14:40 by vbengea           #+#    #+#             */
/*   Updated: 2025/01/26 12:15:22 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/headers.h"

t_ast_node *build_ast_with_inner(t_ast_node *inner, t_token *rest)
{
	if (!rest)
		return inner;
	
	t_ast_node *new_tree = build_ast(rest);
	if (!new_tree)
		return inner;

	t_ast_node *leftmost = new_tree;
	while (leftmost->left)
		leftmost = leftmost->left;
	
	leftmost->left = inner;
	return new_tree;
}

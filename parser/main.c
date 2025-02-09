/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 12:07:38 by vbengea           #+#    #+#             */
/*   Updated: 2025/02/09 18:33:54 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

void	assign_ids(t_ast_node *node, int *id)
{
	if (!node)
		return ;
	if (node->type == NODE_CMND)
		node->nid = ++(*id);
	assign_ids(node->left, id);
	assign_ids(node->right, id);
	}
/**
 * @warning test
 */
int main(void)
{
	t_token *token;
	t_ast_node *ast;
	char *input;

	while (true)
	{
		input = readline(GREEN "minishell$ " RESET);
		if (!input)
		{
			free_token(token);
			free (input);
			break;
		}

		if (input[0] == '\0')
		{
			free_token(token);
			free (input);
			break;
		}
		token = tokenize_input(input);
		if (check_syntax(token, NULL))
			ast = build_ast(token);
		else
			continue ;
		print_ast(ast, 0);

	}
	return (0);
}

// int main(void)
// {
// 	t_token *token;
// 	char *input;
// 	t_token *temp;

// 	while (true)
// 	{
// 		input = readline(GREEN "minishell$ " RESET);
// 		if (!input)
// 		{
// 			free_token(token);
// 			free (input);
// 			break;
// 		}

// 		if (input[0] == '\0')
// 		{
// 			free_token(token);
// 			free (input);
// 			break;
// 		}
// 		token = tokenize_input(input);

// 		temp = token;
// 		while (temp)
// 		{
// 			printf("Token type: %d, value: %s", temp->type, temp->value);
// 			printf("  has_env flag: %d\n", temp->has_env);
// 			temp = temp->next;
// 		}

// 	}
// 	return (0);
// }
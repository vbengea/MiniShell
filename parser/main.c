/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 12:07:38 by vbengea           #+#    #+#             */
/*   Updated: 2025/02/15 10:53:03 by vbengea          ###   ########.fr       */
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

	token = NULL;
	while (true)
	{
		input = readline(GREEN "minishell$ " RESET);
		if (!input)
		{
			if (token)
				free_token(token);
			break;
		}

		if (input[0] == '\0')
		{
			free (input);
			break;
		}
		if (token)
		{
			free_token(token);
			token = NULL;
		}
		token = tokenize_input(input);
		free (input);
		t_token *temp = token;
		if (check_syntax(token, NULL))
			ast = build_ast(token);
		else
		{
			free_token(temp);
			continue ;
		}
		print_ast(ast, 0);
		free_ast(ast);
	}
	return (0);
}

// int main(void)
// {
// 	t_token *token;
// 	char *input;
// 	t_token *temp;

// 	token = NULL;
// 	while (true)
// 	{
// 		input = readline(GREEN "minishell$ " RESET);
// 		if (!input)
// 		{
// 			if (token)
// 				free_token(token);
// 			break;
// 		}

// 		if (input[0] == '\0')
// 		{
// 			free (input);
// 			break;
// 		}
// 		if (token)
// 		{
// 			free_token(token);
// 			token = NULL;
// 		}
// 		token = tokenize_input(input);
// 		free(input);
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
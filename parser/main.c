/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 12:07:38 by vbengea           #+#    #+#             */
/*   Updated: 2025/01/27 19:42:22 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

void print_ast(t_ast_node *node, int level)
{
	if (!node)
		return;
	for (int i = 0; i < level; i++)
		printf("  ");
	printf("Node type: %d", node->type);
	if (node->args)
	{
		printf(", args: ");
		for (int j = 0; node->args[j] != NULL; j++)
		{
			printf("%s ", node->args[j]);
		}
	}
	if (node->file)
	{
		printf(", file: %s", node->file);
	}
	printf("\n");
	print_ast(node->left, level + 1);
	print_ast(node->right, level + 1);
}


void free_ast(t_ast_node *node)
{
	char	**cmd_args;
	int		i;

	if (!node)
		return;
	free_ast(node->left);
	free_ast(node->right);
	if (node->type == NODE_CMND || node->type == NODE_REDIRECT)
	{
		cmd_args = (char **)node->args;
		if (cmd_args)
		{
			i = 0;
			while (cmd_args[i])
			{
				free(cmd_args[i]);
				i++;
			}
			free(cmd_args);
		}
	}
	free(node);
}


/**
 * @warning test
 */
int main(void)
{
	t_token *token;
	t_ast_node *ast;
	char *input;

	//while (true)
	//{
		input = "ls -l && (cd .. && ls -l) || (grep a && cat -e)";//readline(GREEN "minishell$ " RESET);
		//if (!input)
			//break;

		token = tokenize_input(input);
		//printf("Input tokenized!\n");
		// while (token)
		// {
			// printf("Token type: %d, value: %s\n", token->type, token->value);
			// token = token->next;
		// }
		ast = build_ast(token);
		// printf("AST built!\n");

		print_ast(ast, 0);

		//free(input);
		free_token(token);
		free_ast(ast);
	//}
	return (0);
}
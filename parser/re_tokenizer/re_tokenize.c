/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_tokenize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 13:33:34 by vbengea           #+#    #+#             */
/*   Updated: 2025/02/01 13:33:54 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/headers.h"

t_pipeline *re_tokenize(t_token *token_list)
{
	t_pipeline *pipeline_list = NULL;
	t_pipeline *current_pipeline = NULL;
	t_command *current_command = NULL;
	t_redirection *current_redirection = NULL;

	t_token *current = token_list;

	while (current != NULL)
	{
		switch (current->type)
		{
			case TOKEN_WORD:
				if (current_command == NULL)
				{
					// Start a new command
					current_command = create_command(current->value);
					if (pipeline_list == NULL)
					{
						pipeline_list = create_pipeline();
						current_pipeline = pipeline_list;
					}
					current_pipeline->commands = current_command;
				}
				else
				{
					// Add argument to the current command
					add_argument(current_command, current->value);
				}
				break;

			case TOKEN_REDIRECT_IN:
			case TOKEN_REDIRECT_OUT:
			case TOKEN_APPEND:
			case TOKEN_HEREDOC:
				// Start a new redirection
				current_redirection = create_redirection(current->type);
				add_redirection(current_command, current_redirection);
				break;

			case TOKEN_PIPE:
				// End the current command and start a new one in the pipeline
				current_command = create_command(NULL);
				current_pipeline->commands->next = current_command;
				break;

			case TOKEN_AND:
			case TOKEN_OR:
				// Handle logical operators
				t_pipeline *new_pipeline = create_pipeline();
				current_pipeline->next = new_pipeline;
				current_pipeline = new_pipeline;
				break;

			case TOKEN_BG:
				// Mark the current command as background
				current_command->is_background = 1;
				break;

			case TOKEN_OPEN_PAREN:
				// Handle subshells (recursively)
				current_command = create_command(NULL);
				current_command->name = strdup("subshell");
				current_command->args = parse_subshell(current->next);
				break;

			case TOKEN_CLOSE_PAREN:
				// End of subshell
				break;

			default:
				// Handle other tokens (e.g., TOKEN_SPACE, TOKEN_INVALID)
				break;
		}

		current = current->next;
	}

	return pipeline_list;
}
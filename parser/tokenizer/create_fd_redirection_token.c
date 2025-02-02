/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_fd_redirection_token.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 19:41:29 by vbengea           #+#    #+#             */
/*   Updated: 2025/02/02 19:42:03 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/headers.h"

t_token *create_fd_redirection_token(const char *input, int *i)
{
	t_token *new_token;
	char fd_op[4]; // Enough space for "2>>", "2>", etc.
	int j = 0;

	// Capture the file descriptor (digit)
	while (isdigit(input[*i]))
	{
		fd_op[j++] = input[(*i)++];
	}

	// Capture the redirection operator
	if (input[*i] == '>' || input[*i] == '<')
	{
		fd_op[j++] = input[(*i)++];
	}

	// Handle double redirection operators like ">>"
	if (input[*i] == '>' || input[*i] == '<')
	{
		fd_op[j++] = input[(*i)++];
	}

	fd_op[j] = '\0';

	// Determine the type of redirection
	if (strstr(fd_op, ">>"))
	{
		new_token = create_token(TOKEN_APPEND_FD, fd_op);
	}
	else if (strstr(fd_op, ">"))
	{
		new_token = create_token(TOKEN_REDIRECT_FD_OUT, fd_op);
	}
	else if (strstr(fd_op, "<"))
	{
		new_token = create_token(TOKEN_REDIRECT_FD_IN, fd_op);
	}
	else
	{
		new_token = create_token(TOKEN_INVALID, "Invalid file descriptor redirection");
	}

	return new_token;
}
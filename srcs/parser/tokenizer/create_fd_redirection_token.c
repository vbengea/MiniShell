/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_fd_redirection_token.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 19:41:29 by vbengea           #+#    #+#             */
/*   Updated: 2025/03/04 19:12:40 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

t_token	*create_fd_redirection_token(const char *input, int *i)
{
	t_token	*new_token;
	char	fd_op[4];
	int		j;

	j = 0;
	while (isdigit(input[*i]))
		fd_op[j++] = input[(*i)++];
	if (input[*i] == '>' || input[*i] == '<')
		fd_op[j++] = input[(*i)++];
	if (input[*i] == '>' || input[*i] == '<')
		fd_op[j++] = input[(*i)++];
	fd_op[j] = '\0';
	if (strstr(fd_op, ">>"))
		new_token = create_token(TOKEN_APPEND_FD, ft_strdup(fd_op));
	else if (strstr(fd_op, ">"))
		new_token = create_token(TOKEN_REDIRECT_FD_OUT, ft_strdup(fd_op));
	else if (strstr(fd_op, "<"))
		new_token = create_token(TOKEN_REDIRECT_FD_IN, ft_strdup(fd_op));
	else
	{
		new_token = create_token(TOKEN_INVALID, \
			ft_strdup("Invalid file descriptor redirection"));
	}
	return (new_token);
}

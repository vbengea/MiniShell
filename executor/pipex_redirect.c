/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 19:15:33 by jflores           #+#    #+#             */
/*   Updated: 2025/02/16 19:16:00 by jflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

void	pipex_redirect_in(t_ast_node *node, int fd[2], int is_last, \
	t_terminal *tty)
{
	(void) is_last;
	(void) fd;
	if (detect_in_redirection(node, tty))
	{

	}
	else if (dup2(tty->files[0], STDIN_FILENO) == -1)
		perror("(1) Error redirecting");
	//tty->files[0] != STDIN_FILENO && 
}

void	pipex_redirect_out(t_ast_node *node, int fd[2], int is_last, \
	t_terminal *tty)
{
	(void) tty;
	if (detect_out_redirection(node))
		close(fd[1]);
	else if (is_last)
		close(fd[1]);
	else if (dup2(fd[1], STDOUT_FILENO) == -1)
		perror("(3) Error redirecting");
}

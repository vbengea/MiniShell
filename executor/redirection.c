/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaflore <juaflore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:47:10 by juaflore          #+#    #+#             */
/*   Updated: 2025/01/25 17:02:45 by juaflore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"

void	redirect_stdin(struct s_node **children)
{
	int	inre;

	if (children[0]->stdin)
	{
		inre = -1;
		if (children[0]->stdin == INFILE)
			inre = open(children[0]->stdin_value, O_RDONLY);
		else if (children[0]->stdin == HEREDOC)
			inre = here_doc(children[0]->stdin_value);
		if (inre < 0 || dup2(inre, STDIN_FILENO) == -1)
			cleanup("Error redirecting");
	}
}

void	redirect_stdout(int fd[2], struct s_node **children, t_node_type_u type)
{
	int	outre;

	if (children[0]->stdout)
	{
		outre = -1;
		if (children[0]->stdout == OUTFILE)
			outre = open(children[0]->stdout_value, O_WRONLY | O_CREAT | \
				O_TRUNC, 0666);
		else if (children[0]->stdout == APPEND)
			outre = open(children[0]->stdout_value, O_WRONLY | O_CREAT | \
				O_APPEND, 0666);
		if (outre < 0 || dup2(outre, STDOUT_FILENO) == -1)
			cleanup("Error redirecting");
	}
	else if (type == PIPE && *(children + 1) && (dup2(fd[1], \
		STDOUT_FILENO) == -1))
		cleanup("Error redirecting");
}

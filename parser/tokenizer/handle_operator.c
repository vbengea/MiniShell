/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_operator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 18:15:10 by vbengea           #+#    #+#             */
/*   Updated: 2025/02/02 11:53:20 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/headers.h"

// void	handle_operator(t_token **head, t_token *new_token, 
// 	const char *input, int *i)
// {
// 	char	op;
// 	int		count;

// 	op = input[*i];
// 	count = count_consecutive_operators(input, i, op);
// 	dispatch_operator(head, new_token, op, count);
// }


// Updated version
void	handle_operator(t_token **head, t_token *new_token, \
	const char *input, int *i)
{
	char	op;
	int		count;
	char	fd_op[3];

	op = input[*i];
	count = count_consecutive_operators(input, i, op);

	//Check for file descriptors redirection
	if (op >= '0' && op <= '9' && (input[*i] == '>' || input[*i] == '<'))
	{
		fd_op[0] = op;
		fd_op[1] = input[*i];
		fd_op[2] = '\0';
		new_token = create_token(TOKEN_REDIRECT_FD, fd_op);
		add_token(head, new_token);
		(*i)++;
	}
	else
		dispatch_operator(head, new_token, op, count);
}
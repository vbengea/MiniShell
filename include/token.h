/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 11:15:41 by vbengea           #+#    #+#             */
/*   Updated: 2025/01/24 19:34:27 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_AND,
	TOKEN_BG,
	TOKEN_OR,
	TOKEN_SPACE,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOEKN_EOF,
	TOKEN_INVALID,
	TOKEN_OPEN_PAREN,
	TOKEN_CLOSE_PAREN
}	t_token_tpype;

typedef struct	s_token
{
	t_token_tpype	type;
	char			*value;
	struct s_token	*next;
}	t_token;

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 11:15:41 by vbengea           #+#    #+#             */
/*   Updated: 2025/01/23 11:18:40 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_SPACE,
	TOEKN_EOF
}	t_token_tpype;

typedef struct	s_token
{
	t_token_tpype	type;
	char			*value;
	struct s_token	*next;
}	t_token;

#endif

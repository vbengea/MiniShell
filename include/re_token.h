/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_token.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 20:20:23 by vbengea           #+#    #+#             */
/*   Updated: 2025/02/01 13:36:04 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RE_TOKEN_H
# define RE_TOKEN_H

# include "headers.h"

typedef struct s_re_token
{
	char				*value;
	t_token_type		type;
	struct s_re_token	*prev;
	struct s_re_token	*next;
}	t_re_token;

t_re_token	*convert_to_double_linked_list(t_token *tokens);

#endif
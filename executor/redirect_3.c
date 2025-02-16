/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 12:10:56 by juaflore          #+#    #+#             */
/*   Updated: 2025/02/16 11:03:46 by jflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

char	*tmp_path(int nid, t_redirect_type type)
{
	char	*id;
	char	*file;

	id = ft_itoa(nid);
	file = NULL;
	if (id)
	{
		if (type == REDIRECT_OUT || type == REDIRECT_APPEND)
			file = ft_strjoin("tmp/__OUTFILE__", id);
		else if (type == REDIRECT_IN)
			file = ft_strjoin("tmp/__INFILE__", id);
		else if (type == REDIRECT_HEREDOC)
			file = ft_strjoin("tmp/__HEREDOC__", id);
		free(id);
	}
	return (file);
}

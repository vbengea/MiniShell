/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:44:37 by vbengea           #+#    #+#             */
/*   Updated: 2025/02/05 19:07:05 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARD_H
# define WILDCARD_H

# include "../include/headers.h"
# include <dirent.h>
# include <stdbool.h>

t_list	*ft_wildcard(char *input);

#endif

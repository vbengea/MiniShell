/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:09:20 by vbengea           #+#    #+#             */
/*   Updated: 2025/02/19 19:11:51 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

# include "headers.h"

char	*get_prompt(t_terminal *tty);
char	*get_hostname(void);
char	*create_user_host_prompt(char *user, char *host);
char	*get_username(void);
char	*get_colored_cwd(void);
char	*append_prompt_suffix(char *prompt);
char	*create_path_prompt(char *base_prompt);
char	*get_user_host(char **host_ptr);
char	*create_base_prompt(char *user, char *host);
char	*create_initial_prompt(char *base_prompt);
void	clean_existing_prompt(t_terminal *tty);

#endif
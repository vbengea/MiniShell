/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 11:22:57 by vbengea           #+#    #+#             */
/*   Updated: 2025/02/14 00:55:30 by jflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "headers.h"

int		cd_bi(t_ast_node *node, t_terminal *tty);
void	exit_bi(t_ast_node *node, t_terminal *tty);
void	pwd_bi(t_ast_node *node);
void	env_bi(t_ast_node *node, int sorted, t_terminal *tty);
void	export_bi(t_ast_node *node, t_terminal *tty);
void	unset_bi(t_ast_node *node, t_terminal *tty);
void	echo_bi(t_ast_node *node);
char	*get_env(char *var, t_terminal *tty);
void	set_env(char *key, char *value, t_terminal *tty);
char	*interpolation(char *str, t_terminal *tty);
char	**expantion(char *str, char **args);
char	*get_entry(char *key, char *value);
int		env_lookup(char *key, t_terminal *tty);

#endif

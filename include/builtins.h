/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 11:22:57 by vbengea           #+#    #+#             */
/*   Updated: 2025/02/23 14:10:37 by jflores          ###   ########.fr       */
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
char	*get_env(t_ast_node *node, int arg_index, char *key, t_terminal *tty);
void	set_env(t_ast_node *node, char *key, char *value, t_terminal *tty);
char	*interpolation(char *str, int arg_index, t_terminal *tty);
char	**expantion(char *str, char **args);
char	*get_entry(char *key, char *value);
int		env_lookup(char *key, t_ast_node *node, t_terminal *tty);
char	**env_resolution(t_terminal *tty, int hidden_level);
void	unset_one(char *key, t_ast_node *node, t_terminal *tty);

char	*clean_value(char *value, int *to_free);
int		validate_cmd_level(t_ast_node *node);
int		expand_flag(t_ast_node *node, int len, int *j);
int		get_arg_index(t_ast_node *node, char *key);

#endif

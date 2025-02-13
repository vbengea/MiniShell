/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 11:22:57 by vbengea           #+#    #+#             */
/*   Updated: 2025/02/13 20:28:43 by jflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "headers.h"

int		cd_bi(t_ast_node *node, t_terminal *tty);
void	exit_bi(t_ast_node *node, t_terminal *tty);
void	pwd_bi(t_ast_node *node);
void	env_bi(t_ast_node *node, int sorted, t_terminal *tty);
char	**export_bi(t_ast_node *node, t_terminal *tty);
char	**unset_bi(t_ast_node *node, t_terminal *tty);
void	echo_bi(t_ast_node *node);
char	*get_env(char *var, t_terminal *tty);
char	**set_env(char *var, char *value, t_terminal *tty);
char	*interpolation(char *str, t_terminal *tty);
char	**expantion(char *str, char **args);
void	check_shlvl(t_terminal *tty);
char	*interpolate(char *str, int *i, t_terminal *tty);

#endif

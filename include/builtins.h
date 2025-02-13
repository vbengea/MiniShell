/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaflore <juaflore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 11:22:57 by vbengea           #+#    #+#             */
/*   Updated: 2025/02/13 13:40:02 by juaflore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

int		cd_bi(t_ast_node *node, char ***env);
void	exit_bi(t_ast_node *node, char **env);
void	pwd_bi(t_ast_node *node);
void	env_bi(t_ast_node *node, char **env, int sorted);
char	**export_bi(t_ast_node *node, char **env);
char	**unset_bi(t_ast_node *node, char **env);
void	echo_bi(t_ast_node *node);
char	*get_env(char *var, char **env);
char	**set_env(char *var, char *value, char **env);
char	*interpolation(char *str, char **env);
char	**expantion(char *str, char **args);
void	check_shlvl(t_terminal *tty);
char	*interpolate(char *str, char **env, int *i);

#endif

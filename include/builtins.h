/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 11:22:57 by vbengea           #+#    #+#             */
/*   Updated: 2025/01/23 11:24:37 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

int		cd_bi(const char *path, char **env);
void	exit_bi(void);
void	pwd_bi(void);
void	env_bi(char **env);
char	**export_bi(const char *key, const char *value, char **env);
char	**unset_bi(const char *key, char **env);
void	echo_bi(char **params, char **env);

#endif

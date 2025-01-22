/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaflore <juaflore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 12:03:32 by juaflore          #+#    #+#             */
/*   Updated: 2025/01/22 12:44:20 by juaflore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H

# define EXECUTOR_H

# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

int		execute(char *cmd, char **arvp);
void	parent(int files[2], char **arvp, char **commands, int fd[2]);
void	children(int fd[2], int files[2], char **commands, char **arvp);
void	pipex(int files[2], char **arvp, char **commands);
void	process(int argc, char **argv, char **arvp, int files[2]);

char	*environment(char *name, char **env);
char	*find_path(char *cmd, char *env);
void	cleanup(char *err, char **commands);
int		doexec(char *path, char **comm, char **arvp, int is_free);

#endif

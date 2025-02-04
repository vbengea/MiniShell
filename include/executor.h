/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaflore <juaflore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 12:03:32 by juaflore          #+#    #+#             */
/*   Updated: 2025/01/25 17:01:46 by juaflore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H

# define EXECUTOR_H

# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# include "../libft/libft.h"
# include "./data_structure.h"

void		waiter(t_node_type type, t_ast_node *node);
void		selector(t_ast_node *node, char ***env, int file[3]);
void		forker(t_ast_node *node, char ***env, void (*f)(t_ast_node *node, char ***env, int hold, int files[3]), int files[3]);
void		navigator(t_ast_node *node, char ***env, int hold, int files[3]);
void		pipex(t_ast_node *node, char ***env, int files[3], int side);
void		executor(t_ast_node *node, char ***env, int hold, int files[3]);

char		*environment(char *name, char **env);
char		*find_path(char *cmd, char *env);
int			doexec(char *path, char **comm, char **arvp, int is_free);
int			execute(char **comm, char **arvp);

void		detect_in_redirection(t_ast_node *node);
void		detect_out_redirection(t_ast_node *node);
int			has_outward_redirection(t_redirection *lst);
int			has_inward_redirection(t_redirection *lst);
void		multiple_output_redirections(t_ast_node *node);
void		here_doc(char *delimit);
void		pipex_redirect(t_ast_node *node, int fd[2], int files[3], int is_last);

void		cleanup(char *err);
int			is_last_node(t_ast_node *node);
void		populate_node(t_ast_node *node, int side);
int			is_builtin(t_ast_node *node);
int			is_pipe_state(t_ast_node *node);

t_ast_node	*build_redirect_ast(char *context);

#endif

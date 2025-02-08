/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 12:03:32 by juaflore          #+#    #+#             */
/*   Updated: 2025/02/07 02:42:21 by jflores          ###   ########.fr       */
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

void			waiter(t_node_type type, t_ast_node *node, char ***env, int files[3]);
void			selector(t_ast_node *node, char ***env, int file[3]);
void			forker(t_ast_node *node, char ***env, void (*f)(t_ast_node *node, char ***env, int hold, int files[3]), int files[3]);
void			navigator(t_ast_node *node, char ***env, int hold, int files[3]);
void			executor(t_ast_node *node, char ***env, int hold, int files[3]);
void			pipex(t_ast_node *node, char ***env, int files[3]);

char			*environment(char *name, char **env);
char			*find_path(char *cmd, char *env);
int				doexec(char *path, char **comm, char **arvp, int is_free);
int				execute(char **comm, char **arvp);

int				detect_in_redirection(t_ast_node *node);
int				detect_out_redirection(t_ast_node *node);
int				has_outward_redirection(t_ast_node *ast);
int				has_inward_redirection(t_redirection *lst);
void			multiple_output_redirections(t_ast_node *node);
void			here_doc(t_ast_node *node, char *delimit, int do_write);
void			pipex_redirect_in(t_ast_node *node, int fd[2], int files[3], int is_last);
void			pipex_redirect_out(t_ast_node *node, int fd[2], int files[3], int is_last);
void			parse_command(t_ast_node *node, char ***env);

void			cleanup(char *err);
int				is_last(t_ast_node *node, int files[3]);
void			populate_node(t_ast_node *node, int side);
int				is_builtin(t_ast_node *node);
int				is_pipe_state(t_ast_node *node);

t_ast_node		*build_redirect_ast(char *context);

t_redirection	*redlist_new(void *content);
void			redlist_add(t_redirection **lst, t_redirection *new);
void			redlist_iter(t_redirection *lst, void (*f)(void *));
void			print_redirs(void *content);
void			ast_printer(t_ast_node *ast, int level);
void	        free_redirect_ast(t_ast_node *ast, int find_root);

char			*parse_redirections(t_ast_node *ast, char *str);
int				ff_subcontext(char *context);
t_ast_node		*get_node_by_token(t_mini_token token);
int				is_node(char *context, char *term);
int				is_control_character(char *context, t_mini_token level);
char			*read_files_content(char **files);
char			*read_fd_content(int tmp);

t_ast_node		*create_node_command(char *str, int *index);
t_ast_node		*create_structure(char *context, t_mini_token token, int *index);

t_redirection	*ft_lstred(t_redirection *node);
void			reverse_redirections(t_redirection *lst, t_redirection **rev);
int				has_group_redirection(t_ast_node *ast, int is_infile);
char			*tmp_path(int nid, t_redirect_type type);

#endif

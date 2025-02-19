/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 12:03:32 by juaflore          #+#    #+#             */
/*   Updated: 2025/02/19 21:37:44 by jflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H

# define EXECUTOR_H

# include "headers.h"

void			waiter(t_ast_node *node, t_terminal *tty);
void			selector(t_ast_node *node, t_terminal *tty);
void			forker(t_ast_node *node, void (*f)(t_ast_node *node, \
				int hold, t_terminal *tty), t_terminal *tty);
void			navigator(t_ast_node *node, int hold, t_terminal *tty);
void			executor(t_ast_node *node, int hold, t_terminal *tty);
void			pipex(t_ast_node *node, t_terminal *tty);

char			*environment(char *name, t_terminal *tty);
char			*find_path(char *cmd, char *penv);
int				doexec(t_ast_node *node, char **comm, int is_free, \
	t_terminal *tty);
int				execute(t_ast_node *node, char **comm, t_terminal *tty);

int				detect_in_redirection(t_ast_node *node, t_terminal *tty);
int				detect_out_redirection(t_ast_node *node);
int				has_outward_redirection(t_ast_node *ast);
int				has_inward_redirection(t_redirection *lst);
void			multiple_output_redirections(t_ast_node *node);
void			here_doc(t_ast_node *node, t_redirection *lst, \
				int do_write, t_terminal *tty);
void			pipex_redirect_in(t_ast_node *node, int fd[2], \
				int is_last, t_terminal *tty);
void			pipex_redirect_out(t_ast_node *node, int fd[2], \
				int is_last, t_terminal *tty);
void			parse_command(t_ast_node *node, t_terminal *tty);

void			cleanup(char *err, int code, t_ast_node *node, t_terminal *tty);
int				is_last(t_ast_node *node, t_terminal *tty);
int				is_builtin(t_ast_node *node);
int				is_pipe_state(t_ast_node *node);

void			print_redirs(void *content, int flag);
void			ast_printer(t_ast_node *ast, int level);
void			free_redirect_ast(t_ast_node *ast, int find_root);

char			*read_files_content(char **files);
char			*read_fd_content(int tmp);

int				has_group_redirection(t_ast_node *ast, int is_infile);
char			*tmp_path(int nid, t_redirect_type type);
void			builtin_selector(t_ast_node *node, int should_exit, \
				t_terminal *tty);
char			*read_path_content(char *path);
void			redlist_out(t_redirection *lst, char *content);
void			redlist_iter(t_redirection *lst, void (*f)(void *, int x));
int				is_identifier(char c);
void			ast_printer_node(t_ast_node *ast, int i);
int				do_outward_redirection(t_ast_node *node);
int				in_redirect_first(t_ast_node *node, t_terminal *tty);
void			nullify_exit(t_ast_node *node);
void			traverse_pipex(t_ast_node *node, t_terminal *tty, \
	int (*f)(t_ast_node *, t_terminal *));
int				check_options(t_ast_node *node, int hold, t_terminal *tty);
void			builtin_end(t_ast_node *node, int hold, t_terminal *tty);
void			preexecute(t_ast_node *node, t_terminal *tty);
void			postexecute(t_ast_node *node);
void			navigator_init(t_ast_node *node, t_terminal *tty);
void			set_history_status(int status, t_terminal *tty);
void			selector_node(t_ast_node *node, t_terminal *tty);
void			parse_command_inner(char **inter, t_ast_node *node, char ***args);
void			parse_command_master(t_ast_node *node, int i, char ***args, \
	t_terminal *tty);
#endif

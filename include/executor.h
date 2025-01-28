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

typedef enum node_type
{
	AND,
	OR,
	PIPE,
	EXEC
}	t_node_type_u;

typedef enum io
{
	STANDARD,
	INFILE,
	OUTFILE,
	HEREDOC,
	APPEND
}	t_io;

typedef struct s_node
{
	enum node_type	type;
	char			*value;
	struct s_node	**children;
	enum io			stdin;
	enum io			stdout;
	char			*stdin_value;
	char			*stdout_value;
}	t_node;

void		selector(t_ast_node *node, char **env);

void		redirect_stdin(struct s_node **children);
void		redirect_stdout(int fd[2], struct s_node **children, \
	t_node_type_u type);

char		*environment(char *name, char **env);
char		*find_path(char *cmd, char *env);
int			doexec(char *path, char **comm, char **arvp, int is_free);
int			execute(char **comm, char **arvp);

int			here_doc(char *delimit);
void		cleanup(char *err);
void		binode(t_ast_node *s, t_node_type type, int n, char *args[]);

void		binary(t_ast_node *node, char **env, int files[2], int side);
void		populate_node(t_ast_node *node, int side);
void		forkit(t_ast_node *node, char **env, int files[2], int side);

#endif

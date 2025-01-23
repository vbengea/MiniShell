/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaflore <juaflore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 12:03:32 by juaflore          #+#    #+#             */
/*   Updated: 2025/01/22 14:27:47 by juaflore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H

# define EXECUTOR_H

# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# include "../libft/libft.h"

typedef enum node_type {
	AND,
	OR,
	PIPE,
	EXEC
}	node_type;

typedef enum io {
	STANDARD,
	INFILE,
	OUTFILE,
	HEREDOC,
	APPEND
}	io;

typedef struct s_node
{
	enum node_type	type;
	char			*value;
	enum io			stdin;
	enum io			stdout;
	char 			*stdin_value;
	char			*stdout_value;
	struct s_node	**children;
}	t_node;

void	redirect(int fd[2], struct s_node **children, node_type type);
void	parent(int fd[2], struct s_node **children, char **env, node_type type);
void	child(int fd[2], struct s_node **children, char **env, node_type type);
void	pipex(struct s_node **children, char **env, int files[2], node_type type);
void	process(t_node *node, char **env, int fd[2]);

int		execute(char *cmd, char **arvp);
char	*environment(char *name, char **env);
char	*find_path(char *cmd, char *env);

int		here_doc(char *delimit);
void	cleanup(char *err);
int		doexec(char *path, char **comm, char **arvp, int is_free);

t_node*	get_tree();
t_node*	get_stree();
t_node*	get_stree2();
t_node*	get_stree3();
t_node*	get_stree4();

#endif

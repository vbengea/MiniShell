/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaflore <juaflore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 12:03:32 by juaflore          #+#    #+#             */
/*   Updated: 2025/01/24 12:50:28 by juaflore         ###   ########.fr       */
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
	struct s_node	**children;
	enum io			stdin;
	enum io			stdout;
	char 			*stdin_value;
	char			*stdout_value;
}	t_node;

void	redirect(int fd[2], struct s_node **children, node_type type);
void	parent(int fd[2], struct s_node **children, char **env, node_type type);
void	child(int fd[2], struct s_node **children, char **env, node_type type);
void	pipex(struct s_node **children, char **env, int files[2], node_type type);
void	process(t_node *node, char **env, int fd[2]);

char	*environment(char *name, char **env);
char	*find_path(char *cmd, char *env);
int		doexec(char *path, char **comm, char **arvp, int is_free);
int		execute(char *cmd, char **arvp);

int		here_doc(char *delimit);
void	cleanup(char *err);
void	ennode(t_node *s, enum node_type type, int n);
void	binode(t_ast_node *s, enum e_node_type type);

t_node*	get_tree(void);
t_node*	get_stree(void);
t_node*	get_stree2(void);
t_node*	get_stree3(void);
t_node*	get_stree4(void);

t_ast_node	*get_data_structure_1(void);

void	binary(t_ast_node *s, char **env, int fd[2]);

#endif

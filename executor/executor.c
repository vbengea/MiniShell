/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaflore <juaflore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 12:03:44 by juaflore          #+#    #+#             */
/*   Updated: 2025/01/22 14:28:58 by juaflore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"

int	argument_index(char **argv)
{
	if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) == 0)
		return (3);
	else
		return (2);
}

static	void	here_doc(int files[2], char *delimit, char *file2)
{
	char	*str;
	int		str_len;

	files[0] = open("__tmp__", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	str = get_next_line(STDIN_FILENO);
	str_len = ft_strlen(str);
	while (ft_strncmp(str, delimit, str_len - 1) != 0)
	{
		write(files[0], str, ft_strlen(str));
		free(str);
		str = get_next_line(STDIN_FILENO);
		str_len = ft_strlen(str);
	}
	free(str);
	close(files[0]);
	files[0] = open("__tmp__", O_RDONLY);
	files[1] = open(file2, O_WRONLY | O_CREAT | O_APPEND);
}

int	has_blank(char *str)
{
	if (ft_strchr(str, ' ') || ft_strchr(str, '\t' || ft_strchr(str, '\n') || \
		ft_strchr(str, '\v' || ft_strchr(str, '\r') || ft_strchr(str, '\f'))))
	{
		return (1);
	}
	return (0);
}

t_node*	get_ast()
{
	t_node	*s;

	s = malloc(sizeof(t_node));
	s->type = PIPE;
	return (s);
}

int	main(int argc, char **argv, char **env)
{
	t_node	*s;
	(void) argc;
	(void) argv;
	(void) env;
	(void) here_doc;
	s = get_ast();
	free(s);
	return (0);
}

// 							||							
// 													|
// 				&&							<< EOF		>>
// 		|				./mini.sh		cat -e				t2	
// ls -l		>
// 	cat -e		t2

	// (ls -l | cat -e > t2 && ./mini.sh ) || (cat -e << EOF | >>t2)
	// 1	OR
	// 2	

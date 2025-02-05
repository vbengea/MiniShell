/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:16:58 by vbengea           #+#    #+#             */
/*   Updated: 2025/02/05 19:29:58 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdbool.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

static	void	add_node(t_list **head, char *input)
{
	t_list	*new_node;
	t_list	*last;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return ;
	new_node->content = strdup(input);
	if (!new_node->content)
	{
		free(new_node);
		return ;
	}
	new_node->next = NULL;
	if (!*head)
	{
		*head = new_node;
		return ;
	}
	last = *head;
	while (last->next)
		last = last->next;
	last->next = new_node;
}

static	bool	match_pattern(const char *pattern, const char *str)
{
	while (*pattern && *str)
	{
		if (*pattern == '*')
		{
			pattern++;
			if (!*pattern)
				return (true);
			while (*str)
			{
				if (match_pattern(pattern, str))
					return (true);
				str++;
			}
			return (false);
		}
		if (*pattern != *str)
			return (false);
		pattern++;
		str++;
	}
	if (*pattern == '*')
		pattern++;
	return (!*pattern && !*str);
}

static	void	find_matches(t_list *files, char *input, t_list **matches)
{
	t_list	*current;

	current = files;
	*matches = NULL;
	while (current)
	{
		if (match_pattern(input, current->content))
			add_node(matches, current->content);
		current = current->next;
	}
}

static	void	free_files(t_list **files)
{
	t_list	*current;
	t_list	*next;

	current = *files;
	while (current)
	{
		next = current->next;
		free(current->content);
		free(current);
		current = next;
	}
	*files = NULL;
}

t_list	*ft_wildcard(char *input)
{
	DIR				*dir;
	t_list			*copy_files;
	t_list			*matches;
	struct dirent	*entry;

	copy_files = NULL;
	dir = opendir(".");
	if (!dir)
		return (NULL);
	entry = readdir(dir);
	while (entry)
	{
		add_node(&copy_files, entry->d_name);
		entry = readdir(dir);
	}
	closedir(dir);
	find_matches(copy_files, input, &matches);
	if (!matches)
		return (NULL);
	free_files(&copy_files);
	return (matches);
}

int main(int argc, char **argv)
{
	t_list	*matches;
	t_list	*current;

	if (argc != 2)
	{
		printf("Usage: %s <pattern>\n", argv[0]);
		return (1);
	}
	matches = ft_wildcard(argv[1]);
	if (!matches)
	{
		printf("No matches found\n");
		return (1);
	}
	current = matches;
	while (current)
	{
		printf("%s\n", (char *)current->content);
		current = current->next;
	}
	current = matches;
	while (current)
	{
		t_list	*next;

		next = current->next;
		free(current->content);
		free(current);
		current = next;
	}
	return (0);
}
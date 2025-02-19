/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:46:59 by vbengea           #+#    #+#             */
/*   Updated: 2025/02/19 18:00:00 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/headers.h"


static char	*get_hostname(void)
{
	char	*host;
	int		host_fd;

	host_fd = open("/etc/hostname", O_RDONLY);
	if (host_fd < 0)
		host = ft_strdup("minishell");
	else
	{
		host = get_next_line(host_fd);
		if (host)
			host[ft_strlen(host) - 1] = '\0';
		close(host_fd);
		if (!host)
			host = ft_strdup("minishell");
	}
	return (host);
}

static char	*get_username(void)
{
	char	*user;

	user = getenv("USER");
	if (!user)
		user = ft_strdup("minishell");
	else
		user = ft_strdup(user);
	return (user);
}

static char	*create_user_host_prompt(char *user, char *host)
{
	char	*partial_prompt;
	char	*color_prompt;
	char	*final_prompt;

	partial_prompt = ft_strjoin(user, "@");
	if (!partial_prompt)
		return (NULL);
	color_prompt = ft_strjoin(GREEN, partial_prompt);
	free(partial_prompt);
	if (!color_prompt)
		return (NULL);
	partial_prompt = ft_strjoin(color_prompt, host);
	free(color_prompt);
	if (!partial_prompt)
		return (NULL);
	final_prompt = ft_strjoin(partial_prompt, GREEN);
	free(partial_prompt);
	return (final_prompt);
}

static char *create_path_prompt(char *base_prompt)
{
	char	*partial_prompt;
	char	*color_prompt;
	char	*cwd;
	char	*final;

	partial_prompt = ft_strjoin(base_prompt, WHITE ":");
	if (!partial_prompt)
		return (NULL);
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		free(partial_prompt);
		return (NULL);
	}
	color_prompt = ft_strjoin(partial_prompt, BLUE);
	free(partial_prompt);
	if (!color_prompt)
	{
		free(cwd);
		return (NULL);
	}
	partial_prompt = ft_strjoin(color_prompt, cwd);
	free(color_prompt);
	free(cwd);
	if (!partial_prompt)
		return (NULL);
	final = ft_strjoin(partial_prompt, WHITE "€ " RESET);
	free(partial_prompt);
	return (final);
}

char	*get_prompt(t_terminal *tty)
{
	char	*host;
	char	*user;
	char	*user_host_prompt;
	char	*final_prompt;

	if (!tty)
		return (NULL);
	if (tty->prompt)
	{
		free(tty->prompt);
		tty->prompt = NULL;
	}
	host = get_hostname();
	if (!host)
		return (NULL);
	user = get_username();
	if (!user)
	{
		free(host);
		return (NULL);
	}
	user_host_prompt = create_user_host_prompt(user, host);
	free(user);
	free(host);
	if (!user_host_prompt)
		return (NULL);
	final_prompt = create_path_prompt(user_host_prompt);
	free(user_host_prompt);
	if (!final_prompt)
		return (NULL);
	tty->prompt = final_prompt;
	return (final_prompt);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 11:18:54 by vbengea           #+#    #+#             */
/*   Updated: 2025/01/23 12:33:10 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"
#include <string.h>


t_token	*create_token(t_token_tpype type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = value;
	token->next = NULL;
	return (token);
}

void	add_token(t_token **head, t_token *new_token)
{
	t_token	*tmp;

	if (!head || !new_token)
		return ;
	tmp = *head;
	if (!tmp)
	{
		*head = new_token;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_token;
}



t_token	*tokenize(const char *input)
{
	t_token	*head;
	int		start;
	int		i;

	head = NULL;
	i = 0;
	while (input[i])
	{
		if (ft_isspace(input[i]))
		{
			i++;
			continue ;
		}
		if (input[i] == '|')
		{
			add_token(&head, create_token(TOKEN_REDIRECT, ft_strdup("|")));
			i++;
		}
		else if (input[i] == '>')
		{
			if (input[i + 1] == '>')
			{
				add_token(&head, create_token(TOKEN_REDIRECT, ft_strdup(">>")));
				i += 2;
			}
			else
			{
				add_token(&head, create_token(TOKEN_REDIRECT, ft_strdup(">")));
				i++;
			}
		}
		else
		{
			start = i;
			while (input[i] && !ft_isspace(input[i]) && input[i] != '|' && input[i] != '>')
			{
				i++;
			}
			add_token(&head, create_token(TOKEN_WORD, ft_strndup(&input[start], i - start)));
		}
	}
	add_token(&head, create_token(TOEKN_EOF, NULL));
	return (head);
}

int main(void)
{
	char input[] = "cat < input.txt  | grep \"text\" | sort > output.txt";
	t_token *tokens;

	tokens = tokenize(input);

	while (tokens)
	{
		printf("Token type: %d\n", tokens->type);
		if (tokens->value)
			printf("Token value: %s\n", tokens->value);
		tokens = tokens->next;
	}
}

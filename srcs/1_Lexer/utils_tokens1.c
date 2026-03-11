/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tokens1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 10:51:57 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/03/11 16:14:58 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens;
		tokens = tokens->next;
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
}

t_token	*new_token(t_token_type type, char *value)
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

void	add_token(t_token **head, t_token *new)
{
	t_token	*tmp;

	if (!*head)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

char	*token_type_str(t_token_type type)
{
	if (type == WORD)
		return (WORD);
	if (type == PIPE)
		return (PIPE);
	if (type == REDIR_IN)
		return (REDIR_IN);
	if (type == REDIR_OUT)
		return (REDIR_OUT);
	if (type == APPEND)
		return (APPEND);
	if (type == HEREDOC)
		return (HEREDOC);
}

void	print_tokens(t_token *tokens)
{
	while (tokens)
	{
		printf("TYPE: %s", token_type_str(tokens->type));
		if (tokens->value)
			printf(" | VALUE: %s", tokens->value);
		else if (tokens->type == PIPE)
			printf(" | VALUE: |");
		else if (tokens->type == REDIR_OUT)
			printf(" | VALUE: >");
		else if (tokens->type == REDIR_IN)
			printf(" | VALUE: <");
		else if (tokens->type == APPEND)
			printf(" | VALUE: >>");
		else if (tokens->type == HEREDOC)
			printf(" | VALUE: <<");
		printf("\n");
		tokens = tokens->next;
	}
}

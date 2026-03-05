/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 15:54:24 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/03/05 19:44:56 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Lexer :
// Initialise index i
// Skip espaces
// Identifie type
// Appelle une fonction spécialisée
// Ajoute token à la liste
// Verifie les erreurs (ENCORE A VERIFIER !!!)

// 


#include "../../includes/minishell.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

t_token_type	get_operator_type(t_data *data)
{
	char	c;

	c = data->line[data->pos];
	if (c == '|')
	{
        	return (PIPE);
	}
	if (c == '>' && data->line[data->pos + 1] && data->line[data->pos + 1] == '>')
	{
		data->pos++;
		return (APPEND);
	}
	if (c == '<' && data->line[data->pos + 1] && data->line[data->pos + 1] == '<')
	{
		data->pos++;
		return (HEREDOC);
	}
	if (c == '<')
		return (INPUT);
	if (c == '>')
		return (OUTPUT);
	return (TOKEN_NONE);
}

char	*read_quote(t_data *data, char quote)
{
	char	buffer[1024];
	int	buf_pos;

	buf_pos = 0;
	data->pos++;
	while (data->line[data->pos] && data->line[data->pos] != quote && buf_pos < 1023)
	{
		buffer[buf_pos] = data->line[data->pos];
		data->pos++;
		buf_pos++;
	}
	if (data->line[data->pos] == quote)
		data->pos++;
	else
		{
			errno = EINVAL;
			printf("Error: quote %c not closed: %s\n", quote, strerror(errno));
			return (NULL);
		}
	buffer[buf_pos] = '\0';
	return (strdup(buffer));
}

int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

char	*read_normal_word(t_data *data)
{
	char	buffer[1024];
	int	buf_pos;

	buf_pos = 0;
//	while (data->line[data->pos] && !isspace(data->line[data->pos]) && data->line[data->pos] != '\'' && data->line[data->pos] != '"')
	while (data->line[data->pos] && !isspace(data->line[data->pos])  && !is_quote(data->line[data->pos]) && !is_operator(data->line[data->pos]))
	{
		buffer[buf_pos] = data->line[data->pos];
		data->pos++;
		buf_pos++;
	}
	buffer[buf_pos] = '\0';
	return (strdup(buffer));
}

char	*read_word(t_data *data)
{
	int	start;
	char	*word;

	start = data->pos;
	word = NULL;
	char c = data->line[data->pos];
	if (c == '\'' || c == '"')
		word = read_quote(data, c);
	else
		word = read_normal_word(data);
	return (word);
}

t_token	*new_token(t_token_type type, char *value)
{
	t_token	*token; 

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	if (value)
		token->value = strdup(value);
	else
		token->value = NULL;
	return (token);
}

void	add_token(t_token **head, t_token *new)
{
	t_token	*tmp;
	if (!*head)
		*head = new;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

t_token	*lexer(char *line)
{
	t_data	*data;
	t_token	*tokens;
	char	*word;
	t_token_type	type;
	
	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->line = line;
	data->pos = 0;
	tokens = NULL;

	while (data->line[data->pos])
	{
		while (isspace(data->line[data->pos]))
			data->pos++;
		if (!data->line[data->pos])
			break ;
		type = get_operator_type(data);
		if (type != TOKEN_NONE)
		{
			add_token(&tokens, new_token(type, NULL));
			data->pos++;
		}
		else
		{
			word = read_word(data);
			add_token(&tokens, new_token(WORD, word));
			free(word);
		}
	}
	free(data);
	return (tokens);
}

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

int	main()
{
	char *line = "echo \"hello world\" | grep hello | wc -l >> file.txt";
	char *line1 = "cat << EOF";
	char *line2 = "echo hello\"world\""; // melange texte + quotes doubles
	char *line3 = "\'hello world\'"; // quotes simples
	char *line4 = "ls -la"; // commande simple
	char *line5 = "ls | wc";
	char *line6 = "ls -l | grep .c"; // pipe avec arguments
	char *line7 = "";
	char *line8 = "echo hello>file"; // redirection sans espace
	char *line8b = "echo hello > file";
	char *line8c = "cat<<EOF";
	char *line8d = "cat << EOF"; 
	char *line9 = "grep \"main\" <file.c | wc -l >> result.txt"; // commande complexe
	char *line9a = "echo \\ word";
	char *line9b = "echo ; word";

	t_token *tokens = lexer(line9b);
	t_token *tmp = tokens;

	while (tmp)
	{
		printf("Token: %d", tmp->type);
        	if (tmp->value)
            		printf(" (%s)", tmp->value);
        	printf("\n");
        	tmp = tmp->next;
	}
	free_tokens(tokens);
	return (0);
}

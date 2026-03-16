/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 15:54:24 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/03/16 11:26:32 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Lexer :
// Initialise index i
// Skip espaces
// Identifie type
// Appelle une fonction spécialisée
// Ajoute token à la liste
// Verifie les erreurs (ENCORE A VERIFIER TOTALEMENT!!!)
// Encore quelques fuites de memoire a gerer

#include "minishell.h"

char	*read_word(t_data *data)
{
	char	buffer[1024];
	char	*tmp;
	int		buf_pos;
	int		i;

	buf_pos = 0;
	tmp = NULL;
	while (data->line[data->pos]
		&& !ft_isspace(data->line[data->pos])
		&& !ft_isoperator(data->line[data->pos]))
	{
		if (ft_isquote(data->line[data->pos]))
			tmp = read_word_between_quotes(data, data->line[data->pos]);
		else
			tmp = read_normal_word(data);
		if (!tmp)
			return (NULL);
		i = 0;
		while (tmp[i] && buf_pos < 1023)
			buffer[buf_pos++] = tmp[i++];
		free(tmp);
	}
	buffer[buf_pos] = '\0';
	return (ft_strdup(buffer));
}

int	process_token(t_data *data, t_token **tokens)
{
	t_token_type	type;
	char			*word;
	t_token			*tok;

	type = get_operator_type(data);
	if (type != WORD)
	{		
		add_token(tokens, new_token(type, NULL));
		data->pos++;
	}
	else
	{
		word = read_word(data);
		if (!word)
		{
			free_tokens(*tokens);
			return (0);
		}
		tok = new_token(WORD, word);
		if (!tok)
		{
			free(word);
			free_tokens(*tokens);
			return (0);
		}
		add_token(tokens, tok);
	}
	return (1);
}

t_token	*lexer(char *line)
{
	t_data			data;
	t_token			*tokens;

	data.line = line;
	tokens = NULL;
	data.pos = 0;
	while (data.line[data.pos])
	{
		while (ft_isspace(data.line[data.pos]))
			data.pos++;
		if (!data.line[data.pos])
			break ;
		if (!process_token(&data, &tokens))
			return (NULL);
	}
	return (tokens);
}

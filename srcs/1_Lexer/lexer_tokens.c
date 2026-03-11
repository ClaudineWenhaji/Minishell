/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 15:54:24 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/03/11 16:07:28 by clwenhaj         ###   ########.fr       */
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

	type = get_operator_type(&data);
	if (type != WORD)
	{		
		add_token(&tokens, new_token(type, NULL));
		data->pos++;
	}
	else
	{
		word = read_word(&data);
		tok = new_token(WORD, word);
		if (!tok)
		{
			free(word);
			free_tokens(tokens);
			return (0);
		}
		add_token(&tokens, tok);
		//free(word);
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

/*
int	main()
{
	char *line0 = "echo \"hello world\" | grep hello | wc -l >> file.txt";
	char *line0a = "echo \"hello world | grep hello | wc -l >> file.txt"; // quote non fermee
	char *line1 = "cat << EOF";
	char *line2 = "echo hello\"world\""; // melange texte + quotes doubles
	char *line3 = "\'hello world\'"; // quotes simples
	char *line3a = "\'hello world"; // quotes simples non fermees
	char *line4 = "ls -la"; // commande simple
	char *line5 = "ls | wc";
	char *line6 = "ls -l | grep .c"; // pipe avec arguments
	char *line7 = "";
	char *line8 = "echo hello>file"; // redirection sans espace
	char *line8b = "echo hello > file";
	char *line8c = "cat<<EOF"; // sans espaces
	char *line8d = "cat << EOF"; 
	char *line9 = "grep \"main\" <file.c | wc -l >> result.txt"; // commande complexe
	char *line9a = "echo \\ word"; // \ a ne pas traiter dans le sujet
	char *line9b = "echo ; word"; // ; a ne pas traiter aussi

	t_token *tokens = lexer(line3a);
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
}*/
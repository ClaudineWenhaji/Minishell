/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tokens2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 15:44:39 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/03/11 16:22:17 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_type	get_operator_type(t_data *data)
{
	char	c;

	c = data->line[data->pos];
	if (c == '|')
		return (PIPE);
	if (c == '>' && data->line[data->pos + 1]
		&& data->line[data->pos + 1] == '>')
	{
		data->pos++;
		return (APPEND);
	}
	if (c == '<' && data->line[data->pos + 1]
		&& data->line[data->pos + 1] == '<')
	{
		data->pos++;
		return (HEREDOC);
	}
	if (c == '<')
		return (REDIR_IN);
	if (c == '>')
		return (REDIR_OUT);
	return (WORD);
}

int	ft_isoperator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	ft_isquote(char c)
{
	return (c == '\'' || c == '"');
}

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t');
}

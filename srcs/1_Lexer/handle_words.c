/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_words.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 16:06:16 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/03/11 16:07:19 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	copy_expanded_var(t_data *data, char *buffer, int *buf_pos)
{
	char	*tmp;
	int		i;

	data->pos++;
	tmp = expand_variable(data->line, &data->pos);
	if (!tmp)
		return (0);
	i = 0;
	while (tmp[i] && *buf_pos < 1023)
		buffer[(*buf_pos)++] = tmp[i++];
	free(tmp);
	return (1);
}

char	*read_word_between_quotes(t_data *data, char quote)
{
	char	buffer[1024];
	int		buf_pos;

	buf_pos = 0;
	data->pos++;
	while (data->line[data->pos]
		&& data->line[data->pos] != quote && buf_pos < 1023)
	{
		if (quote == '"' && data->line[data->pos] == '$')
		{
			if (!copy_expanded_var(data, buffer, &buf_pos))
				return (NULL);
		}
		else
			buffer[buf_pos++] = data->line[data->pos++];
	}
	if (data->line[data->pos] == quote)
		data->pos++;
	else
	{
		printf("syntax error: unclosed quote %c\n", quote);
		return (NULL);
	}
	buffer[buf_pos] = '\0';
	return (ft_strdup(buffer));
}

char	*read_normal_word(t_data *data)
{
	char	buffer[1024];
	int		buf_pos;

	buf_pos = 0;
	while (data->line[data->pos]
		&& !ft_isspace(data->line[data->pos])
		&& !ft_isquote(data->line[data->pos])
		&& !ft_isoperator(data->line[data->pos]))
	{
		if (data->line[data->pos] == '$')
		{
			if (!copy_expanded_var(data, buffer, &buf_pos))
				return (NULL);
		}
		else
			buffer[buf_pos++] = data->line[data->pos++];
	}
	buffer[buf_pos] = '\0';
	return (ft_strdup(buffer));
}

/*
char	*read_normal_word(t_data *data)
{
	char	buffer[1024];
	int		buf_pos;

	buf_pos = 0;
	while (data->line[data->pos])
	{
		if (data->line[data->pos] == '\\')
		{
			data->pos++;
			if (data->line[data->pos])
				buffer[buf_pos++] = data->line[data->pos++];
		}
		else if (ft_isspace(data->line[data->pos])
			|| ft_isquote(data->line[data->pos])
			|| ft_isoperator(data->line[data->pos]))
			break ;
		else if (data->line[data->pos] == '$')
		{
			if (!copy_expanded_var(data, buffer, &buf_pos))
				return (NULL);
		}
		else
			buffer[buf_pos++] = data->line[data->pos++];
	}
	buffer[buf_pos] = '\0';
	return (ft_strdup(buffer));
}*/
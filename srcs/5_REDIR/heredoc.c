/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 13:59:45 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/04/03 12:33:23 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*int	handle_heredoc(const char *delimiter, t_env_var *env, int expand)
{
	int		pipefd[2];
	char	*line;
	pid_t	pid;
	//char	*expanded;
	//char	*output;
	int	expand;
	int		status;

	expand = !is_single_quoted(delimiter);
	if (pipe(pipefd) == -1)
		return (perror("pipe"), -1);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), -1);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN);
		close(pipefd[0]);
		while (1)
		{
			line = readline("> ");
			if (!line)
				(printf("warning: heredoc ended by EOF\n"), close(pipefd[1]),
						exit(0));
			if (ft_strcmp(line, delimiter) == 0)
				(free(line), close(pipefd[1]), exit(0));
			output = line;
			if (expand)
			{
				expanded = expand_line(line, env);
				if (expanded)
					output = expanded;
			}
			write(pipefd[1], output, ft_strlen(output));
			write(pipefd[1], "\n", 1);
			if (expand && output != line)
				free(output);
			free(line);	
		}
	}
	else
	{
		(close(pipefd[1]), waitpid(pid, &status, 0));
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
			return (close(pipefd[0]), g_status = 130, -1);
		return (pipefd[0]);
	}
}*/

static int	is_heredoc_expand(const char *delimiter)
{
	if (ft_strlen(delimiter) >= 2 && delimiter[0] == '\''
		&& delimiter[ft_strlen(delimiter) - 1] == '\'')
		return (0);
	return (1);
}

static char	*prepare_delim(const char *delimiter, int expand)
{
	if (!expand)
		return (strip_quotes((char *)delimiter));
	return ((char *)delimiter);
}

int	handle_heredoc(const char *delimiter, t_env_var *envs)
{
	int		pipefd[2];
	pid_t	pid;
	int		status;
	int		expand;
	char	*line;
	char	*output;
	char	*delim;

	expand = is_heredoc_expand(delimiter);
	if (pipe(pipefd) == -1)
		return (perror("pipe"), -1);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), -1);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN);
		close(pipefd[0]);
		while (1)
		{
			line = readline("> ");
			if (!line)

				exit(0);
			delim = prepare_delim(delimiter, expand);
			if (ft_strcmp(line, delim) == 0)
				(free(line), free(delim), close(pipefd[1]), exit(0));
			free(delim);
			output = line;
			if (expand)
				output = expand_variable(line, envs, expand);
			write(pipefd[1], output, ft_strlen(output));
			write(pipefd[1], "\n", 1);
			if (expand && output != line)
				free(output);
			free(line);
		}
	}
	close(pipefd[1]);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		return (close(pipefd[0]), g_status = 130, -1);
	return (pipefd[0]);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 13:59:45 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/03/20 16:11:12 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_heredoc(const char *delimiter)
{
	int	pipefd[2];
	char	*line;
	pid_t	pid;
	int		status;

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	pid = fork();	
	if (pid == 0)
	{
		close(pipefd[0]);
		while (1)
		{
			line = readline("> ");
			if (!line || ft_strcmp(line, delimiter) == 0)
			{
				if (!line)
					printf("warning: heredoc ended by EOF\n");
				free(line);
				break ;
			}
			write(pipefd[1], line, ft_strlen(line));
			write(pipefd[1], "\n", 1);
			free(line);
		}
		close(pipefd[1]);
		exit(0);
	}
	close(pipefd[1]);
	waitpid(pid, &status, 0);
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(pipefd[0]);
		return (-1);
	}
	close(pipefd[0]);
	return (0);
}

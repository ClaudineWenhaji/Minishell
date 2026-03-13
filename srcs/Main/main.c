/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 13:20:54 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/03/13 14:49:13 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status = 0;

int	main(int argc, char **argv, char **envp)
{
	char			*line;
	t_token			*tokens;
	t_command_ast	*cmds;

	(void)argc;
	(void)argv;
	(void)envp;
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		if (*line)
			add_history(line);
		tokens = lexer(line);
		print_tokens(tokens);
		cmds = parser(tokens);
		print_commands(cmds);
		ft_free_command(&cmds);
		free_tokens(tokens);

		free(line);
	}
	rl_clear_history();
//	clear_history();
	return (g_status);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 13:19:42 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/03/17 15:53:20 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;

	if (argc != 2)
        	return (0);
	if (ft_strcmp(argv[1], "export") == 0)
        builtin_export(NULL, envp);
	else if (ft_strcmp(argv[1], "cd") == 0)
        builtin_cd(NULL, envp);
	else if (ft_strcmp(argv[1], "pwd") == 0)
		builtin_pwd();
	else if (ft_strcmp(argv[1], "echo") == 0)
		builtin_echo(NULL);
    else if (ft_strcmp(argv[1], "unset") == 0)
        return (0);
    return (0);
}

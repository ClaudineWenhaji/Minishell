/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 11:35:09 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/03/18 16:10:08 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

staic int	error_cd(void)
{
	perror("cd");
	return (1);
}

int	ft_cd(char **args, char **envp)
{
	char	*pwd;

	(void)envp;
	if (!args[1])
	{
		printf("cd: missing arguments\n");
		return (1);
	}
	if (args[2])
	{
		printf("cd: too many argunments\n");
		return (1);
	}
	if (chdir(args[1]) != 0)
		return (error_cd());
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (error_cd());
	free(pwd);
	return (0);
}

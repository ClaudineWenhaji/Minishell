/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 19:01:17 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/03/16 11:12:02 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// char *getcwd(char *buf, size_t size) 
// getcwd(cwd, PATH_MAX) PATH_MAX souvent limite a 4096
// getcwd(NULL, 0) alloue dynamiquement la memoire pour le chemin
#include "minishell.h"

int	builtin_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		perror ("pwd");
	else
	{
		printf("%s\n", cwd);
		free(cwd);
	}
	return (0);
}

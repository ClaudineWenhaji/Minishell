/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 11:35:09 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/03/17 15:53:05 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int builtin_cd(char **args, char **envp)
{
    char    *pwd;
    
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
    {
        perror("cd");
        return (1);
    }
    pwd = getcwd(NULL, 0);
    if (!pwd)
    {
        perror("cd");
        return (1);
    }
    free(pwd);
    return (0);
}

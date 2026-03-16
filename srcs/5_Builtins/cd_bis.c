/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_bis.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 11:35:09 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/03/16 12:31:36 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int builtin_cd(char **args)
{
    char    *oldpwd;
    char    *pwd;
    
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
    oldpwd = getcwd(NULL, 0);
    if (!oldpwd)
        return (1);
    if (chdir(args[1]) != 0)
    {
        perror("cd");
        free(oldpwd);
        return (1);
    }
    pwd = getcwd(NULL, 0);
    if (!pwd)
    {
        free (oldpwd);
        return (1);
    }
    setenv("OLDPWD", oldpwd, 1);
    setenv("PWD", pwd, 1);
    free(oldpwd);
    free(pwd);
    return (0);
}
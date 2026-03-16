/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 12:19:10 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/03/16 17:11:05 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// int chdir(const char *path
// chdir()  changes the current working directory of the calling 
// process to the directory specified in path
// On success, 0 is returned.  
// On error, -1 is returned, 
// and errno is set appropriately

#include "minishell.h"

int builtin_cd(char **args)
{
    if (!args[1])
    {
        printf("cd: missing arguments\n");
        return (1);
    }
    if (args[2])
    {
        printf("cd: too many arguments\n");
        return (1);
    }
    if (chdir(args[1]) != 0)
    {
        perror("cd");
        return (1);
    }
    return (0);
}
/*

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
    char cwd[1024];
    char *args1[] = {"cd", "/tmp", NULL};
    
    getcwd(cwd, sizeof(cwd));
    printf("Current Dir: %s\n", cwd);
    
    builtin_cd(args1);
    getcwd(cwd, sizeof(cwd));
    printf("Dir after cd /tmp: %s\n", cwd);
    
    return (0);
}*/
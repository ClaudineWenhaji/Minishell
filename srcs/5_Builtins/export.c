/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 12:57:08 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/03/18 12:19:03 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_var(char **envp, char *var)
{
	int	len;
	int	i;

	len = ft_strlen(var);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var, len) == 0
			&& envp[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

int	export_var(char *arg, char **envp)
{
	char	*equal;
	char	*name;
	int	name_len;
	char	**new_env;
	int	index;
	int	size;
	int	i;

	equal = ft_strchr(arg, '=');
	if (!equal)
		return (printf("export: invalid format\n"), 1);

	name_len = equal - arg;
	name = malloc(name_len + 1);
	if (!name)
		return (1);

	ft_strncpy(name, arg, name_len);
	name[name_len] =  '\0';

	index = find_var(envp, name);
	if (index != -1)
	{
		free(*envp[index]);
		(*envp)[index] = ft_strdup(arg);
	}
	else
	{
		size = 0;
		while ((*envp)[size])
			size++;
		new_env = malloc(sizeof(char *) * (size + 2));
		if (!new_env)
			return (perror("export"), 1);
		i = 0;
		while (i < size)
		{
			new_env[i] = (*envp)[i];
			i++;
		}
		new_env[size] = ft_strdup(arg);
		new_env[size + 1] = NULL;
		free(*envp);
		*envp = new_env;
	}
	return (0);
}

int	builtin_export(char **args, char **envp)
{
	int i;

	i = 1;
	if (!args)
		return (0);
	while (args[i])
	{
		if (export_var(arg[i], envp) != 0)
			return (1);
		i+++;
	}
	return (0);
}

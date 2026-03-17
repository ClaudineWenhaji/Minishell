/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 14:14:37 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/03/17 15:14:11 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    **copy_env(char **envp)
{
    char    **env;
    int     i;

    i = 0;
    while (envp[i])
        i++;
    env = malloc(sizeof(char *) * (i + 1));
	if (!env)
		return (NULL);

	i = 0;
	while (envp[i])
	{
		env[i] = ft_strdup(envp[i]);
		i++;
	}
	env[i] = NULL;

	return (env);
}

void    update_env(t_env *env, char *key, char *value)
{
    t_env *tmp;

    tmp = env;
    while (tmp)
    {
        if (ft_strcmp(tmp->key, key) == 0)
        {
            free(tmp->value);
            tmp->value = ft_strdup(value);
            return ;
        }
        tmp = tmp->next;
    }
}

char	*get_env_value(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

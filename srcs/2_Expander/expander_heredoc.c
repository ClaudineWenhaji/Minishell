#include "minishell.h"

char *expand_line(char *line, t_env_var *env)
{
    char buffer[4096];
    int i = 0;
    int j = 0;
    char *tmp;
    int start;

    while (line[i])
    {
        if (line[i] == '$')
        {
            start = i;
            i++;
            tmp = expand_variable(line, &i, env);
            if (!tmp)
                return (NULL);
            if (i == start + 1)
                buffer[j++] = '$';
            else
                j += ft_strlcpy(buffer + j, tmp, 4096 - j);
            free(tmp);
        }
        else
            buffer[j++] = line[i++];
    }
    buffer[j] = '\0';
    return (ft_strdup(buffer));
}

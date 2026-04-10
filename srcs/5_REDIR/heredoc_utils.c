#include "minishell.h"

int	is_quoted(char *str)
{
	int	len;

    if (!str)
        return (0);
    len = ft_strlen(str);
    if (len >= 2 && (
        (str[0] == '\'' && str[len - 1] == '\'') ||
        (str[0] == '"' && str[len - 1] == '"')))
        return (1);
    return (0);
}

char *remove_quotes(char *str)
{
    int len;

    if (!str)
        return (NULL);
    len = ft_strlen(str);
    if (is_quoted(str))
        return (ft_substr(str, 1, len - 2));
    return (ft_strdup(str));
}

int is_single_quoted(char *str)
{
    size_t len;
   
    if (!str || str[0] != '\'')
        return 0; // pas de quote simple au début
    len = 0;
    len = ft_strlen(str);
    if (len >= 2 && str[len - 1] == '\'')
	    return (1);
    return (0);
}

char *strip_quotes(const char *str)
{
    size_t len;
    char *new;

    if (!str)
        return NULL;
    len = ft_strlen(str);
    if ((str[0] == '\'' && str[len - 1] == '\'') ||
        (str[0] == '"'  && str[len - 1] == '"'))
    {
        new = malloc(len - 1);
        if (!new)
            return NULL;
        strncpy(new, str + 1, len - 2);
        new[len - 2] = '\0';
        return (new);
    }
    return (strdup(str));
}

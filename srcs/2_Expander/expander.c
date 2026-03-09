#include "minishell.h"

char    *expand_variable(const char *str, int *pos)
{
	char	key[256];
	int	k;
	char	*val;
	char	*value;

	if (str[*pos] == '?')
	{
		(*pos)++;
		val = ft_itoa(g_status);
		return (val);
	}
	k = 0;
	while (ft_isalnum(str[*pos]) || str[*pos] == '_')
	{
		if (k < 255)
			key[k++] = str[*pos];
		(*pos)++;
	}
	key[k] = '\0';
	value = getenv(key);
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
}

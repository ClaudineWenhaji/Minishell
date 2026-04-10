#include "minishell.h"

int ft_addredir_heredoc(t_redir_file **head, char *file, int expand)
{
    t_redir_file *node;
    t_redir_file *tmp;

    node = malloc(sizeof(t_redir_file));
    if (!node)
        return (0);
    node->type = HEREDOC;
    node->file = ft_strdup(file);
    node->expand = expand;
    node->next = NULL;

    if (!*head)
        *head = node;
    else
    {
        tmp = *head;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = node;
    }
    return (1);
}

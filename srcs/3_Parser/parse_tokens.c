/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 13:40:26 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/03/11 11:13:30 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    **add_arg(char **args, char *value)
{
    int i;
    int len;
    
    len = 0;
    while (args && args[len])
        len ++;

    char **new_args = malloc(sizeof(char *) * (len + 2));
    if (!new_args)
        return (NULL);

    i = 0;
    while (i < len)
    {
        new_args[i] = args[i];
        i++;
    }
    new_args[len] = ft_strdup(value);
    new_args[len + 1] = NULL;
    free(args);
    return (new_args);
}

t_cmd *parse_tokens(t_token *tokens)
{
    t_cmd   *cmd_list = NULL;
    t_cmd   *current = NULL;

    while (tokens)
    {
        t_cmd *cmd = malloc(sizeof(t_cmd));
        if (!cmd)
            return (NULL);
        cmd->args = NULL;
        cmd->input_file = NULL;
        cmd->output_file = NULL;
        cmd->append = 0;
        cmd->next = NULL;
        while (tokens && tokens->type != PIPE)
        {
            if (tokens->type == WORD)
                cmd->args = add_arg(cmd->args, tokens->value);
            else if (tokens->type == REDIR_IN || tokens->type == HEREDOC)
            {
                tokens = tokens->next;
                if (tokens && tokens->type == WORD)
                    cmd->input_file = ft_strdup(tokens->value);
            }
            else if (tokens->type == REDIR_OUT || tokens->type == APPEND)
            {
                cmd->append = (tokens->type == APPEND);
                tokens = tokens->next;
                if (tokens && tokens->type == WORD)
                    cmd->output_file = ft_strdup(tokens->value);
            }
            tokens = tokens->next;
        }
        if (!cmd_list)
            cmd_list = cmd;
        else
            current->next = cmd;
        current = cmd;
        if (tokens && tokens->type == PIPE)
            tokens = tokens->next;
    }
    return (cmd_list);
}

void print_args(char **args)
{
    int i = 0;
    if (!args)
    {
        printf("  args: NULL\n");
        return;
    }

    printf("  args: ");
    while (args[i])
    {
        printf("\"%s\" ", args[i]);
        i++;
    }
    printf("\n");
}

void print_command(t_cmd *cmd, int index)
{
    printf("Command %d:\n", index);
    print_args(cmd->args);

    if (cmd->input_file)
        printf("  input: %s\n", cmd->input_file);
    else
        printf("  input: NULL\n");

    if (cmd->output_file)
        printf("  output: %s (%s)\n", cmd->output_file, cmd->append ? "append" : "overwrite");
    else
        printf("  output: NULL\n");

    printf("  next: %s\n", cmd->next ? "yes" : "no");
    printf("\n");
}

void print_commands(t_cmd *cmd_list)
{
    int index = 1;
    t_cmd *current = cmd_list;

    while (current)
    {
        print_command(current, index);
        current = current->next;
        index++;
    }
}

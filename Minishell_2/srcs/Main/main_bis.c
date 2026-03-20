/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 02:03:34 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/03/20 16:07:24 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status = 0;

void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
		g_status = 0;
}

static int	check_builtin_and_do(t_command_ast *cmds, t_env_var **env,
		t_minishell_data **data)
{
	int ret;
	char *arg;
	int stdin_copy;
	int stdout_copy;
	

	//if (!cmds || !cmds->command)
	//	return (0);
	ret = 0;
	stdin_copy = dup(STDIN_FILENO);
	stdout_copy = dup(STDOUT_FILENO);
	if (cmds->redirs)
	{
		if (!apply_redirections(cmds->redirs, 1))
		{
			dup2(stdin_copy, STDIN_FILENO);
			dup2(stdout_copy, STDOUT_FILENO);
			close(stdin_copy);
			close(stdout_copy);
			return (0);
		}
	}
	if (ft_strcmp(cmds->command, "echo") == 0)
	{
		ft_echo(cmds->args);
		ret = 1;
	}
	else if (ft_strcmp(cmds->command, "pwd") == 0)
	{
		ft_pwd();
		ret = 1;
	}
	else if (ft_strcmp(cmds->command, "env") == 0 && !cmds->args)
	{
		ft_env(*env);
		ret = 1;
	}
	else if (ft_strcmp(cmds->command, "cd") == 0)
	{
		arg = NULL;
		if (cmds->args)
			arg = (char *)cmds->args->content;
		ft_cd(arg, *env);
		ret = 1;
	}
	else if (ft_strcmp(cmds->command, "export") == 0)
	{
		if (!cmds->args)
			ft_export(NULL, env, NULL);
		else
			ft_export((char *)cmds->args->content,
						env, &(*data)->execdirs);
		ret = 1;
	}
	else if (ft_strcmp(cmds->command, "unset") == 0 && cmds->args->content)
	{
		ft_unset(env, (char *)cmds->args->content);
		ret = 1;
	}
	else if (ft_strcmp(cmds->command, "exit") == 0)
	{
		ft_exit(data);
		ret = 1;
	}
	dup2(stdin_copy, STDIN_FILENO);
	dup2(stdout_copy, STDOUT_FILENO);
	close(stdin_copy);
	close(stdout_copy);
	return (ret);
}

static void	do_commands(t_minishell_data **data)
{
	t_command_ast	*node;

	node = (*data)->cmds;
	while (node)
	{
		if (!check_builtin_and_do(node, &(*data)->envs, data))
			run_command(node, data);
		node = node->next;
	}
}

static void	lp_read_loop(t_minishell_data **data)
{
	char	*line;

	while (1)
	{
		line = readline("minishell> ");
		if (!line)
			exit(EXIT_SUCCESS);
		add_history(line);
		(*data)->tokens = lexer(line);
		(*data)->cmds = parser((*data)->tokens);
		do_commands(data);
		ft_free_command(&(*data)->cmds);
		free_tokens((*data)->tokens);
		free(line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell_data	*data;
	int					i;

	(void)argc;
	(void)argv;
	if (signal(SIGINT, handle_signal) != 0
		|| signal(SIGQUIT, handle_signal) != 0)
		return (printf("error: fail to catch a signal.\n"), 1);
	i = -1;
	data = (t_minishell_data *)malloc(sizeof(t_minishell_data));
	if (!data)
		return (1);
	data->envs = NULL;
	data->execdirs = NULL;
	while (envp[++i])
		ft_export(envp[i], &data->envs, &data->execdirs);
	lp_read_loop(&data);
	ft_free_envs(&data->envs);
	free(data);
	rl_clear_history();
	return (g_status);
}

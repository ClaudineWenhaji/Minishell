#include "minishell.h"

int g_status = 0;

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

int	execute_builtin(t_command_ast *cmds, char **envp)
{
	if (ft_strcmp(cmds->command, "export") == 0)
		return (builtin_export(cmds->args, envp));
	else if (ft_strcmp(cmds->command, "cd") == 0)
		return (builtin_cd(cmds->args, envp));
	else if (ft_strcmp(cmds->command, "echo") == 0)
		return (builtin_echo(cmds->args));
	else if (ft_strcmp(cmds->command, "pwd") == 0)
		return (builtin_pwd());
	return (-1);
}

void	do_commands(t_command_ast *cmds, char **envp)
{
	t_command_ast *node;

	node = cmds;
	while (node)
	{
		execute_builtin(node, envp);
		node = node->next;
	}
}

int	execute_command(t_command_ast *cmd, t_env **env)
{
	int ret;

	ret = execute_builtin(cmd, env);
	if (ret != -1)
		return (ret);
	return (execute_external_command(cmd, env));
}
static void	lp_read_loop(char *line, char **envp)
{
	t_token			*tokens;
	t_command_ast	*cmds;

	(void)envp;
	if (!line)
		exit(EXIT_SUCCESS);
	add_history(line);
	tokens = lexer(line);
	//print_tokens(tokens);
	cmds = parser(tokens);
	print_commands(cmds);
	//do_commands(cmds, envp);
	execute_command(cmds, envp);
	ft_free_command(&cmds);
	free_tokens(tokens);
}

int main(int argc, char **argv, char **envp)
{
	char	*line;

	(void)argc;
	(void)argv;
	(void)envp;

	if (signal(SIGINT, handle_signal) != 0
		|| signal(SIGQUIT, handle_signal) != 0)
		return (printf("error: fail to catch a signal.\n"), 1);
	line = NULL;
	while (1)
	{
		line = readline("minishell> ");
		lp_read_loop(line, envp);
		free(line);
	}
	rl_clear_history();
//	clear_history();
	return (g_status);
}

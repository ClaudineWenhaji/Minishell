#include <stdio.h>
#include <stdlib.h>
#include "minishell.h" // ton header avec lexer, t_token, etc.

void	print_tokens(t_token *tokens)
{
	t_token *tmp = tokens;
	while (tmp)
	{
		if (tmp->type == WORD)
			printf("WORD     | %s\n", tmp->value);
		else if (tmp->type == PIPE)
			printf("PIPE     | |\n");
		else if (tmp->type == REDIR_IN)
			printf("REDIR_IN | <\n");
		else if (tmp->type == REDIR_OUT)
			printf("REDIR_OUT| >\n");
		else if (tmp->type == APPEND)
			printf("APPEND   | >>\n");
		else if (tmp->type == HEREDOC)
			printf("HEREDOC  | <<\n");
		tmp = tmp->next;
	}
}

void	test_lexer(const char *input)
{
	printf("\nCOMMAND: %s\n", input);
	t_token *tokens = lexer((char *)input);
	if (!tokens)
	{
		printf("Lexer returned NULL (probably unclosed quote)\n");
		return;
	}
	print_tokens(tokens);
	free_tokens(tokens);
}

int	main(void)
{
	// 1️⃣ Commandes simples
	test_lexer("echo hello");
	test_lexer("ls -l");

	// 2️⃣ Quotes simples
	test_lexer("echo \"hello world\"");
	test_lexer("echo 'hello world'");
	test_lexer("echo \"hello\"");
	test_lexer("echo ''");

	// 3️⃣ Mots mixtes
	test_lexer("echo hello\"world\"");
	test_lexer("echo \"hello\"world");
	test_lexer("echo \"hello\"\"world\"");
	test_lexer("echo 'hello'\"world\"");
	test_lexer("echo 'a'b\"c\"");

	// 4️⃣ Pipes
	test_lexer("ls | wc");
	test_lexer("echo a | grep a | wc -l");

	// 5️⃣ Redirections
	test_lexer("cat < file.txt");
	test_lexer("echo hello > out.txt");
	test_lexer("echo hello >> out.txt");
	test_lexer("cat << EOF");

	// 6️⃣ Combinaisons
	test_lexer("grep \"main\" < file.c | wc -l >> result.txt");
	test_lexer("echo \"hello\"world | cat > out.txt");

	// 7️⃣ Cas invalides / edge
	test_lexer("echo \"hello"); // unclosed quote
	test_lexer("echo      hello"); // espaces multiples
	test_lexer("echo>out.txt"); // redirection collée aux mots
	test_lexer("echo a\"b\"'c'd"); // mots mixtes + quotes multiples

	return 0;
}

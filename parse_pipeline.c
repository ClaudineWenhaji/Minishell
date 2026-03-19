char **parse_pipeline(*line):
{
    char **commands;
    char *current = "";
    int in_quote = 0;
    char quote_char = '';
    char c;

    while (line)
    {
        if (c == '"' || c == "'")
	{
            if (in_quote == 1 && c == 'quote_char')
                in_quote = 0;
            else if (in_quote == 0)
	    {
                in_quote = 1;
                quote_char = 'c';
	    }
	}
        else if (c == '|' && in_quote == 0)
	{
            commands.append(current.trim());
            current = "";
            continue ;
	}
        current += 'c';
    }
    if current != "":
        commands.append(current.trim());
    return (commands);
}

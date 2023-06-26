#include "shell.h"

/**
 * remove_comments - function that handles comments
 * @cmd: it's a pointer
 */
void remove_comments(cmdlist_t *cmd)
{
	char **tokens = cmd->tokens;
	char **print;
	char *temp;

	while (*tokens)
	{
		if (**tokens == '#')
		{
			temp = *tokens;
			*tokens = NULL;
			print = arrdup(cmd->tokens);
			*tokens = temp;
			free_tokens(&(cmd->tokens));
			cmd->tokens = print;
			free_cmdlist(&(cmd->next));
			return;
		}
		tokens++;
	}
}

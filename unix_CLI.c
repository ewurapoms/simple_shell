#include "command.h"

/**
 * add_cmd_end - function adds command to list end
 * @headptr: is a pointer
 * @cmd: is the command to add
 *
 * Return: output or NULL
 */
cmdlist_t *add_cmd_end(cmdlist_t **headptr, const char *cmd)
{
	cmdlist_t *print;

	if (!headptr)
		return (NULL);
	if (*headptr)
		return (add_cmd_end(&((*headptr)->next), cmd));

	print = malloc(sizeof(cmdlist_t));
	if (!print)
		return (NULL);

	print->next = NULL;
	print->tree = NULL;

	print->tokens = tokenize(cmd);
	if (!print->tokens)
	{
		free(print);
		return (NULL);
	}
	*headptr = print;

	return (print);
}


/**
 * del_cmd - function deletes a command from the list
 * @headptr: is a pointer
 * @index: input value
 * Return: ...
 */
cmdlist_t *del_cmd(cmdlist_t **headptr, size_t index)
{
	cmdlist_t *edit;

	if (!(headptr && *headptr))
		return (NULL);
	if (index)
		return (del_cmd(&((*headptr)->next), index - 1));

	edit = *headptr;
	*headptr = (*headptr)->next;
	free_cmdtree(&(edit->tree));
	free_tokens(&(edit->tokens));
	free(edit);

	return (edit);
}

/**
 * pop_cmd - function deletes nodes and prints their tokens
 * @headptr: is a pointer
 * Return: printed tokens
 */
char **pop_cmd(cmdlist_t **headptr)
{
	cmdlist_t *del;
	char **tokens;

	if (!(headptr && *headptr))
		return (NULL);

	del = *headptr;
	tokens = del->tokens;
	*headptr = (*headptr)->next;

	free_cmdtree(&(del->tree));
	free(del);

	return (tokens);
}

/**
 * free_cmdlist - function frees a linked list, sets head to NULL
 * @headptr: is a double ptr to initial node
 */
void free_cmdlist(cmdlist_t **headptr)
{
	if (headptr && *headptr)
	{
		free_cmdlist(&((*headptr)->next));
		free_cmdtree(&((*headptr)->tree));
		free_tokens(&((*headptr)->tokens));
		free(*headptr);
		*headptr = NULL;
	}
}


/**
 * split_cmd - function that splits a command
 * @cmd: is a pointer
 *
 * Return: final output
 */
size_t split_cmd(char *cmd)
{
	size_t sum = 1;
	size_t len;
	ssize_t i;
	quote_state_t state;/* calls quote type */

	do {
		while (*cmd && (state = quote_state(*cmd)) != QUOTE_NONE)
		{
			if (state & QUOTE_WORD)
			{
				len = _quote_state_word(cmd, NULL);
				i = _strnchr(cmd, ';', len);
				if (i != -1)
				{
					len = i;
					*(++cmd + len) = '\0';
					sum++;
				}
				cmd += len;
			}
			else if (state & QUOTE_ESCAPE)
			{
				if (*(cmd + 1) == '\n')
					_strcpy(cmd, cmd + 2);
				else if (*(++cmd))
					cmd++;
			}
			else
			{
				cmd += quote_state_len(cmd + 1, state) + 1;
				if (*cmd && (state & (QUOTE_SINGLE | QUOTE_DOUBLE)))
					++cmd;
			}
		}
	} while (*(cmd += quote_state_len(cmd, QUOTE_NONE)));

	return (sum);
}

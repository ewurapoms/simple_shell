#include "command.h"

/**
 * cmd_to_list - function that parses the command
 * @cmd: is the command pointer
 * Return: NULL
 */
cmdlist_t *cmd_to_list(const char *cmd)
{
	cmdlist_t *top = NULL;
	size_t sum;
	char *split = _strdup(cmd);

	if (!split)
		return (NULL);

	sum = split_cmd(split);
	if (!_cmd_to_list(&top, split, sum))
	{
		free_cmdlist(&top);
		return (NULL);
	}
	free(split);
	return (top);
}

/**
 * _cmd_to_list - function prints a linked list of tokenized cmd
 * @tailptr: is a ptr to the end of cmdlist
 * @split: separates list
 * @count: sum of the split
 *
 * Return: 0 or NULL
 */

cmdlist_t *_cmd_to_list(cmdlist_t **tailptr, char *split, size_t count)
{
	cmdlist_t *end;

	if (!count)
		return (*tailptr);

	end = add_cmd_end(tailptr, split);
	if (!end)
		return (NULL);
	while (*split++)
		;
	return (_cmd_to_list(&end, split, count - 1));
}


/**
 * cmd_to_tree - prints a commands binary tree
 * @tokens: command to print
 *
 * Return: output or NULL
 */
cmdtree_t *cmd_to_tree(const char * const *tokens __attribute__((unused)))
{
	return (NULL);
}

/**
 * free_cmdtree - function frees the binary tree
 * @rootptr: is a double pointer
 * Return: NULL
 */
void free_cmdtree(cmdtree_t **rootptr)
{
	if (rootptr && *rootptr)
	{
		free_cmdtree(&((*rootptr)->success));
		free_cmdtree(&((*rootptr)->failure));
		(*rootptr)->tokens = NULL;
		(*rootptr) = NULL;
	}
}

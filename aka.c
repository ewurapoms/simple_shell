#include "builtins.h"

/**
 * __alias_add - function adds an alias cmd
 * @aliases: is a pointer
 * @name: alias name
 * @value: alias val
 */
void __alias_add(alias_t **aliases, const char *name, const char *value)
{
	alias_t *alias = get_dict_node(aliases ? *aliases : NULL, name);

	if (alias)
	{
		free(alias->val);
		alias->val = _strdup(value);
	}
	else
	{
		add_dict_node_end(aliases, name, value);
	}
}


/**
 * __alias_print - function creates an alias
 * @alias: input value
 */
void __alias_print(alias_t *alias)
{
	write(STDOUT_FILENO, alias->key, _strlen(alias->key));
	write(STDOUT_FILENO, "='", 2);
	write(STDOUT_FILENO, alias->val, _strlen(alias->val));
	write(STDOUT_FILENO, "'\n", 2);
}


/**
 * __alias - function forms and print the alias builtins
 * @info: is the shell directory
 *
 * Return: status
 */
int __alias(info_t *info)
{
	alias_t *alias;
	char *name;
	char **args = info->tokens + 1;
	ssize_t length;

	info->status = EXIT_SUCCESS;
	if (*args)
	{
		do {
			length = _strchr(*args, '=');
			if (length == -1)
			{
				alias = get_dict_node(info->aliases, *args);
				if (alias)
				{
					__alias_print(alias);
				}
				else
				{
					perrorl("not found", *info->tokens, *args, NULL);
					info->status = EXIT_FAILURE;
				}
			}
			else
			{
				name = _strndup(*args, length);
				__alias_add(&info->aliases, name, *args + length + 1);
				free(name);
			}
		} while (*++args);
	}
	else
	{
		for (alias = info->aliases; alias; alias = alias->next)
			__alias_print(alias);
	}
	return (info->status);
}

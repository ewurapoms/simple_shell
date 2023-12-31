#include "builtins.h"

/**
 * get_builtins - function prints builtins
 * Return: pointer to 'n\0' array of builtins
 */
const builtin_t *get_builtins(void)
{
	static builtin_t builtins[] = {
		{"alias", __alias, ALIAS_HELP, ALIAS_DESC},
		{"cd", __cd, CD_HELP, CD_DESC},
		{"env", __env, ENV_HELP, ENV_DESC},
		{"exec", __exec, EXEC_HELP, EXEC_DESC},
		{"exit", __exit, EXIT_HELP, EXIT_DESC},
		{"help", __help, HELP_HELP, HELP_DESC},
		{"setenv", __setenv, SETENV_HELP, SETENV_DESC},
		{"unsetenv", __unsetenv, UNSETENV_HELP, UNSETENV_DESC},
		{0}
	};

	return (builtins);
}

/**
 * get_builtin - function retrieves builtin by name
 * @name: the name of the builtin to retrieve
 * Return: NULL if name is absent, else a pointer to the builtin
 */
const builtin_t *get_builtin(const char *name)
{
	const builtin_t *b = NULL;

	for (b = get_builtins(); b->name; b += 1)
	{
		if (_strcmp(name, b->name) == 0)
			return (b);
	}
	return (NULL);
}

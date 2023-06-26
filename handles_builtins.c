#include "builtins.h"

/**
 * __setenv - sets the environment variables
 * @info: arguments passed
 *
 * Return: status
 */
int __setenv(info_t *info)
{
	env_t *ven;
	char *val;
	char **built = info->tokens + 1;

	if (built[0])
	{
		if (built[1])
		{
			if (built[2])
			{
				perrorl("Too many arguments.", *info->tokens, NULL);
				info->status = EXIT_FAILURE;
				return (info->status);
			}
			val = built[1];
		}
		else
		{
			val = "";
		}
		ven = get_dict_node(info->env, built[0]);
		if (ven)
		{
			free(ven->val);
			ven->val = _strdup(val);
		}
		else
		{
			add_dict_node_end(&info->env, built[0], val);
		}
		info->status = EXIT_SUCCESS;
	}
	else
	{
		__env(info);
	}
	return (info->status);
}


/**
  * __unsetenv - function that unsets the env var
  * @info: ...
  * Return: ...
  */
int __unsetenv(info_t *info)
{
	char **undo = info->tokens + 1;

	if (*undo)
	{
		while (*undo)
			del_dict_node(&info->env, *undo++);
		info->status = EXIT_SUCCESS;
	}
	else
	{
		perrorl("Too few arguments.", *info->tokens, NULL);
		info->status = EXIT_FAILURE;
	}
	return (info->status);
}


/**
 * __cd_error - function prints errors where cd commands fails
 * @info: is the shell info
 * @dir: is the directory
 */
void __cd_error(info_t *info, char *dir)
{
	char *fail = strjoin(NULL, " ", "can't cd to", dir);

	perrorl_default(*info->argv, info->lineno, fail, *info->tokens, NULL);

	info->status = 2;

	free(fail);
}


/**
 * __cd_success - function prints an update to the env for cd success
 * @info: is the shell info
 */
void __cd_success(info_t *info)
{
	char **tok = info->tokens;
	char *env_toks[] = {"setenv", NULL, NULL, NULL};

	info->tokens = env_toks;

	env_toks[1] = "OLDPWD";
	env_toks[2] = info->cwd;

	__setenv(info);

	free(info->cwd);
	info->cwd = getcwd(NULL, 0);

	env_toks[1] = "PWD";
	env_toks[2] = info->cwd;

	__setenv(info);

	info->tokens = tok;

	info->status = EXIT_SUCCESS;
}


/**
 * __cd - function that prints the change directory cmd
 * @info: input value
 * Return: an int
 */
int __cd(info_t *info)
{
	char *directs = NULL;
	char **args = info->tokens + 1;

	info->status = EXIT_SUCCESS;
	if (*args)
	{
		if (!_strcmp(*args, "-"))
		{
			directs = get_dict_val(info->env, "OLDPWD");
			if (!directs)
				directs = info->cwd;

			info->status = chdir(directs);
			if (!info->status)
			{
				write(STDOUT_FILENO, directs, _strlen(directs));
				write(STDOUT_FILENO, "\n", 1);
			}
		}
		else
		{
			directs = *args;
			info->status = chdir(directs);
		}
	}
	else
	{
		directs = get_dict_val(info->env, "HOME");
		if (directs)
			info->status = chdir(directs);
	}
	if (info->status != -1)
		__cd_success(info);
	else
		__cd_error(info, directs);

	return (info->status);
}

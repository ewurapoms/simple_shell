#include "envar.h"

/**
  * env_to_dict - function that creates a list from the environment
  * @env: input value
  * Return: start
  */
env_t *env_to_dict(char **env)
{
	env_t *start = NULL;

	if (!_env_to_dict(&start, env))
		free_dict(&start);

	return (start);
}


/**
 * _env_to_dict - helper function that substitutes env for linked list
 * @tailptr: ptr to list tail
 * @env: input value
 *
 * Return: ...
 */
env_t *_env_to_dict(env_t **tailptr, char **env)
{
	env_t *end;
	char *str;
	ssize_t len;

	if (!*env)
		return (*tailptr);

	str = _strdup(*env);
	if (!str)
		return (NULL);

	len = _strchr(*env, '=');

	if (len == -1)
		return (NULL);

	str[len] = '\0';
	end = add_dict_node_end(tailptr, str, len + str + 1);
	free(str);

	return (_env_to_dict(&end, env + 1));
}


/**
  * dict_to_env - function prints a linked list from environment
  * @head: is the head of list
  * Return: pointer to linked list
  */
char **dict_to_env(env_t *head)
{
	char **env;
	size_t len = 0;
	env_t *temp = head;

	while (temp)
		len++, temp = temp->next;

	env = malloc(sizeof(char *) * (len + 1));
	if (!env)
		return (NULL);

	for (len = 0; head; head = head->next)
		env[len++] = strjoin(NULL, "=", head->key, head->val);
	env[len] = NULL;

	return (env);
}

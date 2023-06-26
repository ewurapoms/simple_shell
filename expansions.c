#include "shell.h"

/**
 * expand_aliases - function is a recursion on existing alias cmd
 * @aliases:is the list of aliases
 * @tokptr: pointer value
 *
 * Return: 0
 */
void expand_aliases(alias_t *aliases, char ***tokptr)
{
	char **n, **p;
	char *file, *value, *tmp;

	if (!*tokptr)
		return;
	do {
		file = expand_alias(aliases, tokptr);
		value = get_dict_val(aliases, file);
		if (value && *value && _isspace(value[_strlen(value) - 1]))
		{
			p = *tokptr;
			n = arrdup(p + 1);

			expand_aliases(aliases, &n);
			tmp = *(p + 1);

			*(p + 1) = NULL;
			*tokptr = arrjoin(p, n);
			*(p + 1) = tmp;

			free_tokens(&p);
			free_tokens(&n);
		}
	} while (file && **tokptr && _strcmp(file, **tokptr));
}

/**
 * expand_alias - Entry point
 * @aliases: ...
 * @tokptr: pointer value
 *
 * Return: ptr to alias or NULL
 */
char *expand_alias(alias_t *aliases, char ***tokptr)
{
	char **tokas, **toks = *tokptr;

	if (!*toks)
		return (NULL);

	while (aliases)
	{
		if (!_strcmp(*toks, aliases->key))
		{
			tokas = tokenize(aliases->val);
			*tokptr = arrjoin(tokas, toks + 1);

			free_tokens(&toks);
			free_tokens(&tokas);

			return (aliases->key);
		}
		aliases = aliases->next;
	}
	return (NULL);
}

/**
 * expand_vars - function prints variable expansions
 * @info: ...
  * @tokptr: is a pointer
 */
void expand_vars(info_t *info, char ***tokptr)
{
	char **n = NULL, **p, **temp, **toks;
	
	for (toks = *tokptr; **tokptr; ++(*tokptr))
	{
		p = n;
		temp = _expand_vars(info, tokptr);
		n = arrjoin(p, temp);
		free_tokens(&p);
		free_tokens(&temp);
		free(**tokptr);
	}
	free(toks);
	*tokptr = n;
}

/**
 * _expand_vars - function that performs variable expansion
 * @info: ...
  * @tokptr: ...
 *
 * Return: new token
 */
char **_expand_vars(info_t *info, char ***tokptr)
{
	char *var = NULL, *val = NULL;
	char *tok = **tokptr;
	size_t pos = 0;
	size_t var_len, val_len;
	quote_state_t state = QUOTE_NONE;

	while (var_len = val_len = 1, tok[pos])
	{
		if (quote_state_len(tok + pos, state) == 0)
		{
			if ((state & (QUOTE_DOUBLE | QUOTE_SINGLE)) && !tok[++pos])
				break;
			state = quote_state(tok[pos]);
			if (state & (QUOTE_DOUBLE | QUOTE_SINGLE | QUOTE_ESCAPE))
				++pos;
			continue;
		}
		if ((state & (QUOTE_DOUBLE)) && (quote_state(tok[pos]) & QUOTE_ESCAPE))
		{
			if (!tok[++pos] || !tok[++pos])
				break;
			state = quote_state(tok[pos]);
			if (state & (QUOTE_DOUBLE | QUOTE_SINGLE | QUOTE_ESCAPE))
				++pos;
			continue;
		}
		if (state & (QUOTE_SINGLE))
		{
			pos += quote_state_len(tok + pos, state);
			if (tok[pos])
				++pos;
			continue;
		}
		if (state & (QUOTE_ESCAPE))
		{
			if (!tok[++pos] || !tok[++pos])
				break;
			state = quote_state(tok[pos]);
			if (state & (QUOTE_DOUBLE | QUOTE_SINGLE | QUOTE_ESCAPE))
				++pos;
			continue;
		}
		if (tok[pos] != '$')
		{
			++pos;
			continue;
		}
		if (tok[pos + 1] == '$')
		{
			val = num_to_str(info->pid);
		}
		else if (tok[pos + 1] == '?')
		{
			val = num_to_str(info->status);
		}
		else if (_isident(tok[pos + 1]) && !_isdigit(tok[pos + 1]))
		{
			while (_isident(tok[pos + var_len + 1]))
				++var_len;

			var = _strndup(tok + pos + 1, var_len);
			val = get_dict_val(info->env, var);

			if (val)
				val = _strdup(val);
			else
				val = _strdup("");

			free(var);
			var = NULL;
		}
		if (val)
		{
			val_len = _strlen(val);
			**tokptr = malloc(sizeof(char) * (
					pos + val_len + _strlen(tok + pos + var_len) + 1
					));
			_memcpy(**tokptr, tok, pos);
			_memcpy(**tokptr + pos, val, val_len);
			_strcpy(**tokptr + pos + val_len, tok + pos + var_len + 1);

			free(tok);
			tok = **tokptr;

			free(val);
			val = NULL;
		}
		pos += val_len;
	}
	return (tokenize(**tokptr));
}

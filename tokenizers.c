#include "toks.h"

/**
 * count_tokens - func checks strlen after dequoting
 * @str: is the string to check
 * Return: strlen
 */
size_t count_tokens(const char *str)
{
	size_t sum = 0;
	quote_state_t state;

	for (; *(str += quote_state_len(str, QUOTE_NONE)); sum++)
	{
		while (*str && (state = quote_state(*str)) != QUOTE_NONE)
		{
			if (state & (QUOTE_DOUBLE | QUOTE_SINGLE | QUOTE_ESCAPE))
				str += quote_state_len(str + 1, state) + 1;
			else
				str += quote_state_len(str, state);

			if (*str && (state & (QUOTE_DOUBLE | QUOTE_SINGLE)))
				str++;
		}
	}
	return (sum);
}

/**
 * count_tokens_noquote - function that counts words in a str
 * @str: the string to count
 * Return: -1 where str is NULL, else num of tokenized strings
 */
size_t count_tokens_noquote(const char *str)
{
	size_t total = 0;

	for (; *str; total++)
	{
		while (_isspace(*str))
			++str;
		if (!*str)
			break;
		do {
			++str;
		} while (*str && !_isspace(*str));
	}
	return (total);
}

/**
 * tokenize - function that prints dequoted tokens
 * @str: is the string
 * Return: Null (malloc failure, str = 0 or absence of tokens)
 * else return an array of str
 */

char **tokenize(const char *str)
{
	quote_state_t state;
	char **tokes;
	const char *tk;
	size_t sum;

	if (!str)
		return (NULL);

	tokes = malloc(sizeof(char *) * (count_tokens(str) + 1));
	if (!tokes)
		return (NULL);

	for (sum = 0; *(str += quote_state_len(str, QUOTE_NONE)); sum++)
	{
		tk = str;

		while (*str && (state = quote_state(*str)) != QUOTE_NONE)
		{
			if (state & (QUOTE_DOUBLE | QUOTE_SINGLE | QUOTE_ESCAPE))
				str += quote_state_len(str + 1, state) + 1;
			else
				str += quote_state_len(str, state);

			if (*str && (state & (QUOTE_DOUBLE | QUOTE_SINGLE)))
				str++;
		}

		tokes[sum] = _memdup(tk, str - tk + 1);
		if (!tokes[sum])
		{
			free_tokens(&tokes);
			return (NULL);
		}
		tokes[sum][str - tk] = '\0';
	}
	tokes[sum] = NULL;

	return (tokes);
}

/**
 * tokenize_noquote - function splits a string into tokens
 * @str: the string to split
 * Return: Null (malloc failure, str = 0 or absence of tokens)
 * else return an array of str
 */
char **tokenize_noquote(const char *str)
{
	char **tokes;
	const char *tk;
	size_t sum;

	if (!str)
		return (NULL);

	tokes = malloc(sizeof(char *) * (count_tokens_noquote(str) + 1));
	if (!tokes)
		return (NULL);

	for (sum = 0; *str; sum++)
	{
		while (_isspace(*str))
			++str;
		if (!*str)
			break;

		tk = str;
		do {
			++str;
		} while (*str && !_isspace(*str));

		tokes[sum] = _memdup(tk, str - tk + 1);
		if (!tokes[sum])
		{
			free_tokens(&tokes);
			return (NULL);
		}
		tokes[sum][str - tk] = '\0';
	}
	tokes[sum] = NULL;

	return (tokes);
}

/**
 * free_tokens - function frees an array of strings
 * @tokens: is a double pointer
 */
void free_tokens(char ***tokens)
{
	char **tk;

	if (!tokens)
		return;

	tk = *tokens;
	if (!tk)
		return;

	while (*tk)
		free(*tk++);
	free(*tokens);

	*tokens = NULL;
}

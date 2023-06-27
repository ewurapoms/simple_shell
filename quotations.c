#include "quotes.h"

/**
 * quote_state - function retrieves state of given character
 * @c: is the character
 * Return: function results
 */
quote_state_t quote_state(char c)
{
	if (_isspace(c))
		return (QUOTE_NONE);
	if (c == '"')
		return (QUOTE_DOUBLE);
	if (c == '\'')
		return (QUOTE_SINGLE);
	if (c == '\\')
		return (QUOTE_ESCAPE);
	return (QUOTE_WORD);
}

/**
 * quote_state_f - retrieves function of a given state
 * @s: is the state
 *
 * Return: the state of char 'c'
 */
quote_state_fp quote_state_f(quote_state_t s)
{
	switch (s)
	{
		case QUOTE_NONE:
			return (_quote_state_none);
		case QUOTE_WORD:
			return (_quote_state_word);
		case QUOTE_DOUBLE:
			return (_quote_state_double);
		case QUOTE_SINGLE:
			return (_quote_state_single);
		case QUOTE_ESCAPE:
			return (_quote_state_escape);
	}
	return (NULL);
}
/**
 * quote_state_len - outputs a state's length
 * @str: is the string
 * @state: ...
 *
 * Return: the state of char 'c'
 */
size_t quote_state_len(const char *str, quote_state_t state)
{
	return (quote_state_f(state)(str, NULL));
}

/**
 * dequote - function unquotes a str
 * @str: the string to unquote
 * Return: NULL (failed), else copy of dequoted string.
 */

char *dequote(const char *str)
{
	char *new_node;
	size_t length = 0, slen;
	quote_state_t state;

	if (!str)
		return (NULL);

	new_node = malloc(sizeof(char) * (dequote_len(str) + 1));
	if (!new_node)
		return (NULL);

	while (*str)
	{
		state = quote_state(*str);
		str += (1 && (state & (QUOTE_DOUBLE | QUOTE_SINGLE | QUOTE_ESCAPE)));
		slen = quote_state_len(str, state);
		if (state & QUOTE_DOUBLE)
		{
			for ( ; slen; --slen)
			{
				if (quote_state(*str++) & QUOTE_ESCAPE)
				{
					if (*str == '\n')
					{
						++str, --slen;
						continue;
					}
					if (_isspecial_double(*str))
						++str, --slen;
				}
				new_node[slen++] = str[-1];
			}
		}
		_memcpy(new_node + length, str, slen);
		length += slen;
		str += slen;
		str += (*str && (state & (QUOTE_DOUBLE | QUOTE_SINGLE)));
	}
	new_node[length] = '\0';
	return (new_node);
}


/**
 * dequote_len - sum string len after dequoting
 * @str: string input
 * Return: strlen post dequote
 */
size_t dequote_len(const char *str)
{
	size_t length = 0, slen;
	quote_state_t state;

	while (*str)
	{
		state = quote_state(*str);
		str += (1 && (state & (QUOTE_DOUBLE | QUOTE_SINGLE | QUOTE_ESCAPE)));
		slen = quote_state_len(str, state);
		if (state & QUOTE_DOUBLE)
		{
			for ( ; slen; --slen)
			{
				if (quote_state(*str++) & QUOTE_ESCAPE)
				{
					if (*str == '\n')
					{
						++str, --slen;
						continue;
					}
					if (_isspecial_double(*str))
						++str, --slen;
				}
				length++;
			}
		}
		length += slen;
		str += slen;
		str += (*str && (state & (QUOTE_DOUBLE | QUOTE_SINGLE)));
	}
	return (length);
}

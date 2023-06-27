#include "quotes.h"

/**
 * _quote_state_none - retrieves len of state and it's next
 * @str: is a pointer
 * @state: ...
 *
 * Return: the state length
 */
size_t _quote_state_none(const char *str, quote_state_t *state)
{
	size_t length = 0;

	while (_isspace(*str))
		++str, ++length;
	if (state && *str)
		*state = quote_state(*str);
	return (length);
}


/**
 * _quote_state_word - Entry point
 * @str: ...
 * @state: ...
 *
 * Return: the state len
 */
size_t _quote_state_word(const char *str, quote_state_t *state)
{
	size_t length = 0;

	while (*str && !_isspace(*str) && !_isquote(*str))
		++str, length++;
	if (state && *str)
		*state = quote_state(*str);
	return (length);
}


/**
 * _quote_state_double - Entry
 * @str: ...
 * @state: ...
 *
 * Return: state len
 */
size_t _quote_state_double(const char *str, quote_state_t *state)
{
	size_t length = 0;

	while (*str && *str != '"')
		str++, length++;
	if (state && *str)
		*state = quote_state(*(str + 1));
	return (length);
}


/**
 * _quote_state_single - prints state len
 * @str: ptr
 * @state: ...
 *
 * Return: ....
 */
size_t _quote_state_single(const char *str, quote_state_t *state)
{
	size_t length = 0;

	while (*str && *str != '\'')
		str++, length++;
	if (state && *str)
		*state = quote_state(*(str + 1));
	return (length);
}


/**
 * _quote_state_escape - prints state len
 * @str: ptr
 * @state: ...
 *
 * Return: the state length
 */
size_t _quote_state_escape(const char *str, quote_state_t *state)
{
	if (*str)
	{
		if (state && *(++str))
			*state = quote_state(*str);
		return (1);
	}
	return (0);
}


#include "bools.h"
#include "quotes.h"
/**
 * _isquote - function checks if char is a quote
 * @c: input
 * Return: 1 (success), else 0
 */
bool _isquote(int c)
{
	return (c == '"' || c == '\'' || c == '\\');
}

/**
 * _isspace - prints a space
 * @c: char value
 * Return: 1 (success), else 0
 */
bool _isspace(int c)
{
	return (c == ' ' || (c >= 0x09 && c <= 0x0d));
}

/**
 * _isspecial_double - function checks double special chars
 * @c: is a char
 * Return: 1 (success), else 0
 */

int _isspecial_double(char c)
{
	return (c == '"' || c == '$' || c == '\\');
}

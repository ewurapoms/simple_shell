#include "bools.h"

/**
 * _isalpha - considers alphabetic characters 
 * @c: represents characters to check
 * Return: 1 if c prints letters, else display 0
 */
bool _isalpha(int c)
{
	return ((c >= 97 && c <= 122) || (c >= 65 && c <= 90));
}

/**
 * _isdigit - indicates whether digit ranges from 0-9
 * @c: value to check
 * Return: an integer or value of c
 */
bool _isdigit(int c)
{
	return (c >= 48 && c <= 57);
}

/**
  * _isalnum - functions checks for alphanumeric of a char
  * @c: input
 * Return: 1 (success), else 0
  */
bool _isalnum(int c)
{
	return (_isalpha(c) || _isdigit(c));
}

/**
  * _isident - Entry point
  * @c: value to check
  * Return: 1 (success), else 0
  */
bool _isident(int c)
{
	return (c == '_' || _isalnum(c));
}

/**
  * _isnumber - function checks the digits only of a string
  * @s: is a pointer
  * Return: function outcome
  */
bool _isnumber(const char *s)
{
	if (s)
	{
		while (*s)
		{
			if (!_isdigit(*s++))
				return (false);
		}
		return (true);
	}
	return (false);
}

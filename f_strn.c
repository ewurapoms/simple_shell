#include "string.h"

/**
 * _strnlen - function checks length of a string
 * @str: string to check
 * @n: is the num of chars
 * Return: value of n
 */
ssize_t _strnlen(const char *str, size_t n)
{
	const char *ch = str;

	if (!str)
		return (-1);

	while (n && *ch)
		--n;
	ch++;

	return (ch - str);
}

/**
  * _strnchr - Entry point
  * @str: string
  * @chr: is character
  * @n: number value
  * Return: ...
  */
ssize_t _strnchr(const char *str, char chr, size_t n)
{
	ssize_t i;

	if (!str)
		return (-1);

	for (i = 0; n && str[i]; --n, ++i)
	{
		if (str[i] == chr)
			return (i);
	}

	return (-1);
}

/**
 * _strncpy - function copies the string
 * @dest: input value
 * @src: source input
 * @n: is the num
 * Return: *dest
 */

char *_strncpy(char *dest, const char *src, size_t n)
{
	char *m = dest;

	for ( ; n && *src; --n)
		*m++ = *src++;
	if (n)
		*m = '\0';

	return (dest);
}
/**
 * _strndup - function duplicates a string
 * @str: the string value
 * @n: number to copy
 * Return: NULL
 */
char *_strndup(const char *str, size_t n)
{
	char *twin;
	size_t x = 0;

	if (!str)
		return (NULL);

	while (n && str[x])
		--n, x++;

	twin = malloc(sizeof(char) * (x + 1));
	if (!twin)
		return (NULL);

	twin[x] = '\0';

	while (x--)
		twin[x] = str[x];

	return (twin);
}

/**
 * _strncmp - function that compares two strings
 * @s1: a string
 * @s2: another string
 * @n: num
 * Return: 0
 */
int _strncmp(const char *s1, const char *s2, size_t n)
{
	for (; n && *s1 && *s2; --n, ++s1, ++s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
	}

	if (n)
	{
		if (*s1)
			return (1);
		if (*s2)
			return (-1);
	}

	return (0);
}

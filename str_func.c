#include "string.h"

/**
 * _strlen - checks the string length
 * @str: the string to check
 * Return: length of the string
 */
ssize_t _strlen(const char *str)
{
	const char *ch = str;

	if (!str)
		return (-1);

	while (*ch)
		ch++;

	return (ch - str);
}

/**
  * _strchr - Entry point
  * @str: is the string
  * @chr: is the char
  * Return: value of i
  */
ssize_t _strchr(const char *str, char chr)
{
	ssize_t i = 0;

	if (!str)
		return (-1);

	for (; str[i]; i++)
	{
		if (str[i] == chr)
			return (i);
	}

	return (-1);
}

/**
 * _strcpy - function that copies a string
 * @dest: is the destination
 * @src: is the source
 * Return: ptr to dest
 */
char *_strcpy(char *dest, const char *src)
{
	char *m = dest;

	while (*src)
		*m++ = *src++;
	*m = '\0';

	return (dest);
}

/**
 * _strdup - function duplicates an array of strings
 * @str: is a string pointer
 * Return: NULL
 */
char *_strdup(const char *str)
{
	char *twin;
	size_t y = 0;

	if (!str)
		return (NULL);

	while (str[y++])
		;

	twin = malloc(sizeof(char) * y);
	if (!twin)
		return (NULL);

	while (y--)
		twin[y] = str[y];

	return (twin);
}

/**
 * _strcmp - function that compares two strings
 * @s1: first string
 * @s2: another string
 * Return: 0
 */
int _strcmp(const char *s1, const char *s2)
{
	for (; *s1 && *s2; ++s1, ++s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
	}

	if (*s1)
		return (1);
	if (*s2)
		return (-1);

	return (0);
}

#include "string.h"

/**
 * _memset - Entry point
 * @dest: input
 * @chr: input
 * @n: input
 * Return: dest
 */

void *_memset(void *dest, unsigned char chr, size_t n)
{
	unsigned char *mem = dest;

	if (dest)
	{
		while (n--)
			*mem++ = chr;
	}
	return (dest);
}

/**
 * _memcpy - function copies a memory
 * @dest: destination
 * @src: source
 * @n: input
 *
 * Return: dest
*/

void *_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char *mem = dest;
	const unsigned char *area = src;

	if (dest && src)
	{
		while (n--)
			*mem++ = *area++;
	}
	return (dest);
}

/**
 * _memdup - duplicates the memory
 * @src: source
 * @n: the number value
 * Return: duplicated memory otherwise NULL
 */

void *_memdup(const void *src, size_t n)
{
	void *dobs = malloc(n);
	unsigned char *mem = dobs;
	const unsigned char *area = src;

	if (dobs)
	{
		while (n--)
			*mem++ = *area++;
	}
	return (dobs);
}

/**
 * _memchr - Entry point
 * @src: memory source
 * @chr: is char
 * @n: input
 * Return: -1
 */

ssize_t _memchr(const void *src, unsigned char chr, size_t n)
{
	const unsigned char *x = src;
	ssize_t y = 0;

	if (src)
	{
		while (n--)
		{
			if (x[y] == chr)
				return (y);
			y += 1;
		}
	}
	return (-1);
}

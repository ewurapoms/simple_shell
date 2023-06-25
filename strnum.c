#include "string.h"

/**
 * _num_to_str - function changes num to a string
 * @buf: the string to change
 * @n: number value
 */
static void _num_to_str(char **buf, size_t n)
{
	if (n > 9)
		_num_to_str(buf, n / 10);
	**buf = 48 + n % 10;
	*buf += 1;
	**buf = '\0';
}

/**
 * num_to_str - function changes num to a string (helper)
 * @n: is the number
 * Return: a pointer to the string
 */
char *num_to_str(size_t n)
{
	size_t temp = n, length = 1;
	char *buf;

	while (temp /= 10)
		length++;
	buf = malloc(length + 1);
	if (!buf)
		return (NULL);
	_num_to_str(&buf, n);
	return (buf - length);
}

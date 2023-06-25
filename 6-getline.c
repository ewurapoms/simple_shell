#include "getline.h"
#include "string.h"

/**
 * _realloc - funtion that reallocates a buffer
 * @old: it's a ptr
 * @old_size: current buffer size
 * @new_size: change buffer size
 * Return: NULL or pointer to buffer
 */
static void *_realloc(void *old, size_t old_size, size_t new_size)
{
	void *n = NULL;

	if (old)
	{
		if (new_size)
		{
			n = malloc(new_size);
			if (n)
			{
				_memcpy(n, old, old_size < new_size ? old_size : new_size);
				free(old);
			}
		}
		else
		{
			free(old);
		}
	}
	return (n);
}
/**
 * _getline_next - read a line of input(helper)
 * @buf: pointer value
 * @line: pointer address
 * @size: pointer value
 * @n: num of chars to copy from the buffer
 * Return: NULL (fail), or pointer to the line of input.
 */
static char *_getline_next(buf_t *buf, char **line, size_t *size, size_t n)
{
	char *tmp = NULL;

	if (*line)
		tmp = _realloc(*line, *size, *size + n);
	else
		tmp = malloc(n + 1);

	if (tmp)
	{
		*line = tmp;

		if (*size)
			*size -= 1;

		_memcpy(*line + *size, buf->next, n);
		*size += n;

		(*line)[*size] = '\0';
		*size += 1;
	}
	else
	{
		free(*line);
		*line = NULL;
		*size = 0;
	}
	return (*line);
}

/**
 * _getline_buf - function that creates, retrieves, and removes buffers
 * @table: input value
 * @fd: ...
 * Return: NULL or a ptr to the buffer
 */
static buf_t *_getline_buf(buf_table_t *table, const int fd)
{
	buf_table_node_t *list = NULL;
	size_t i = fd % GETLINE_TABLE_SIZE;

	if (table)
	{
		if (fd < 0)
		{
			for (i = 0; i < GETLINE_TABLE_SIZE; i += 1)
			{
				while ((list = (*table)[i]))
				{
					(*table)[i] = list->next;
					free(list);
				}
			}
		}
		else
		{
			list = (*table)[i];
			while (list && list->fd != fd)
				list = list->next;
			if (list == NULL)
			{
				list = malloc(sizeof(*list));
				if (list)
				{
					list->fd = fd;
					list->buf.next = NULL;
					list->buf.remaining = 0;
					list->next = (*table)[i];
					(*table)[i] = list;
				}
			}
		}
	}
	return (list ? &list->buf : NULL);
}

/**
 * _getline - function that reads a line of input
 * @fd: it's the file descriptor
 * Return: NULL.
 */
char *_getline(const int fd)
{
	static buf_table_t tab;
	buf_t *buff = _getline_buf(&tab, fd);
	char *line = NULL;
	size_t size = 0;
	ssize_t i = 0;
	ssize_t _read = 0;

	if (buff)
	{
		do {
			if (buff->remaining == 0)
				buff->next = buff->buffer;
			if (_read)
				buff->remaining = _read;
			if (buff->remaining)
			{
				i = _memchr(buff->next, '\n', buff->remaining);
				if (i == -1)
				{
					if (_getline_next(buff, &line, &size, buff->remaining))
						buff->next += buff->remaining, buff->remaining = 0;
					else
						break;
				}
				else
				{
					if (_getline_next(buff, &line, &size, i + 1))
						buff->next += i + 1, buff->remaining -= i + 1;
					break;
				}
			}
		} while ((_read = read(fd, buff->buffer, GETLINE_BUFFER_SIZE)) > 0);
		if (_read == -1)
		{
			free(line);
			line = NULL;
			size = 0;
		}
	}
	return (line);
}

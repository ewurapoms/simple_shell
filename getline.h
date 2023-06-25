#ifndef _GETLINE_H_
#define _GETLINE_H_

#include <stdlib.h>
#include <unistd.h>

#include "string.h"

#define GETLINE_BUFFER_SIZE 4096

/**
 * struct buf_s - Entry point
 * @buffer: input
 * @next: is a ptr value
 * @remaining: is num remainder
 */
typedef struct buf_s
{
	char buffer[GETLINE_BUFFER_SIZE];
	char *next;
	size_t remaining;
} buf_t;

#define GETLINE_TABLE_SIZE 127

/**
 * struct buf_table_node_s - function creates a buffer table
 * @fd: is the file descriptor
 * @buf: is a buffer
 * @next: input
 */
typedef struct buf_table_node_s
{
	int fd;
	struct buf_s buf;
	struct buf_table_node_s *next;
} buf_table_node_t;

typedef buf_table_node_t *buf_table_t[GETLINE_TABLE_SIZE];

char *_getline(const int fd);

#endif


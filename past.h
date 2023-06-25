#ifndef _PAST_H_
#define _PAST_H_

#include "lists.h"
#include "typdef.h"

/**
  * struct history - prints shell history
  * @head: is a pointer to the list
  * @filename: is the files to archive name
  * @n: is the num of list entries
  */
struct history
{
	struct list *head;
	char *filename;
	size_t n;
};

#endif

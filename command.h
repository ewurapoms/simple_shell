#ifndef _COMMAND_H_
#define _COMMAND_H_

#include <stdlib.h>
#include "quotes.h"
#include "string.h"
#include "toks.h"
#include "typdef.h"

/**
 * enum cmdlist_sep_n - Entry point
 * @SEMICOLON: is the symbol ';'
 * @AMPERSAND: is the symbol '&'
 * @AND: is the '&&' symbol
 * @OR: represnts the operator '||'
 */

typedef enum cmdlist_sep_n
{
	SEMICOLON = 1,
	AMPERSAND = 2,
	AND       = 4,
	OR        = 8
} cmdlist_sep_n_t;


/**
 * struct cmdlist_sep - function that separates a command list
 * @sep: is the separator
 * @n: is the num value
 */

typedef struct cmdlist_sep
{
	const char *sep;
	enum cmdlist_sep_n n;
} cmdlist_sep_t;

/**
 * struct cmdlist - function that creates a linked list of commands
 * @next: input
 * @tree: input
 * @tokens: input
 */

struct cmdlist
{
	struct cmdlist *next;
	struct cmdtree *tree;
	char **tokens;
};

/**
 * struct cmdtree - function that creates a command binary tree
 * @success: cmd value
 * @failure: cmd value
 * @tokens: input value
 * @sep: seperates a list
 */

struct cmdtree
{
	struct cmdtree *success;
	struct cmdtree *failure;
	const char * const *tokens;
	struct cmdlist_sep sep;
};

char **pop_cmd(cmdlist_t **headptr);
cmdlist_t *cmd_to_list(const char *cmd);
cmdlist_t *_cmd_to_list(cmdlist_t **tailptr, char *split, size_t count);
cmdlist_t *add_cmd_end(cmdlist_t **headptr, const char *cmd);
cmdlist_t *del_cmd(cmdlist_t **headptr, size_t index);
cmdtree_t *cmd_to_tree(const char * const *tokens);
size_t split_cmd(char *cmd);
void free_cmdlist(cmdlist_t **headptr);
void free_cmdtree(cmdtree_t **rootptr);

#endif

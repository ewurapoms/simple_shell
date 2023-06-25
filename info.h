#ifndef _INFO_H_
#define _INFO_H_

#include <stdlib.h>
#include <unistd.h>

#include "aka.h"
#include "command.h"
#include "envar.h"
#include "err.h"
#include "getline.h"
#include "past.h"
#include "lists.h"
#include "string.h"
#include "toks.h"
#include "typdef.h"

extern char **environ;

/**
  * struct info - shell state
  * @interactive: input
  * @argc: input
  * @argv: input
  * @file: input
  * @fileno: input
  * @status: input
  * @line: input
  * @lineno: input
  * @tokens: input
  * @pid: input
  * @cwd: input
  * @exe: input
  * @env: input
  * @path: input
  * @aliases: input
  * @history: input
  * @commands: input
  */
struct info
{
	int interactive;
	int argc;
	char **argv;
	char *file;
	int fileno;
	int status;
	char *line;
	size_t lineno;
	char **tokens;
	pid_t pid;
	char *cwd;
	char *exe;
	env_t *env;
	list_t *path;
	alias_t *aliases;
	history_t *history;
	cmdlist_t *commands;
};

info_t *init_info(int argc, char **argv);
int free_info(info_t *info);

#endif

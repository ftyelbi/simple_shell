#ifndef SHELL_H_
#define SHELL_H_

#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <signal.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define BUFSIZE 1024
#define NEWLINE '\n'
#define DELIM_T " \t\n\a\r"

extern char **environ;

/**
 * struct path - A linked list containing each path in PATH variable
 * @str: A single variable (i.e /usr/bin )
 * @next: next path in the list
 */
typedef struct path
{
	char *str;
	struct path *next;
} path_l;

/**
 * struct alias - linked list of all set aliases in the shell
 * @name: the name of the alias
 * @value: the value of the alias corresponding to name
 * @next: next alias in aliases
 */
typedef struct alias
{
	char *name;
	char *value;
	struct alias *next;
} alias_l;

/**
 * struct data - structure containing shell data
 * @_environ: the shell environment, copied from the default shell environment
 * @alias: linked list of aliases created in the current shell session
 * @arr: an array containing each argument entered into the shell
 * @av: arguments vector
 * @length: length of the line
 * @line: the entire line of commands
 * @path: linked list containing the PATH variable
 * @pid: process id of the current shell
 * @status: shell status, updated on success/failure of a command
 */
typedef struct data
{
	alias_l *alias;
	char **_environ;
	char **arr;
	char **av;
	char *line;
	int status;
	path_l *path;
	pid_t pid;
	size_t length;
} sh_data;

/**
 * struct built_in - structure containg builtin functions and their functions
 * @str: the command name
 * @func: pointer to the function for the specific command
 */
typedef struct built_in
{
	char *str;
	int (*func)(sh_data *);
} built_in;

/* Major stakeholders */
char **_get_commands(char *, size_t);
char *_check_shell(sh_data *);
char *my_getenv(sh_data *, char *);
char *_search_path(path_l *, char *);
int (*_get_func(char **))(sh_data *);
void _loop_shell(sh_data *);
void _non_interact(sh_data *);
int _rm_comments(char **);
void _expand_var(sh_data *);
int _cd_err(sh_data *, int);

/* Aliases */
alias_l *plus_alias(alias_l **, char *, char *);
int is_alias(sh_data *);
int print_1_alias(sh_data *, char *);
int print_a_alias(sh_data *);
int on_alias(sh_data *, char *);
void _check_alias(sh_data *);
void _free_aliases(alias_l *);

/* Other builtins */
int is_cd(sh_data *);
void _mod_dir(sh_data *, char *, char *);
int is_env(sh_data *);
char *my_mod_env(sh_data *);
int is_exit(sh_data *);
int is_set(sh_data *);
int is_unset(sh_data *);

/* Replacement functions */
char *is_strcat(char *, char *);
char *is_strcpy(char *, char *);
char *is_strdup(char *);
char *is_itoa(int);
char *is_strtok(char *, const char *);
int is_atoi(char *);
int is_isdigit(char *);
int is_strcmp(char *, char *);
int is_strlen(char *);
void *is_memchr(register const void *, int, size_t);
void *is_realloc(void *, unsigned int, unsigned int);
void is_memcpy(void *, const void *, unsigned int);
ssize_t _my_getline(char **, size_t *, FILE *);
void _insert_line(char **, size_t *n, char *, size_t);
void _reverse_str(char *);

/* Custom functions */
void _free_arr2(char **);
void _free_list(path_l *);
int _get_len(int);
path_l *_add_node_end(path_l **, char *);
path_l *_path_to_list(sh_data *);
size_t print_list(const path_l *);
void print_path_dir(void);

#endif

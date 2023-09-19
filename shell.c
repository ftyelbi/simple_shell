#include "shell.h"

/**
 * _get_func - returns functions for builtin commands
 * @arr: the line splitted into command and args
 *
 * Return: the function that prints the builtin command
 */
int (*_get_func(char **arr))(sh_data *)
{
	built_in sh[] = {
		{"exit", is_exit},
		{"env", is_env},
		{"setenv", is_set},
		{"unsetenv", is_unset},
		{"cd", is_cd},
		{"alias", is_alias},
		{NULL, NULL}
	};

	int i = 0;

	if (arr != NULL)
	{
		while (sh[i].func != NULL)
		{
			if (is_strcmp(sh[i].str, arr[0]) == 0)
			{
				return (sh[i].func);
			}
			else
				i++;
		}
	}

	return (NULL);
}

/**
 * _non_interact - runs the shell in non interactive mode
 * @shell: the shell data struct
 *
 * Return: non, uses exit with a status
 */
void _non_interact(sh_data *shell)
{
	char *path;

	path = _check_shell(shell);
	if (!path)
		is_exit(shell);

	shell->status = execve(path, shell->arr, shell->_environ);
	if (shell->status == -1)
	{
		write(STDERR_FILENO, shell->av[0], is_strlen(shell->av[0]));
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, shell->arr[0], is_strlen(shell->arr[0]));
		write(STDERR_FILENO, ": Permission denied\n", 20);
		free(path);
		shell->status = 13;
		is_exit(shell);
	}
	shell->status = WEXITSTATUS(shell->status);
	_free_arr2(shell->arr);
	free(path);
	is_exit(shell);
}

/**
 * _loop_shell - runs the shell continously
 * @shell: the shell data
 *
 * Return: void
 */
void _loop_shell(sh_data *shell)
{
	char *path;

	if (shell->av[1])
	{
	}
	else if (!isatty(STDIN_FILENO))
		_non_interact(shell);
	else
	{
		for (; ;)
		{
			write(STDOUT_FILENO, "($) ", 4);
			fflush(stdout);
			path = _check_shell(shell);
			if (!path)
				continue;
			shell->pid = fork();
			if (shell->pid == 0)
			{
				shell->status = execve(path, shell->arr, shell->_environ);
				if (shell->status == -1)
				{
					write(STDERR_FILENO, shell->av[0], is_strlen(shell->av[0]));
					write(STDERR_FILENO, ": ", 2);
					write(STDERR_FILENO, shell->arr[0], is_strlen(shell->arr[0]));
					write(STDERR_FILENO, ": Permission denied\n", 20);
					free(path);
					shell->status = 13;
					is_exit(shell);
				}
			}
			else
			{
				wait(&shell->status);
				shell->status = WEXITSTATUS(shell->status);
			}
			_free_arr2(shell->arr);
			free(path);
		}
	}
}

/**
 * _check_shell - checks the shell commands, paths and builtins
 * @shell: pointer to shell data structure
 *
 * Return: path or NULL
 */
char *_check_shell(sh_data *shell)
{
	int (*built_in_func)(sh_data *sh);
	char *path;

	shell->arr = _get_commands(shell->line, shell->length);
	if (!shell->arr)
	{
		free(shell->line);
		return (NULL);
	}
	_check_alias(shell);
	_expand_var(shell);
	built_in_func = _get_func(shell->arr);

	if (built_in_func != NULL)
	{
		shell->status = built_in_func(shell);
		_free_arr2(shell->arr);
		return (NULL);
	}
	path = _search_path(shell->path, shell->arr[0]);

	if (!path)
	{
		write(STDERR_FILENO, shell->av[0], is_strlen(shell->av[0]));
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, shell->arr[0], is_strlen(shell->arr[0]));
		write(STDERR_FILENO, ": No such file or directory\n", 28);
		shell->status = 2;
		_free_arr2(shell->arr);
		free(path);
		return (NULL);
	}
	return (path);
}

/**
 * main - main body of the shell
 * @ac: command line argument count
 * @av: pointer to strings of command line arguments
 * @env: environment variables
 *
 * Return: 0 at successful exit
 */
int main(int ac, char *av[], char *env[])
{
	sh_data shell;
	int i;

	shell.line = NULL;
	shell.length = 0;
	shell.pid = getpid();
	shell.status = 0;
	shell.arr = NULL;
	shell.alias = NULL;

	shell.av = malloc(sizeof(char *) * (ac + 1));
	for (i = 0; av[i]; i++)
		shell.av[i] = is_strdup(av[0]);
	shell.av[i] = NULL;

	/* count th enumber of env strings to malloc a copy */
	for (i = 0; env[i]; i++)
		;

	shell._environ = malloc(sizeof(char *) * (i + 1));
	for (i = 0; env[i]; i++)
		shell._environ[i] = is_strdup(env[i]);
	shell._environ[i] = NULL;

	shell.path = _path_to_list(&shell);

	_loop_shell(&shell);

	return (0);
}

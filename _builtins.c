#include "shell.h"

/**
 * is_cd - changes the working directory of the shell
 * @shell: shell data struct
 *
 * Return: an exit value
 */
int is_cd(sh_data *shell)
{
	int m, n = 0;
	char *new_pwd, *old_pwd = my_getenv(shell, "PWD");

	if (shell->arr[1] == NULL)
	{
		_free_arr2(shell->arr);
		shell->arr = malloc(sizeof(char *) * 3);
		shell->arr[0] = is_strdup("cd");
		shell->arr[1] = my_getenv(shell, "HOME");
		shell->arr[2] = NULL;
	}
	else if (is_strcmp(shell->arr[1], "-") == 0)
	{
		free(shell->arr[1]);
		shell->arr[1] = my_getenv(shell, "OLDPWD");
		n++;
	}
	m = chdir(shell->arr[1]);
	if (m == -1)
	{
		_cd_err(shell, 1);
		free(old_pwd);
		return (2);
	}
	if (n == 1)
	{
		write(STDOUT_FILENO, shell->arr[1], is_strlen(shell->arr[1]));
		write(STDOUT_FILENO, "\n", 1);
	}
	new_pwd = getcwd(NULL, 1024);
	_mod_dir(shell, "new", new_pwd);
	_mod_dir(shell, "old", old_pwd);
	free(new_pwd);
	free(old_pwd);
	return (0);
}

/**
 * is_exit - exits the shell
 * @shell: shell data
 *
 * Return: exits with the status of shell, or 0 if none is specified
 */
int is_exit(sh_data *shell)
{
	int ex_it = shell->status;

	if (shell->arr[1])
	{
		shell->status = is_atoi(shell->arr[1]);
		ex_it = shell->status;
	}

	_free_list(shell->path);
	if (shell->alias)
		_free_aliases(shell->alias);
	_free_arr2(shell->av);
	_free_arr2(shell->_environ);
	_free_arr2(shell->arr);
	free(shell->line);

	exit(ex_it);
}

/**
 * is_env - prints the environment variables
 * @shell: shell data
 *
 * Return: 0
 */
int is_env(sh_data *shell)
{
	int j, len;

	for (j = 0; shell->_environ[j]; j++)
	{
		len = is_strlen(shell->_environ[j]);
		write(STDOUT_FILENO, shell->_environ[j], len);
		write(STDOUT_FILENO, "\n", 1);
	}

	return (0);
}

/**
 * is_set - adds or modifies an environment variable
 * @shell: shell data
 *
 * Return: 0 on completion or 12 if memory cannot be allocated
 */
int is_set(sh_data *shell)
{
	int i, j, k = 0, check, done = 0;
	char **new_env;

	for (i = 0; shell->_environ[i]; i++)
		;
	if (shell->arr[1] == NULL || shell->arr[2] == NULL)
		return (_cd_err(shell, 2));

	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return (12);
	for (i = 0; shell->_environ[i]; i++)
	{
		j = 0, check = 0;
		while (shell->_environ[i][j] != '=' && shell->arr[1][j] != '\0')
		{
			if (shell->_environ[i][j] != shell->arr[1][j])
				check = 1;
			j++;
		}
		if (check == 0)
		{
			new_env[k] = my_mod_env(shell);
			k++, done = 1;
			continue;
		}
		new_env[k] = is_strdup(shell->_environ[i]);
		k++;
	}
	if (done == 0)
	{
		new_env[k] = my_mod_env(shell);
		new_env[k + 1] = NULL;
	}
	else
		new_env[k] = NULL;
	_free_arr2(shell->_environ);
	shell->_environ = new_env;
	return (0);
}

/**
 * is_unset - deletes an environment variable
 * @shell: shell data
 *
 * Return: 0 on completion or -1 otherwise
 */
int is_unset(sh_data *shell)
{
	int i, j, k = 0, check, done = 0;
	char **new_env;

	for (i = 0; shell->_environ[i]; i++)
		;
	if (shell->arr[1] == NULL)
		return (_cd_err(shell, 3));

	new_env = malloc(sizeof(char *) * (i + 1));
	if (!new_env)
		return (12);
	for (i = 0; shell->_environ[i]; i++)
	{
		j = 0, check = 0;
		while (shell->_environ[i][j] != '=' && shell->arr[1][j] != '\0')
		{
			if (shell->_environ[i][j] != shell->arr[1][j])
				check = 1;
			j++;
		}
		if (check == 0)
		{
			done = 1;
			continue;
		}
		new_env[k] = is_strdup(shell->_environ[i]);
		k++;
	}
	new_env[k] = NULL;
	if (done == 0)
	{
		perror("Environment variable does not exist\n");
		_free_arr2(new_env);
		return (6);
	}
	_free_arr2(shell->_environ);
	shell->_environ = new_env;
	return (0);
}

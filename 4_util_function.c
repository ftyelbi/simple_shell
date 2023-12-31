#include "shell.h"

/**
 * _reverse_str - reverses a string
 * @string: to be reversed
 * Return: a pointer to the destination
 */
void _reverse_str(char *string)
{
	char temp;
	int q, r, k;

	for (q = 0; string[q] != '\0'; q++)
		;

	for (r = 0; r < (q - 1); r++)
	{
		for (k = r + 1; k > 0; k--)
		{
			temp = string[k];
			string[k] = string[k - 1];
			string[k - 1] = temp;
		}

	}
}
/**
 * my_mod_env - adds or modifies and environment variable
 * @shell: shell data
 *
 * Return: varaible with value
 */
char *my_mod_env(sh_data *shell)
{
	char *str;
	int len1;
	int len2;

	len1 = is_strlen(shell->arr[1]);
	len2 = is_strlen(shell->arr[2]);

	str = malloc(sizeof(char) * (len1 + len2 + 2));

	if (!str)
		return (NULL);

	is_strcpy(str, shell->arr[1]);
	is_strcat(str, "=");
	is_strcat(str, shell->arr[2]);

	return (str);
}
/**
 * _mod_dir - modifies a directory
 * @shell: pointer to shell
 * @dir: directory to set
 * @newdir: new directory
 *
 * Return: void
 */
void _mod_dir(sh_data *shell, char *dir, char *newdir)
{
	_free_arr2(shell->arr);
	shell->arr = malloc(sizeof(char *) * 4);
	shell->arr[0] = is_strdup("setenv");

	if (is_strcmp(dir, "old") == 0)

		shell->arr[1] = is_strdup("OLDPWD");
	else if (is_strcmp(dir, "new") == 0)
		shell->arr[1] = is_strdup("PWD");

	shell->arr[2] = is_strdup(newdir);
	shell->arr[3] = NULL;

	is_set(shell);
}
/**
 * _cd_err - prints an error
 * @shell: shell data
 * @n: the error number, from cd, set and unset | 1, 2, 3 respectively
 *
 * Return: nothing
 */
int _cd_err(sh_data *shell, int n)
{
	if (n == 1)
	{
		write(STDERR_FILENO, shell->av[0], is_strlen(shell->av[0]));
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, shell->arr[0], 2);
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, shell->arr[1], is_strlen(shell->arr[1]));
		write(STDERR_FILENO, ": No such file or directory\n", 28);
		return (1);
	}

	if (n == 2)
	{
		write(STDERR_FILENO, shell->av[0], is_strlen(shell->av[0]));
		write(STDERR_FILENO, ": Usage: setenv VARIABLE VALUE\n", 31);
		return (1);
	}
	if (n == 3)
	{
		write(STDERR_FILENO, shell->av[0], is_strlen(shell->av[0]));
		write(STDERR_FILENO, ": Usage: unsetenv VARIABLE\n", 27);
		return (1);
	}

	return (1);
}

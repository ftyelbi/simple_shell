#include "shell.h"

/**
 * my_getenv - gets the value of an environment variable
 * @shell: shell data struct (shell._environ contains all env data)
 * @name: name of variable to return
 *
 * Return: pointer to the value of env
 */

char *my_getenv(sh_data *shell, char *name)
{
	int a, b, c, d, check;
	char *value;

	for (a = 0; shell->_environ[a]; a++)
	{
		b = 0, check = 0;
		while (shell->_environ[a][b] != '=' && name[b] != '\0')
		{
			if (shell->_environ[a][b] != name[b])
				check = 1;
			b++;
		}
		if (check == 0 && shell->_environ[a][b] == '=')
		{
			for (c = b + 1, d = 0; shell->_environ[a][c]; c++, d++)
				;

			value = malloc(sizeof(char) * (d + 1));

			for (c = b + 1, d = 0; shell->_environ[a][c]; d++, c++)
				value[d] = shell->_environ[a][c];
			value[d] = '\0';
			return (value);
		}
	}

	return (NULL);
}

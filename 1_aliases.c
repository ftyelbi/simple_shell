#include "shell.h"

/**
 * is_alias - handles the alias builtin, sets and prints
 * @shell: pointer to the shell structure
 *
 * Return: 0 on success or appropriate err
 */
int is_alias(sh_data *shell)
{
        int i, j, check, ret = 0;

        if (!shell->arr[1])
        {
                ret = print_a_alias(shell);
        }
        else
        {
                for (i = 1; shell->arr[i]; i++)
                {
                        check = 0;
                        for (j = 0; shell->arr[i][j]; j++
				
					
			if (shell->arr[i][j] == '=')
				{
					check = 1;
					ret = on_alias(shell, shell->arr[i]);
					break;
				}
			}
			if (check == 0)
			ret = print_1_alias(shell, shell->arr[i]);
		}
	}

	return (ret);
}

/**
 * on_alias - creates an alias
 * @shell: pointer to shell structure
 * @arg: of the format: name=value
 *
 * Return: 0 on success
 */
int on_alias(sh_data *shell, char *arg)
{
	char *name, *value, *str;

	str = is_strdup(arg);
	name = is_strtok(str, "=");
	value = is_strtok(NULL, "");

	plus_alias(&shell->alias, name, value);
	if (shell->alias == NULL)
	{
		write(STDERR_FILENO, shell->av[0], is_strlen(shell->av[0]));
		write(STDERR_FILENO, ": Unable to add alias\n", 22);
		free(str);
	return (12);
	}

	free(str);
	return (0);
}

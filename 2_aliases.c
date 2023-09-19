#include "shell.h"

/**
 * _check_alias - checks if a command is an alias
 * @shell: pointer to shell structure
 *
 * Return: void
 */
void _check_alias(sh_data *shell)
{
	alias_l *temp = shell->alias;
	int j, k, len;
	char *command;

	while (temp)
	{
		if (is_strcmp(temp->name, shell->arr[0]) == 0)
		{
			len = is_strlen(temp->value);
			command = malloc(sizeof(char) * (len - 1));

			for (j = 1, k = 0; j < len - 1; j++, k++)
				command[k] = temp->value[j];
			command[k] = '\0';

			free(shell->arr[0]);
			shell->arr[0] = command;
			break;
		}
		temp = temp->next;
	}
}
/**
 * _free_aliases - frees the alias_l linked list
 * @head: pointer to the list
 *
 * Return: non
 */
void _free_aliases(alias_l *head)
{
	alias_l *temp = head, *second;

	if (head)
	{
		while (temp->next)
		{
			second = temp;
			temp = temp->next;
			free(second->name);
			free(second->value);
			free(second);
		}

		free(temp->name);
		free(temp->value);
		free(temp);
	}
}

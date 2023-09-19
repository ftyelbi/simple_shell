#include "shell.h"

/**
 * _expand_var - expands a variable to its corresponding value
 * @shell: pointer to shell structure
 *
 * Return: void
 */
void _expand_var(sh_data *shell)
{
	int a, b, c;
	char *str, *value;

	for (a = 0; shell->arr[a]; a++)
	{
		if (is_strcmp(shell->arr[a], "$$") == 0)
		{
			free(shell->arr[a]);
			str = is_itoa(shell->pid);
			shell->arr[a] = is_strdup(str);
			free(str);
		}
		else if (is_strcmp(shell->arr[a], "$?") == 0)
		{
			free(shell->arr[a]);
			str = is_itoa(shell->status);
			shell->arr[a] = is_strdup(str);
			free(str);
		}
		else if (shell->arr[a][0] == '$')
		{
			str = malloc(sizeof(char) * is_strlen(shell->arr[a]));
			for (b = 1, c = 0; shell->arr[a][b]; b++, c++)
				str[c] = shell->arr[a][b];
			str[c] = '\0';
			value = my_getenv(shell, str);
			if (value == NULL)
			{
				free(value);
				free(str);
			}
			else
			{
				free(shell->arr[a]);
				free(str);
				shell->arr[a] = is_strdup(value);
				free(value);
			}
		}
	}
}

/**
 * _add_node_end - adds a new node at the end of the path_l linked list
 * @head: pointer to the list
 * @str: string to add to the end of the list
 *
 * Return: address of new list
 */
path_l *_add_node_end(path_l **head, char *str)
{
	path_l *list, *temp;

	temp = *head;
	list = malloc(sizeof(path_l));

	if (!list)
		return (NULL);

	list->str = is_strdup(str);
	list->next = NULL;

	if (!temp)
	{
		*head = list;
	}
	else
	{
		while (temp->next)
			temp = temp->next;
		temp->next = list;
	}

	return (*head);
}

/**
 * _path_to_list - creates a linked list of each directory contained in the PATH
 * environment variable
 * @shell: the shell environment's struct
 *
 * Return: a linked list containing the PATH's paths
 */
path_l *_path_to_list(sh_data *shell)
{
	char path[5] = "PATH";
	int i, j, k, check;
	path_l *head = NULL;
	char *str;

	for (i = 0; shell->_environ[i]; i++)
	{
		j = 0, check = 0;
		while (shell->_environ[i][j] != '=' && path[j] != '\0')
		{
			if (shell->_environ[i][j] != path[j])
				check = 1;
			j++;
		} k = 0;
		if (check == 0)
		{
			j++;
			while (shell->_environ[i][j])
			{
				if (shell->_environ[i][j] == ':')
				{
					str[k] = '\0', k = 0;
					_add_node_end(&head, str);
					free(str);
				}
				else
				{
					if (k == 0)
						str = malloc(sizeof(char) * 150);
					str[k] = shell->_environ[i][j], k++;
				} j++;
			} str[k] = '\0';
			_add_node_end(&head, str);
			free(str);
			break;
		}
	} str = my_getenv(shell, "PWD");
	_add_node_end(&head, str);
	free(str);
	return (head);
}

/**
 * _search_path - searches a path linked list to find a particular file
 * @list: pointer to a path list
 * @file: file to search for
 *
 * Return: pointer to full path name of NULL if not found
 */
char *_search_path(path_l *list, char *file)
{
	path_l *temp = list;
	char *path;
	struct stat s;

	while (temp)
	{
		path = malloc(sizeof(char) * (is_strlen(temp->str) + is_strlen(file) + 2));

		if (file[0] == '/')
		{
			free(path);
			if (stat(file, &s) == 0)
			{
				path = is_strdup(file);
				return (path);
			}
			else
				return (NULL);
		}

		is_strcpy(path, temp->str);
		is_strcat(path, "/");
		is_strcat(path, file);
		if (stat(path, &s) == 0)
			return (path);

		free(path);
		temp = temp->next;
	}

	return (NULL);
}

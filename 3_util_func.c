#include "shell.h"

/**
 * _free_list - frees the path_l linked list
 * @head: pointer to the list
 *
 * Return: non
 */
void _free_list(path_l *head)
{
	path_l *temp = head, *second;

	if (head)
	{
		while (temp->next)
		{
			second = temp;
			temp = temp->next;
			free(second->str);
			free(second);
		}

		free(temp->str);
		free(temp);
	}
}
/**
 * _free_arr2 - frees an array of arrays
 * @arr: array name
 * Return: nil
 */
void _free_arr2(char **arr)
{
	int k;

	for (k = 0; arr[k] ; k++)
		free(arr[k]);
	free(arr);
}
/**
 * is_atoi - converts a string to an integer.
 * @s: input string.
 *
 * Return: integer.
 */
int is_atoi(char *s)
{
	unsigned int count = 0, size = 0, oi = 0, pn = 1, m = 1, i;

	while (s[count] != '\0')
	{
		if (size > 0 && (s[count] < '0' || s[count] > '9'))
			break;

		if (s[count] == '-')
			pn *= -1;

		if ((s[count] >= '0') && (s[count] <= '9'))
		{
			if (size > 0)
				m *= 10;
			size++;
		}
		count++;
	}

	for (i = count - size; i < count; i++)
	{
		oi = oi + ((s[i] - 48) * m);
		m /= 10;
	}
	return (oi * pn);
}
/**
 * is_itoa - function converts int to string.
 * @n: type int number
 *
 * Return: String.
 */
char *is_itoa(int n)
{
	unsigned int n1;
	int len = _get_len(n);
	char *buffer;

	buffer = malloc(sizeof(char) * (len + 1));
	if (buffer == 0)
		return (NULL);

	buffer[len] = '\0';

	if (n < 0)
	{
		n1 = n * -1;
		buffer[0] = '-';
	}
	else
	{
		n1 = n;
	}
	len--;

	do

	{
		buffer[len] = (n1 % 10) + '0';
		n1 = n1 / 10;
		len--;
	}
	while (n1 > 0)
		;
	return (buffer);
}
/**
 * _get_len - Get the length of a number.
 * @n: type int number.
 *
 * Return: Length of a number.
 */
int _get_len(int n)
{
	unsigned int n1;
	int len = 1;

	if (n < 0)
	{
		len++;
		n1 = n * -1;
	}
	else
	{
		n1 = n;
	}
	while (n1 > 9)
	{
		len++;
		n1 = n1 / 10;
	}
	return (len);
}

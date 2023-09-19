#include "shell.h"

/**
 * _get_commands - gets a command from the standard input
 * @buffer: a buffer to store the line input by the user (*shell.line)
 * @n: size of buffer (shell.length)
 *
 * Return: an array of split tokens of commands to **shell.arr
 */
char **_get_commands(char *buffer, size_t n)
{
	char **arr = NULL;
	char *token;
	size_t k = 0;
	ssize_t i, r;

	r = _my_getline(&buffer, &n, stdin);
	if (r == -1)
	{
		free(buffer);
		return (arr);
	}
	r = _rm_comments(&buffer);
	if (r == 0)
		return (NULL);
for (i = 0; i < r; i++)
{
	if (buffer[i] == ' ' || buffer[i] == '\n' || buffer[i] == '\t' ||
			buffer[i] == '\r' || buffer[i] == '\a')
	{
		k++;
	}
	else
		continue;
	}
	arr = malloc(sizeof(char *) * (k + 1));
	token = is_strtok(buffer, DELIM_T);
	i = 0;
	while (token != NULL)
	{
		arr[i] = malloc(sizeof(char) * (is_strlen(token) + 1));
		is_strcpy(arr[i], token);
		token = is_strtok(NULL, DELIM_T);
		i++;
	}
	arr[i] = NULL;
	free(buffer);
	return (arr);
}

/**
 * _rm_comments - strips the comments from a command
 * @buffer: the buffer retrieved by my_getline
 *
 * Return: 0 if a # is encountered as the first character, or the length of
 * the new buffer stripped of its comments
 */
int _rm_comments(char **buffer)
{
	int m = 0, n, j = 0;
	char *buf = is_strdup(*buffer);
	char *temp = NULL, prev = 'c';

	for (; buf[m] != '\0'; m++)
	{
		if (m == 0 && buf[m] == '#')
		{
			free(buf);
			return (0);
		}
		if (j == 0 && buf[m] == '#')
		{
			free(buf);
			return (0);
		}
		if (buf[m] != ' ' && buf[m] != '\t')
			j++;
		if (prev == ' ' && buf[m] == '#')
			break;

		prev = buf[m];
	}
	if (m == is_strlen(*buffer))
	{
		free(buf);
		return (m);
	}
	temp = malloc(sizeof(char) * (m + 2));
	for (n = 0; buf[n] != '#'; n++)
		temp[n] = buf[n];
	temp[n] = '\n';
	temp[n + 1] = '\0';
	free(*buffer);
	*buffer = temp;
	free(buf);

	return (m + 1);
}

/**
 * _insert_line - inserts the buffer into the lineptr
 * @lineptr: the address passed into getline(char **buffer aka shell.line)
 * @buffer: buffer from read call
 * @n: size of line
 * @size: size of buffer
 *
 * Return: nil
 */
void _insert_line(char **lineptr, size_t *n, char *buffer, size_t size)
{
	if (*lineptr == NULL || *n < size)
	{
		if (size > BUFSIZE)
			*n = size;
		else
			*n = BUFSIZE;
		*lineptr = buffer;
	}
	else
	{
		is_strcpy(*lineptr, buffer);
		free(buffer);
	}
}

/**
 * _my_getline - gets a line of input from a stream/file descriptor
 * @buffer: address of buffer
 * @n: pointer to size of buffer
 * @stream: the stream to read data from
 *
 * Return: number of characters read
 */
ssize_t _my_getline(char **buffer, size_t *n, FILE *stream)
{
	int fd;
	char *buf, c = 'c';
	static ssize_t input;
	ssize_t r;
	size_t size;

	if (input == 0)
		fflush(stream);

	buf = malloc(sizeof(char) * BUFSIZE);
	if (!buf)
		return (-1);

	fd = fileno(stream);
	while (c != NEWLINE)
	{
		r = read(fd, &c, 1);
		if ((r == 0 && input == 0) || r == -1)
		{
			free(buf);
			return (-1);
		}
		if (r == 0 && input != 0)
		{
			input++;
			break;
		}
		if (input >= BUFSIZE)
		{
			buf = is_realloc(buf, input, input + 1);
		}
		buf[input] = c;
		input++;
	}
	buf[input] = '\0';
	_insert_line(buffer, n, buf, input);
	size = input;
	if (r != 0)
		input = 0;
	return (size);
}

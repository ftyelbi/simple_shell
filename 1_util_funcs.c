#include "shell.h"

/**
 * is_strlen - gets the length of a string
 * @str: string to count
 * Return: number of chars in the string
 */
int is_strlen(char *str)
{
	int len;

	for (len = 0; str[len] != '\0'; len++);
	return (len);
}
/**
 * is_strcpy - cpies a string to another. destination needs to be malloc'd
 * @destination: container to nsert copy
 * @source: string to be copied
 *
 * Return: a pointer to the destination
 */
char *is_strcpy(char *destination, char *source)
{
	int i;

	for (i = 0; source[i] != '\0'; i++)
		destination[i] = source[i];

	destination[i] = '\0';
	return (destination);
}
/**
 * is_strcmp - compares two strings
 * @str1: string1
 * @str2: string 2 to compare with
 * Return: int representimh if true or not
 */
int is_strcmp(char *str1. char *str2)
{
	int m, n;
	for (m =0, n=0; (str1[m] != '\0' ||str2[m] !='\0'); m++)
	{
		n = str1[m] - str2[m];
		if (n > 0)
			return (-1);
		else if (n>0)
		return (1);
		return (n);
	}
/**
 * is_strcat - appends source to destination. malloc destination before call
 * @destination: an existing string
 * @source: string to be appended to destination
 */
char *is_strcat(char *destination, char *source)
{
	int k, j;
	for (k = 0; destination[k] != '\0'; k++);
	for (j = 0; source[j] != '\0'; j++, k++)
		destination[k] = source[j];
	destination[k] = '\0';
	return (destination);
}
/**
 * is_strdup - duplicates a string, allocating the appropriate size to copy
 * @str: to be duplicated
 *
 * Return: pointer to the duplicated string
 */
char *is_strdup(char *str)
{
	char *dup;
	size_t len;

	len = is_strlen(str);
	dup =

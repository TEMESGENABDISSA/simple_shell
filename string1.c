#include "shell.h"

/**
 * _strcpy - copy str
 * @dest:  destinations
 * @src:  src
 *  author: temesgen abdissa and amanuel dessalegn
 * Return: point to the  destinations
 */
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

/**
 * _strdup - replicate a str
 * @str:  str to replicate
 * author : temesgen abdissa and amnuels dessalegn
 * Return: point  to the replicate string
 */
char *_strdup(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
}

/**
 *_puts - displays  input str
 *@str:  string to displayed
 * author : temesgen abdissa and amanuel dessalegn
 * Return: returns void or  Nothing
 */
void _puts(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
}

/**
 * _putchar - notes the char c to stdout
 * @c:  char to display
 * author: temesgen abdissa and amanuel dessalegn
 * Return: print 1. to show success
 * On error, -1 is returns, and errno is set proportionately .
 */
int _putchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

#include "shell.h"

/**
 *_eputs -  Prints the specified string to standard error.
 * @str: The string(str) to be printed.
 *
 * Return: None
 */
void _eputs(char *str)
{
	int A = 0;

	if (!str)
		return;
	while (str[A] != '\0')
	{
		_eputchar(str[A]);
		A++;
	}
}

/**
 * _eputchar - Writes the specified character to standard error.
 * @c: The c character to be writte
 *
 * Return: On success, returns 1. 
 * On error, returns -1 and sets errno appropriately.
 */
int _eputchar(char c)
{
	static int A;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || A >= WRITE_BUF_SIZE)
	{
		write(2, buf, A);
		A = 0;
	}
	if (c != BUF_FLUSH)
		buf[A++] = c;
	return (1);
}

/**
 * _putfd - Writes character to the specified file descriptor.
 * @c: The character to be written.
 * @fd: The filedescriptor to write to
 *
 * Return: On success, returns 1. 
 * On error, returns -1 and sets errno appropriately..
 */
int _putfd(char c, int fd)
{
	static int A;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || A >= WRITE_BUF_SIZE)
	{
		write(fd, buf, A);
		A = 0;
	}
	if (c != BUF_FLUSH)
		buf[A++] = c;
	return (1);
}

/**
 *_putsfd - Writes str  to the specified file descriptor.
 * @str: the string(STR) to be printed
 * @fd: the filedescriptor to write to
 *
 * Return: The number of characters written.
 */
int _putsfd(char *str, int fd)
{
	int A = 0;

	if (!str)
		return (0);
	while (*str)
	{
		A += _putfd(*str++, fd);
	}
	return (A);
}

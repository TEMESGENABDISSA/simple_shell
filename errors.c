#include "shell.h"

/**
 *_eputs - display an input str
 * @str: A str to  print
 * author: temesgen abdissa and amanuel dessalegn
 * Return:  returns nothing 0
 */
void _eputs(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_eputchar(str[i]);
		i++;
	}
}

/**
 * _eputchar - draw a char c for  stderr
 * @c: character to display
 * Author:temesgen abdissa and amanuel dessalegn
 * Return:  1 to indicate sucess
 *  -1 is toindicate error,and  errno is set appropriately.
 */
int _eputchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _putfd - draw  char c for a given fd
 * @c:  char to display
 * @fd:  filedescriptor to draw
 * author: temesgenabdissa and amanuel dessalegn
 * Return:  1. to indicate success
 * -1 is toindicate error,and  errno is set appropriately.
 */
int _putfd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}
/**
 *_putsfd - print to  input str
 * @str:  str to displayed
 * @fd: the filedescriptor to write to
 * author: temesgen abdissa and amanuel dessalegn
 * Return:  num of char to put
 */
int _putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _putfd(*str++, fd);
	}
	return (i);
}

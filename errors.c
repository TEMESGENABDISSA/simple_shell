#include "shell.h"
/**
 * Prints the specified string to standard error.
 *
 * @param str The string to be printed.
 *
 * @return None.
 */
void _eputs(char *str)
{
    int i = 0;

    if (!str) {
        return;
    }

    while (str[i] != '\0') {
        _eputchar(str[i]);
        i++;
    }
}
/**
 * Writes the specified character to standard error.
 *
 * @param c The character to be written.
 *
 * @return On success, returns 1. On error, returns -1 and sets errno appropriately.
 */
int _eputchar(char c)
{
    static int i;
    static char buf[WRITE_BUF_SIZE];

    if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE) {
        write(STDERR_FILENO, buf, i);
        i = 0;
    }

    if (c != BUF_FLUSH) {
        buf[i++] = c;
    }

    return 1;
}
/**
 * Writes the specified character to the specified file descriptor.
 *
 * @param c The character to be written.
 * @param fd The file descriptor to write to.
 *
 * @return On success, returns 1. On error, returns -1 and sets errno appropriately.
 */
int _putfd(char c, int fd)
{
    static int i;
    static char buf[WRITE_BUF_SIZE];

    if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE) {
        write(fd, buf, i);
        i = 0;
    }

    if (c != BUF_FLUSH) {
        buf[i++] = c;
    }

    return 1;
}
/**
 * Writes the specified string to the specified file descriptor.
 *
 * @param str The string to be printed.
 * @param fd The file descriptor to write to.
 *
 * @return The number of characters written.
 */
int _putsfd(char *str, int fd)
{
    int i = 0;

    if (!str) {
        return 0;
    }

    while (*str) {
        i += _putfd(*str++, fd);
    }

    return i;
}

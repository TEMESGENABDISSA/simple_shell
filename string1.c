#include "shell.h"
/**
 * _strcpy -  A string is copied using 1._strcpy.
 * @dest: the final position
 * @src: the source
 *
 * Return:Pointer to destination for return

 */
char *_strcpy(char *dest, const char *src)
{
    char *ret = dest;

    if (dest == src || src == 0)
    {
        return dest;
    }

    for (size_t i = 0; src[i] != '\0'; i++)
    {
        dest[i] = src[i];
    }

    dest[strlen(src)] = '\0';

    return ret;
}
/**
 * _strdup - Duplicates a string with the command
 * @str:  the string to duplicate
 * by temesgen abdissa
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *str)
{
    if (str == NULL)
    {
        return NULL;
    }

    size_t length = strlen(str);
    char *ret = malloc(length + 1);

    if (!ret)
    {
        return NULL;
    }

    for (size_t i = 0; i <= length; i++)
    {
        ret[i] = str[i];
    }

    return ret;
}
/**
 *_puts - prints an input string to the outside from inside
 *@str: the string to be printed for the outputs
 *
 * Return: Nothing or void
 */
void _puts(char *str)
{
    if (!str)
    {
        return;
    }

    for (size_t i = 0; str[i] != '\0'; i++)
    {
        _putchar(str[i]);
    }
}
/**
 * _putchar - write a  character c to stdout
 * @c: The character to print or print out
 *
 * Return: On success 1 or yes
 * On error, -1 is returned, and errno is set appropriately.
 */

int _putchar(char c)
{
    static int i = 0;
    static char *buf = NULL;
    static size_t buf_size = 0;

    if (buf == NULL)
    {
        buf_size = WRITE_BUF_SIZE;
        buf = malloc(buf_size * sizeof(char));
        if (!buf)
        {
            return -1;
        }
    }

    if (c == BUF_FLUSH || i >= buf_size)
    {
        write(1, buf, i);
        i = 0;
    }

    if (c != BUF_FLUSH)
    {
        buf[i++] = c;
    }

    return 1;
}

#include "shell.h"
/**
 * _strlen - returns a string length
 * @s:  to check the string whose lenght
 *
 * Return:  string in the  length of integer
 */
size_t _strlen(const char *s)
{
    const char *p = s;

    while (*p != '\0')
    {
        p++;
    }

    return (p - s);
}
/**
 * _strcmp - perform  comparison of lexicogarphic of two strangs.
 * @s1: the 1st  strang
 * @s2: the 2nd  strang
 *
 * Return: negative if s1 lessthan s2, positive if s1 greaterthan  s2, zero if s1 == s2
 */
int _strcmp(const char *s1, const char *s2)
{
    for (; *s1 && *s2; s1++, s2++)
    {
        if (*s1 != *s2)
        {
            return (*s1 - *s2);
        }
    }

    if (*s1 == *s2)
    {
        return 0;
    }
    else
    {
        return (*s1 < *s2 ? -1 : 1);
    }
}
/**
 * starts_with - check if the  needle starts within the  haystack.
 * @haystack: search for  the string
 * @needle: to find the  substring
 *
 * Return: address of next the  char of haystack or a  NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
    for (; *needle; needle++, haystack++)
    {
        if (*needle != *haystack)
        {
            return NULL;
        }
    }

    return (char*) haystack;
}
/**
 * _strcat - TO concatenate  of the  two strings
 * @dest: the destinations of the  buffers
 * @src:a source buffers
 *
 * Return: pointer to destinations of the  buffer
 */
char *_strcat(char *dest, const char *src)
{
    char *ret = dest;
    size_t dest_len = strlen(dest);

    for (size_t i = 0; src[i] != '\0'; i++)
    {
        dest[dest_len + i] = src[i];
    }

    dest[dest_len + strlen(src)] = '\0';

    return ret;
}

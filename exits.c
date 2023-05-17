#include "shell.h"
/**
 * Copies the specified number of characters from the source string to the destination string.
 *
 * @param dest The destination string to copy to.
 * @param src The source string to copy from.
 * @param n The number of characters to copy.
 *
 * @return A pointer to the destination string.
 */
char *_strncpy(char *dest, const char *src, size_t n)
{
    size_t i;

    for (i = 0; i < n && src[i] != '\0'; i++) {
        dest[i] = src[i];
    }

    if (i < n) {
        dest[i] = '\0';
    }

    return dest;
}
/**
 * Concatenates the specified number of bytes from the source string to the end of the destination string.
 *
 * @param dest The first string to concatenate.
 * @param src The second string to concatenate.
 * @param n The maximum number of bytes to concatenate.
 *
 * @return A pointer to the concatenated string.
 */
char *_strncat(char *dest, const char *src, size_t n)
{
    size_t dest_len = strlen(dest);
    size_t i;

    for (i = 0; i < n && src[i] != '\0'; i++) {
        dest[dest_len + i] = src[i];
    }

    dest[dest_len + i] = '\0';

    return dest;
}
/**
 * Locates the first occurrence of the specified character in the string.
 *
 * @param s The string to search.
 * @param c The character to look for.
 *
 * @return A pointer to the first occurrence of the character in the string, or NULL if the character is not found.
 */
char *_strchr(const char *s, int c)
{
    while (*s != '\0') {
        if (*s == c) {
            return (char *)s;
        }
        s++;
    }

    if (c == '\0') {
        return (char *)s;
    }

    return NULL;
}

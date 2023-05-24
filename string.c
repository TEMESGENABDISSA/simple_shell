#include "shell.h"

/**
 * _strlen - displays  length of str
 * @s:  str  length to check
 * author : temesgen abdissa and amanuel dessalegn
 * Return:  returns int length for  the  str
 */
int _strlen(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}

/**
 * _strcmp - perform  lexicogarphic compare of 2 str.
 * @s1: first strings
 * @s2: second strings
 * author: temesgen abdissa and amanuel dessalegn
 * Return: returns -ve if s1 < s2 and +ve if s1 > s2 else  0 if s1 == s2
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - check  needle if start withhaystack
 * @haystack: str to search
 * @needle:  substring to find
 * author: temesgen abdissa and amanuel dessalegn
 * Return: address of the next char haystack or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - concatenated 2 strs
 * @dest: destinations  buffer
 * @src:  src buffer
 * author: temesgen abdissa and amanuel dessalegn
 * Return: point destinations buffer
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}

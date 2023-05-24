#include "shell.h"

/**
 **_memset - fill the  memory a constant byte
 *@s:  point to  memory area
 *@b:  byte to fill *s with
 *@n:  amount of bytes to  filled
 *Return: (s) a point to  memory area s
 * author: temesgen abdissa and amanuel dessalegn
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * ffree - free  str of the str
 * @pp: string of the  string
 * author: temesgen abdissa and amanuel dessalegn
 */
void ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * _realloc - reallocate block of the  memories
 * @ptr: point  to previous malloc'ated bl
 * @old_size: byte size of the  previous bl
 * @new_size: byte size of the  new bl
 * author : temesgen Abdissa and Amanuel dessalegn
 * Return: point for  da ol'block nameen.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}

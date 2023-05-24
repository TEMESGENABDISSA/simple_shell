#include "shell.h"

/**
 * bfree - clear point to  NULLs address
 * @ptr: address the pointerto  free
 * author: temesgen abdissa and amanuel dessalegn
 * Return: returns  1 if its  free and else 0.
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}

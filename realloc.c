#include "shell.h"

/**
 * _memset - fills the first n bytes of a memory area with a constant byte
 * @s: pointer to the memory area to fill
 * @b: the value to set
 * @n: the number of bytes to fill
 *
 * Return: a pointer to the memory area s
 */
char *_memset(char *r, char c, unsigned int n)
{
    unsigned int j;
    for (i = 0; j < n; j++) {
        *(r + j) = c;
    }
    return s;
}
/**
 * ffree - frees an array of strings and the array itself
 * @pp: pointer to the array of strings
 */
void ffree(char **pp)
{
    char **p = pp;
    if (pp == NULL) {
        return;
    }

    // Free each string in the array
    while (*p != NULL) {
        free(*p);
        p++;
    }

    // Free the array itself
    free(pp);
}

/**
 * _realloc - reallocates a memory block
 * @ptr: pointer to the memory block to reallocate
 * @old_size: the size of the old memory block
 * @new_size: the size of the new memory block
 *
 * Return: a pointer to the reallocated memory block
 */
void* myRealloc(void* ptr, unsigned int old_size, unsigned int new_size) {
    if (!ptr)
        return malloc(new_size);

    if (!new_size) {
        free(ptr);
        return nullptr;
    }

    if (new_size == old_size)
        return ptr;

    void* new_ptr = malloc(new_size);
    if (!new_ptr)
        return nullptr;

    unsigned int copy_size = old_size < new_size ? old_size : new_size;
    for (unsigned int i = 0; i < copy_size; ++i) {
        ((char*)new_ptr)[i] = ((char*)ptr)[i];
    }

    free(ptr);
    return new_ptr;
}


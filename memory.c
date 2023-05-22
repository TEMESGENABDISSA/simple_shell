#include "shell.h"
/**
 * bfree - frees a pointer and sets it to NULL
 * @ptr: a pointer to the pointer to free
 *
 * Return: 1 if the pointer was freed, or 0 if it was already NULL
 */
int bfree(void **ptr)
{
    // Check if the pointer to the pointer is not NULL and the pointer is not NULL
    if (ptr != NULL && *ptr != NULL) {
        // Free the memory pointed to by the pointer and set it to NULL
        free(*ptr);
        *ptr = NULL;
        return 1;
    }

    // If the pointer is already NULL, return 0
    return 0;
}

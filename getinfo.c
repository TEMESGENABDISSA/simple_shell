#include "shell.h"
/**
 * Initializes the fields of an info_t struct.
 *
 * @param info Pointer to the info_t struct to initialize.
 */
void clear_info(info_t *info)
{
info->arg = NULL;
info->argv = NULL;
info->path = NULL;
info->argc = 0;
}
/**
 * Initializes the fields of an info_t struct based on the given argument vector.
 *
 * @param info Pointer to the info_t struct to initialize.
 * @param av The argument vector to use for initialization.
 */
void set_info(info_t *info, char **av) {
    info->fname = av[0];

    if (info->arg) {
        // split argument string into argv array
        info->argv = split_string(info->arg, " \t");
        if (!info->argv) {
            // allocate a single-element argv array with the argument string
            info->argv = malloc(sizeof(char *));
            if (info->argv) {
                info->argv[0] = _strdup(info->arg);
                info->argv[1] = NULL;
            }
        }
        info->argc = count_elements(info->argv);

        // replace aliases and variables in the argv array
        replace_aliases(info);
        replace_vars(info);
    }
}
/**
 * Frees the dynamically allocated fields of an info_t struct.
 *
 * @param info Pointer to the info_t struct to free.
 * @param all True if all fields should be freed, false if only some fields should be freed.
 */
void free_info(info_t *info, int all) {
    // free dynamically allocated fields
    ffree(info->argv);
    ffree(info->environ);
    bfree((void **)info->cmd_buf);

    // clear non-dynamically allocated fields
    info->argv = NULL;
    info->path = NULL;
    info->environ = NULL;
    info->cmd_buf = NULL;

    if (all) {
        // free dynamically allocated lists
        free_list(&(info->env));
        free_list(&(info->history));
        free_list(&(info->alias));

        // free argument string if command buffer is not being used
        if (!info->cmd_buf) {
            free(info->arg);
            info->arg = NULL;
        }

        // close read file descriptor and flush buffer
        if (info->readfd > 2) {
            close(info->readfd);
        }
        _putchar(BUF_FLUSH);
    }
}

#include "shell.h"
/**
 * Displays the shell command history, one command per line, with line numbers starting at 0.
 *
 * @param info A structure containing potential arguments. Used to maintain a constant function prototype.
 *
 * @return Always returns 0.
 */
int _myhistory(info_t *info)
{
print_list(info->history);
return (0);
}
/**
 * Unsets an alias with the given name.
 *
 * @param info A parameter struct.
 * @param str The name of the alias to unset.
 *
 * @return Always returns 0 on success, 1 on error.
 */
int unset_alias(info_t *info, char *str)
{
    char *p = _strchr(str, '=');
    char c;
    int ret;

    if (!p) {
        return 1;
    }

    c = *p;
    *p = '\0';

    ret = delete_node_at_index(&(info->alias),
                               get_node_index(info->alias, node_starts_with(info->alias, str, -1)));

    *p = c;

    return ret;
}

/**
 * Sets an alias with the given name and value.
 *
 * @param info A parameter struct.
 * @param str The name and value of the alias, in the form "name=value".
 *
 * @return Always returns 0 on success, 1 on error.
 */
int set_alias(info_t *info, char *str)
{
    char *p = _strchr(str, '=');

    if (!p) {
        return 1;
    }

    if (!*++p) {
        return unset_alias(info, str);
    }

    unset_alias(info, str);

    return add_node_end(&(info->alias), str, 0) == NULL;
}
/**
 * Prints the name and value of an alias.
 *
 * @param node The node containing the alias name and value.
 *
 * @return Always returns 0 on success, 1 on error.
 */
int print_alias(list_t *node)
{
    char *p = NULL, *a = NULL;

    if (node != NULL) {
        p = _strchr(node->str, '=');

        for (a = node->str; a <= p; a++) {
            _putchar(*a);
        }

        _putchar('\'');
        _puts(p + 1);
        _puts("'\n");

        return 0;
    }

    return 1;
}
/**
 * Implements the alias command, which sets or displays command aliases.
 *
 * @param info A structure containing potential arguments. Used to maintain a constant function prototype.
 *
 * @return Always returns 0.
 */
int _myalias(info_t *info)
{
    int i;
    char *p;
    list_t *node;

    if (info->argc == 1) {
        node = info->alias;

        while (node) {
            print_alias(node);
            node = node->next;
        }

        return 0;
    }

    for (i = 1; info->argv[i] != NULL; i++) {
        p = _strchr(info->argv[i], '=');

        if (p) {
            set_alias(info, info->argv[i]);
        } else {
            print_alias(node_starts_with(info->alias, info->argv[i], '='));
        }
    }

    return 0;
}

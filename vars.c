#include "shell.h"
/**
 * is_chain - check  if current char in the  buffer is a chain delimeter
 * @info: a parameter is the struct
 * @buf: the char buffer
 * @p: address of the  current position in the buf
 *
 * Return:  if chain delimeter one, otherwise  zero
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
    if (!info || !buf || !p || *p >= strlen(buf)) {
        return 0;
    }

    char c = buf[*p];
    size_t j = *p;

    if (c == '|' && buf[j + 1] == '|') {
        buf[j] = '\0';
        *p = ++j;
        info->cmd_buf_type = CMD_OR;
        return 1;
    } else if (c == '&' && buf[j + 1] == '&') {
        buf[j] = '\0';
        *p = ++j;
        info->cmd_buf_type = CMD_AND;
        return 1;
    } else if (c == ';') {
        buf[j] = '\0';
        *p = ++j;
        info->cmd_buf_type = CMD_CHAIN;
        return 1;
    } else {
        return 0;
    }
}
/**
 * check_chain - identifies  we should continue chaining based onthe  last status
 * @info: the parameter of the  struct
 * @buf: the char of the  buffer
 * @p: address of the  current position in the  buf
 * @i: starting position in the  buf
 * @len: length of the  buf
 *
 * Return: Void or nothing
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
    if (!info || !buf || !p || i >= len) {
        return;
    }

    size_t j = *p;

    switch (info->cmd_buf_type) {
        case CMD_AND:
            if (info->status) {
                buf[i] = '\0';
                j = len;
            }
            break;
        case CMD_OR:
            if (!info->status) {
                buf[i] = '\0';
                j = len;
            }
            break;
        default:
            break;
    }

    *p = j;
}
/**
 * replace_alias - replaces  aliases in the tokenized string
 * @info: the parameter is  struct
 *
 * Return:  if replaced 1, 0 otherwise
 */
int replace_alias(info_t *info)
{
    if (!info || !info->alias || !info->argv[0]) {
        return 0;
    }

    list_t *node = node_starts_with(info->alias, info->argv[0], '=');
    if (!node) {
        return 0;
    }

    char *alias_value = strchr(node->str, '=') + 1;
    char *replacement = strdup(alias_value);
    if (!replacement) {
        return 0;
    }

    free(info->argv[0]);
    info->argv[0] = replacement;

    return 1;
}
/**
 * replace_vars - replaces vars in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(info_t *info)
{
    if (!info) {
        return 0;
    }

    for (int i = 0; info->argv[i]; i++) {
        char* arg = info->argv[i];
        if (arg[0] == '$' && arg[1]) {
            if (strcmp(arg, "$?") == 0) {
                char* status_str = convert_number(info->status, 10, 0);
                if (!status_str) {
                    return 0;
                }
                replace_string(&info->argv[i], status_str);
                free(status_str);
            } else if (strcmp(arg, "$$") == 0) {
                char* pid_str = convert_number(getpid(), 10, 0);
                if (!pid_str) {
                    return 0;
                }
                replace_string(&info->argv[i], pid_str);
                free(pid_str);
            } else {
                char* env_var = getenv(arg + 1);
                if (env_var) {
                    replace_string(&info->argv[i], strdup(env_var));
                } else {
                    replace_string(&info->argv[i], strdup(""));
                }
            }
        }
    }

    return 1;
}
/**
 * replace_string - replaces string
 * @old_str: address of old string
 * @new_str: new string
 *
 * Return: true if replaced, false otherwise
 */
bool replace_string(char **old_str, const char *new_str)
{
    if (!old_str || !new_str) {
        return false;
    }

    char *temp = strdup(new_str);
    if (!temp) {
        return false;
    }

    free(*old_str);
    *old_str = temp;

    return true;
}

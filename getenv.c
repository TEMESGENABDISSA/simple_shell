#include "shell.h"
/**
 * Returns a copy of the environment variable strings as an array of strings.
 *
 * @param info Structure containing potential arguments. Used to maintain constant function prototype.
 *
 * @return A pointer to an array of strings containing the environment variable strings.
 */
char **get_environ(const info_t *info) {
    if (!info->environ || info->env_changed) {
        info->environ = convert_env_list_to_array(info->env);
        info->env_changed = false;
    }
    return info->environ;
}
/**
 * Removes the specified environment variable.
 *
 * @param info Structure containing potential arguments. Used to maintain constant function prototype.
 * @param var The name of the environment variable to remove.
 *
 * @return 1 if the environment variable was successfully removed, 0 otherwise.
 */
int _unsetenv(info_t *info, const char *var) {
    list_t *node = info->env;
    size_t index = 0;
    int env_changed = 0;

    if (!node || !var) {
        return 0;
    }

    while (node) {
        const char *p = strstr(node->str, var);
        if (p == node->str && *(p + strlen(var)) == '=') {
            env_changed = delete_node_at_index(&(info->env), index);
            break;
        }
        node = node->next;
        index++;
    }

    info->env_changed |= env_changed;
    return env_changed;
}
/**
 * _setenv - Initializes a new environment variable or modifies an existing one.
 *
 * @info: Structure containing potential arguments. Used to maintain a constant function prototype.
 * @var: The string representing the environment variable property.
 * @value: The string representing the environment variable value.
 *
 * Return: Always 0.
 */  

int _setenv(info_t *info, const char *var, const char *value) {
    char *env_str = NULL;
    list_t *node = info->env;

    if (!var || !value) {
        return 0;
    }

    // construct the new environment variable string
    size_t env_str_len = strlen(var) + 1 + strlen(value);
    env_str = malloc(env_str_len + 1);
    if (!env_str) {
        return 1;
    }
    snprintf(env_str, env_str_len + 1, "%s=%s", var, value);

    // find the node with the same environment variable name, if it exists
    while (node) {
        const char *p = strstr(node->str, var);
        if (p == node->str && *(p + strlen(var)) == '=') {
            // update the existing environment variable
            free(node->str);
            node->str = env_str;
            info->env_changed = true;
            return 0;
        }
        node = node->next;
    }

    // add the new environment variable to the end of the list
    add_node_end(&(info->env), env_str, 0);
    info->env_changed = true;
    return 0;
}

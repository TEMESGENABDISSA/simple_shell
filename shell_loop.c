#include "shell.h"
/**
 * The `hsh` function is the main loop of the shell program.
 *
 * @param info - a structure containing information about the shell
 * @param av - the argument vector from `main()`
 *
 * @return 0 on success, 1 on error, or an error code
 */
int hsh(info_t *info, char **av)
{
    int builtin_ret = 0;

    for (ssize_t r = 0; r != -1 && builtin_ret != -2; clear_info(info))
    {
        if (interactive(info))
            _puts("$ ");

        _eputchar(BUF_FLUSH);
        r = get_input(info);

        if (r != -1)
        {
            set_info(info, av);
            builtin_ret = find_builtin(info);
            if (builtin_ret == -1)
                find_cmd(info);
        }
        else if (interactive(info))
        {
            _putchar('\n');
        }

        free_info(info, 0);
    }

    write_history(info);
    free_info(info, 1);

    if (!interactive(info) && info->status)
        exit(info->status);

    if (builtin_ret == -2)
    {
        if (info->err_num == -1)
            exit(info->status);
        exit(info->err_num);
    }

    return builtin_ret;
}
/**
 * This function finds a builtin command and executes it if found.
 *
 * @param info - a struct containing information about the command and its arguments
 * * @return -1 if the builtin command is not found, 
 * 0 if the builtin command executed successfully,
 *          1 if the builtin command was found but not executed successfully, and 
 *          2 if the builtin commandsignals an exit.
 */

int find_builtin(info_t *info)
{
    int builtin_ret = -1;

    switch (hash(info->args[0]))
    {
        case HASH_EXIT:
            builtin_ret = _myexit(info);
            break;
        case HASH_ENV:
            builtin_ret = _myenv(info);
            break;
        case HASH_HELP:
            builtin_ret = _myhelp(info);
            break;
        case HASH_HISTORY:
            builtin_ret = _myhistory(info);
            break;
        case HASH_SETENV:
            builtin_ret = _mysetenv(info);break;
        case HASH_UNSETENV:
            builtin_ret = _myunsetenv(info);
            break;
        case HASH_CD:
            builtin_ret = _mycd(info);
            break;
        case HASH_ALIAS:
            builtin_ret = _myalias(info);
            break;
        default:
            break;
    }

    return builtin_ret;
}
/**
 * find_cmd - found  a command in the  PATH
 * @info: the parameters and  return info struct
 *
 * Return: a  void or nothing 
 */
void find_cmd(info_t *info)
{
    char *path = NULL;
    int arg_count = count_args(info->args);

    if (arg_count == 0)
    {
        return;
}

    if (info->linecount_flag)
    {
        info->line_count++;
        info->linecount_flag = 0;
    }

    path = find_executable(info->args[0], info->env_path);
    if (path == NULL)
    {
        if (is_absolute_path(info->args[0]))
        {
            print_error(info, "Permission denied\n");
        }
        else
        {
            print_error(info, "%s: command not found\n", info->args[0]);
        }

        info->status = 127;
    }
    else
    {
        info->path = path;
        fork_cmd(info);
 }
}
/**
 * fork_cmd - fork  an exec threads to run command
 * @info: a parameters and  returns to  info struct
 *
 * Return: void or nothing
 */
void fork_cmd(info_t *info)
{
    pid_t pid = fork();

    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        char **envp = get_envp(info->env);
        execvp(info->args[0], info->args);
        perror("execvp");
        free_str_array(envp);
        exit(EXIT_FAILURE);
 }
    else
    {
        int status;
        waitpid(pid, &status, 0);
        info->status = WIFEXITED(status) ? WEXITSTATUS(status) : EXIT_FAILURE;

        if (info->status == 126)
        {
            print_error(info, "Permission denied\n");
        }
    }
}

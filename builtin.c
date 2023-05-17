#include "shell.h"
/**
 * Exits the shell with a given exit status.
 *
 * @param info A structure containing potential arguments. Used to maintain a constant function prototype.
 *
 * @return An exit status of 0 if info.argv[0] is not equal to "exit".
 */
int _myexit(info_t *info)
{
    int exit_code = 0;

    if (info->argv[1] != NULL) {
        exit_code = _erratoi(info->argv[1]);

        if (exit_code == -1) {
            info->status = 2;
            print_error(info, "Illegal number: ");
            _eputs(info->argv[1]);
            _eputchar('\n');
            return 1;
        }

        info->err_num = exit_code;
        return -2;
    }

    info->err_num = -1;
    return -2;
}
/**
 * Changes the current directory of the process.
 *
 * @param info A structure containing potential arguments. Used to maintain a constant function prototype.
 *
 * @return Always returns 0.
 *
 */
int _mycd(info_t *info)
{
    char *s, *dir, buffer[1024];
    int chdir_ret;

    s = getcwd(buffer, 1024);
    if (!s) {
        _puts("TODO: >>getcwd failure emsg here<<\n");
    }

    if (!info->argv[1]) {
        dir = _getenv(info, "HOME=");

        if (!dir) {
            chdir_ret = chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
        } else {
            chdir_ret = chdir(dir);
        }
    } else if (_strcmp(info->argv[1], "-") == 0) {
        if (!_getenv(info, "OLDPWD=")) {
            _puts(s);
            _putchar('\n');
            return 1;
        }

        _puts(_getenv(info, "OLDPWD="));
        _putchar('\n');

        chdir_ret = chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
    } else {
        chdir_ret = chdir(info->argv[1]);
    }

    if (chdir_ret == -1) {
        print_error(info, "can't cd to ");
        _eputs(info->argv[1]);
        _eputchar('\n');
    } else {
        _setenv(info, "OLDPWD", _getenv(info, "PWD="));
        _setenv(info, "PWD", getcwd(buffer, 1024));
    }

    return 0;
}
/**
 * Provides help information for the shell.
 *
 * @param info A structure containing potential arguments. Used to maintain a constant function prototype.
 *
 * @return Always returns 0.
 */
int _myhelp(info_t *info)
{
    char **arg_array = info->argv;

    _puts("help call works. Function not yet implemented \n");

    if (0) {
        _puts(*arg_array); /* temp att_unused workaround */
    }

    return 0;
}

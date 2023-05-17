#include "shell.h"
/**
 * Reads input from the user and buffers chained commands.
 *
 * @param info Pointer to the parameter struct.
 * @param buf Address of the buffer for storing input.
 * @param len Address of the variable for storing the length of the input.
 *
 * @return The number of bytes read from the user.
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len) {
    ssize_t r = 0;
    size_t len_p = 0;

    if (*len == 0) {
        // free buffer and set to NULL
        free(*buf);
        *buf = NULL;

        // set SIGINT handler and read input from user
        signal(SIGINT, sigintHandler);
        #if USE_GETLINE
        r = getline(buf, &len_p, stdin);
        #else
        r = _getline(info, buf, &len_p);
        #endif

        if (r > 0) {
            // remove trailing newline and build history list
            if ((*buf)[r - 1] == '\n') {
                (*buf)[r - 1] = '\0';
                r--;
            }
            info->linecount_flag = 1;
            remove_comments(*buf);
            build_history_list(info, *buf, info->histcount++);

            // check if input is a command chain
            if (strchr(*buf, ';') != NULL) {
                *len = r;
                info->cmd_buf = buf;
            }
        }
    }

    return r;
}
/**
 * Reads a line of input from the user and removes the trailing newline.
 *
 * @param info Pointer to the parameter struct.
 *
 * @return The number of bytes read from the user, excluding the trailing newline.
 */
ssize_t get_input(info_t *info) {
    static char *buf = NULL;
    static size_t i = 0, len = 0;
    ssize_t r = 0;
    char **buf_p = &(info->arg);

    _putchar(BUF_FLUSH);

    r = input_buf(info, &buf, &len);
    if (r == -1) {  // EOF
        return -1;
    }

    if (len > 0) {  // we have commands left in the chain buffer
        size_t j = i;
        char *p = buf + i;
        check_chain(info, buf, &j, i, len);

        while (j < len) {  // iterate to semicolon or end
            if (is_chain(info, buf, &j)) {
                break;
            }
            j++;
        }

        i = j + 1;  // increment past nulled ';'

        if (i >= len) {  // reached end of buffer
            i = len = 0;  // reset position and length
            info->cmd_buf_type = CMD_NORM;
        }

        *buf_p = p;  // pass back pointer to current command position
        return _strlen(p);  // return length of current command
    }

    *buf_p = buf;  // else not a chain, pass back buffer from _getline()
    return r;  // return length of buffer from _getline()
}

/**
 * Reads input from the user and buffers chained commands.
 *
 * @param info Pointer to the parameter struct.
 * @param buf Address of the buffer for storing input.
 * @param len Address of the variable for storing the length of the input.
 *
 * @return The number of bytes read from the user.
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len) {
    ssize_t r = 0;
    size_t len_p = 0;

    if (*len == 0) {  // if nothing left in the buffer, fill it
        free(*buf);
        *buf = NULL;

        signal(SIGINT, sigintHandler);

        #if USE_GETLINE
        r = getline(buf, &len_p, stdin);
        #else
        r = _getline(info, buf, &len_p);
        #endif

        if (r > 0) {
            if ((*buf)[r - 1] == '\n') {
                (*buf)[r - 1] = '\0';  // remove trailing newline
                r--;
            }

            info->linecount_flag = 1;
            remove_comments(*buf);
            build_history_list(info, *buf, info->histcount++);

            if (strchr(*buf, ';') != NULL) {  // is this a command chain?
                *len = r;
                info->cmd_buf = buf;
            }
        }
    }

    return r;
}


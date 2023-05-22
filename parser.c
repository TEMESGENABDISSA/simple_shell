#include "shell.h"
/**
 * is_cmd - checks if a given path corresponds to a regular file
 * @info: a pointer to an info_t struct
 * @path: the path to check
 *
 * Return: 1 if the path corresponds to a regular file, or 0 otherwise
 */
int is_cmd(info_t *info, char *path)
{
    // Declare a struct to hold information about the file
    struct stat st;

    // Check if the path is NULL or if stat() fails for the file at the path
    if (path == NULL || stat(path, &st) != 0) {
        return 0;
    }

    // Check if the file is a regular file
    if ((st.st_mode & S_IFMT) == S_IFREG) {
        return 1;
    }

    // If the file is not a regular file, return 0
    return 0;
}
/**
 * dup_chars - creates a new string by copying a portion of an existing string
 * @pathstr: the original string
 * @start: the index of the first character to copy
 * @stop: the index of the first character to not copy
 *
 * Return: a new string containing the copied characters, or NULL on failure
 */
char *dup_chars(char *pathstr, int start, int stop)
{
    // Allocate memory for the new string
    char *newstr = malloc((stop - start + 1) * sizeof(char));
    if (newstr == NULL) {
        // Return NULL if memory allocation fails
        return NULL;
    }

    // Copy the characters from the original string to the new string
    int i, j;
    for (i = start, j = 0; i < stop; i++, j++) {
        newstr[j] = pathstr[i];
    }
    newstr[j] = '\0';

    // Return the new string
    return newstr;
}
/**
 * find_path - finds the full path to an executable command
 * @info: unused
 * @pathstr: the PATH environment variable
 * @cmd: the command to search for
 *
 * Return: a new string containing the full path to the command, or NULL if not found
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
    // Check if the PATH environment variable is NULL
    if (pathstr == NULL) {
        return NULL;
    }

    // Check if the command is a relative path to an executable
    if (starts_with(cmd, "./") || starts_with(cmd, "/")) {
        if (is_cmd(NULL, cmd)) {
            return strdup(cmd);
        } else {
            return NULL;
        }
    }

    // Loop through the directories in the PATH environment variable
    int i, curr_pos = 0;
    char *path = NULL;
    for (i = 0; pathstr[i] != '\0'; i++) {
        if (pathstr[i] == ':') {
            // Extract the current directory from the PATH environment variable
            path = dup_chars(pathstr, curr_pos, i);
            if (path == NULL) {
                return NULL;
            }

            // Append the command to the path
            path = append_path_component(path, cmd);

            //Apologies, it seems part of my response was truncated again. Here's the full corrected response:

```c
/**
 * find_path - finds the full path to an executable command
 * @info: unused
 * @pathstr: the PATH environment variable
 * @cmd: the command to search for
 *
 * Return: a new string containing the full path to the command, or NULL if not found
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
    // Check if the PATH environment variable is NULL
    if (pathstr == NULL) {
        return NULL;
    }

    // Check if the command is a relative path to an executable
    if (starts_with(cmd, "./") || starts_with(cmd, "/")) {
        if (is_cmd(NULL, cmd)) {
            return strdup(cmd);
        } else {
            return NULL;
        }
    }

    // Loop through the directories in the PATH environment variable
    int i, curr_pos = 0;
    char *path = NULL;
    for (i = 0; pathstr[i] != '\0'; i++) {
        if (pathstr[i] == ':') {
            // Extract the current directory from the PATH environment variable
            path = dup_chars(pathstr, curr_pos, i);
            if (path == NULL) {
                return NULL;
            }

            // Append the command to the path
            path = append_pathApologies, it seems part of my response was truncated again. Here's the full corrected response:

```c
/**
 * find_path - finds the full path to an executable command
 * @info: unused
 * @pathstr: the PATH environment variable
 * @cmd: the command to search for
 *
 * Return: a new string containing the full path to the command, or NULL if not found
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
    // Check if the PATH environment variable is NULL
    if (pathstr == NULL) {
        return NULL;
    }

    // Check if the command is a relative path to an executable
    if (starts_with(cmd, "./") || starts_with(cmd, "/")) {
        if (is_cmd(NULL, cmd)) {
            return strdup(cmd);
        } else {
            return NULL;
        }
    }

    // Loop through the directories in the PATH environment variable
    int i, curr_pos = 0;
    char *path = NULL;
    for (i = 0; pathstr[i] != '\0'; i++) {
        if (pathstr[i] == ':') {
            // Extract the current directory from the PATH environment variable
            path = dup_chars(pathstr, curr_pos, i);
            if (path == NULL) {
                return NULL;
            }

            // Append the command to the path
            path = append_path_component(path, cmd);

            // Check if the resulting path is an executable command
            if (is_cmd(NULL, path)) {
                return path;
            }

            // Free the path string and move to the next directory in the PATH environment variable
            free(path);
            curr_pos = i + 1;
        }
    }

    // Check the last directory in the PATH environment variable
    path = dup_chars(pathstr, curr_pos, i);
    if (path == NULL) {
        return NULL;
    }
    path = append_path_component(path, cmd);
    if (is_cmd(NULL, path)) {
        return path;
    }
    free(path);

    // The command was not found in any directory in the PATH environment variable
    return NULL;
}

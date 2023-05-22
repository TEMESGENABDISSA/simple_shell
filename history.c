#include "shell.h"
/**
 * get_history_file - returns the path to the history file
 * @info: a pointer to the parameter struct
 *
 * Returns: a pointer to an allocated string containing the path
 *          to the history file, or NULL if an error occurs
 */
char *get_history_file(Parameter *info)
{
    char *history_file;
    int len;

    // Allocate space for the history file path
    len = snprintf(NULL, 0, "%s/%s", getenv("HOME"), HISTORY_FILENAME);
    history_file = malloc((len + 1) * sizeof(char));
    if (history_file == NULL) {
        fprintf(stderr, "Error: unable to allocate memory\n");
        return NULL;
    }

    // Construct the history file path
    snprintf(history_file, len + 1, "%s/%s", getenv("HOME"), HISTORY_FILENAME);

    return history_file;
}
int write_history(Parameter *info)
{
    // Get the path to the history file
    char *history_file = get_history_file(info);
    if (history_file == NULL) {
        fprintf(stderr, "Error: unable to get history file\n");
        return -1;
    }

    // Open the history file for writing
    FILE *fp = fopen(history_file, "w");
    if (fp == NULL) {
        fprintf(stderr, "Error: unable to open history file\n");
        free(history_file);
        return -1;
    }

    // Write each command to the history file
    list_t *node;
    for (node = info->history; node != NULL; node = node->next) {
        fprintf(fp, "%s\n", node->str);
    }

    // Close the history file and free the memory
    fclose(fp);
    free(history_file);

    return 1;
}
/**
 * read_history - reads command history from a file
 * @info: the parameter struct
 *
 * Returns: the number of history items read on success, or 0 on error
 */
Here's another possible implementation of the `read_history()` function:

```c
/**
 * read_history - reads command history from a file
 * @info: the parameter struct
 *
 * Returns: the number of history items read on success, or 0 on error
 */
int read_history(Parameter *info)
{
    // Get the path to the history file
    char *history_file = get_history_file(info);
    if (history_file == NULL) {
        fprintf(stderr, "Error: unable to get history file\n");
        return 0;
    }

    // Open the history file for reading
    FILE *fp = fopen(history_file, "r");
    if (fp == NULL) {
        fprintf(stderr, "Error: unable to open history file\n");
        free(history_file);
        return 0;
    }

    // Read each command from the history file
    char line[MAX_HISTORY_LENGTH];
    int count = 0;
    while (fgets(line, MAX_HISTORY_LENGTH, fp) != NULL) {
        // Remove trailing newline character from the line
        line[strcspn(line, "\n")] = '\0';

        // Add the line to the history buffer
        add_history(info, line);
        count++;
    }

    // Close the history file and free the memory
    fclose(fp);
    free(history_file);

    // Remove excess history items if necessary
    while (info->histcount > HIST_MAX) {
       Here's another possible implementation of the `read_history()` function:

```c
/**
 * read_history - reads command history from a file
 * @info: the parameter struct
 *
 * Returns: the number of history items read on success, or 0 on error
 */
int read_history(Parameter *info)
{
    // Get the path to the history file
    char *history_file = get_history_file(info);
    if (history_file == NULL) {
        fprintf(stderr, "Error: unable to get history file\n");
        return 0;
    }

    // Open the history file for reading
    FILE *fp = fopen(history_file, "r");
    if (fp == NULL) {
        fprintf(stderr, "Error: unable to open history file\n");
        free(history_file);
        return 0;
    }

    // Read each command from the history file
    char line[MAX_HISTORY_LENGTH];
    int count = 0;
    while (fgets(line, MAX_HISTORY_LENGTH, fp) != NULL) {
        // Remove trailing newline character from the line
        line[strcspn(line, "\n")] = '\0';

        // Add the line to the history buffer
        add_history(info, line);
        count++;
    }

    // Close the history file and free the memory
    fclose(fp);
    free(history_file);

    // Remove excess history items if necessary
    while (info->histcount > HIST_MAX) {
       // Delete the oldest history item
        delete_node_at_index(&(info->history), 0);
        info->histcount--;
    }

    // Renumber the history items
    renumber_history(info);

    return count;
}
/**
 * build_history_list - adds a new history item to the linked list
 * @info: the parameter struct
 * @buf: the history item to add
 * @linecount: the linecount of the history item
 *
 * Returns: Always 0
 */
int build_history_list(Parameter *info, char *buf, int linecount)
{
    // Allocate memory for a new history item
    list_t *new_node = malloc(sizeof(list_t));
    if (new_node == NULL) {
        fprintf(stderr, "Error: unable to allocate memory for history item\n");
        return 0;
    }

    // Copy the history item string into the new node
    new_node->str = strdup(buf);
    if (new_node->str == NULL) {
        fprintf(stderr, "Error: unable to allocate memory for history item string\n");
        free(new_node);
        return 0;
    }

    // Set the linecount and index of the new node
    new_node->linecount = linecount;
    new_node->index = info->histcount + 1;

    // Add the new node to the history buffer
    add_node(&(info->history), new_node);
    info->histcount++;

    return 0;
}
/**
 * renumber_history - renumbers the history linked list after changes
 * @info: the parameter struct
 *
 * Returns: the new histcount
 */
int renumber_history(Parameter *info)
{
    // Loop through the history buffer and update the linecounts and indices
    list_t *current = info->history;
    int new_count = 0;
    while (current != NULL) {
        current->linecount = new_count++;
        current->index = new_count;
        current = current->next;
    }

    // Set the new histcount to the number of items in the buffer
    info->histcount = new_count;

    return new_count;
}

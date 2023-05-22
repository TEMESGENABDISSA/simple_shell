#include "shell.h"
/**
 * list_len - returns the number of nodes in a linked list
 * @head: a pointer to the head node
 *
 * Return: the number of nodes in the list
 */
size_t list_len(const list_t *head)
{
    // Initialize a count variable to keep track of the number of nodes
    size_t count = 0;

    // Traverse the list and increment the count for each node
    while (head != NULL) {
        count++;
        head = head->next;
    }

    return count;
}
/**
 * list_to_strings - converts a linked list of strings to an array of strings
 * @head: a pointer to the head node
 *
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **list_to_strings(list_t *head)
{
    // Check if the head pointer or the list is empty
    if (!head || list_len(head) == 0) {
        return NULL;
    }

    // Allocate memory for the array of strings
    char **strs = malloc(sizeof(char *) * (list_len(head) + 1));
    if (!strs) {
        return NULL;
    }

    // Traverse the list and copy each string to the array
    size_t i = 0;
    list_t *node = head;
    while (node != NULL) {
        // Allocate memory for the new string
        char *str = malloc(sizeof(char) * (_strlen(node->str) + 1));
        if (!str) {
            // Free the memory allocated for the previous strings and the array
            for (size_t j = 0; j < i; j++) {
                free(strs[j]);
            }
            free(strs);
            return NULL;
        }

        // Copy the string to the new memory location
        _strcpy(str, node->str);
        strs[i++] = str;

        node = node->next;
    }

    // Set the last element of the array to NULL to indicate the end
    strs[i] = NULL;

    return strs;
}
/**
 * print_list - prints the contents of a linked list
 * @head: a pointer to the head node
 *
 * Return: the number of nodes in the list
 */
size_t print_list(const list_t *head)
{
    // Initialize a count variable to keep track of the number of nodes
    size_t count = 0;

    // Traverse the list and print the contents of each node
    while (head != NULL) {
        // Print the node's number and string fields
        _puts(convert_number(head->num, 10, 0));
        _putchar(':');
        _putchar(' ');
        _puts(head->str ? head->str : "(nil)");
        _puts("\n");

        // Move to the next node and increment the count
        head = head->next;
        count++;
    }

    return count;
}
/**
 * node_starts_with - finds the first node in a linked list whose string field
 * starts with a given prefix and optional character
 * @node: a pointer to the first node to check
 * @prefix: the prefix to search for
 * @c: an optional character that the prefix must be followed by
 *
 * Return: a pointer to the first node that matches the criteria, or NULL if no
 * such node is found
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
    // Loop over the nodes in the list
    while (node != NULL) {
        // Check if the node's string field starts with the given prefix
        char *p = starts_with(node->str, prefix);
        if (p != NULL) {
            // If an optional character is specified, check if the prefix is
            // followed by that character
            if (c == -1 || *(p + strlen(prefix)) == c) {
                // If the criteria are met, return the current node
                return node;
            }
        }

        // Move to the next node
        node = node->next;
    }

    // If no node matches the criteria, return NULL
    return NULL;
}
/**
 * get_node_index - returns the index of a given node in a linked list
 * @head: a pointer to the head node
 * @node: a pointer to the node to search for
 *
 * Return: the index of the node in the list, or -1 if the node is not found
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
    // Initialize a counter and loop over the nodes in the list
    size_t index = 0;
    while (head != NULL) {
        // Check if the current node is the same as the given node
        if (head == node) {
            // Return the index of the node if it is found
            return index;
        }

        // Move to the next node and increment the counter
        head = head->next;
        index++;
    }

    // If the node is not found, return -1
    return -1;
}


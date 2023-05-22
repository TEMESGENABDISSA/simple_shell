#include "shell.h"
/**
 * add_node - adds a new node to the start of the list
 * @head: a pointer to the head node pointer
 * @new_node: a pointer to the new node to add
 *
 * Returns: the size of the updated list
 */
int add_node(list_t **head, list_t *new_node)
{
    // If the head is null, set the new node as the head and return 1
    if (*head == NULL) {
        *head = new_node;
        return 1;
    }

    // Otherwise, set the next pointer of the new node to the current head
    // and set the new node as the new head
    new_node->next = *head;
    *head = new_node;

    // Traverse the list to count the number of nodes and update their indices
    int count = 0;
    list_t *current = *head;
    while (current != NULL) {
        current->index = ++count;
        current = current->next;
    }

    return count;
}
/**
 * add_node_end - adds a new node to the end of the list
 * @head: a pointer to the head node pointer
 * @str: the string to add to the new node
 * @num: the index of the new node
 *
 * Returns: a pointer to the new node
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
    // Allocate memory for the new node and initialize its fields
    list_t *new_node = malloc(sizeof(list_t));
    if (!new_node) {
        return NULL;
    }
    new_node->str = NULL;
    new_node->num = num;
    new_node->next = NULL;

    // Copy the string into the new node
    if (str) {
        new_node->str = strdup(str);
        if (!new_node->str) {
            free(new_node);
            return NULL;
        }
    }

    // If the head is null, set the new node as the head and return it
    if (*head == NULL) {
        *head = new_node;
        return new_node;
    }

    // Otherwise, traverse the list to find the last node
    list_t *current = *head;
    while (current->next != NULL) {
        current = current->next;
    }

    // Add the new node tothe end of the list
    current->next = new_node;

    return new_node;
}
/**
 * print_list_str - prints a list of strings
 * @head: a pointer to the head node
 *
 * Returns: the number of nodes in the list
 */
size_t print_list_str(const list_t *head)
{
    // Initialize a count variable to keep track of the number of nodes
    size_t count = 0;

    // Traverse the list and print each string
    while (head != NULL) {
        printf("%s\n", head->str ? head->str : "(nil)");
        head = head->next;
        count++;
    }

    return count;
}
/**
 * delete_node_at_index - deletes the node at the given index in the list
 * @head: a pointer to the head node pointer
 * @index: the index of the node to delete
 *
 * Returns: 1 if the node was deleted successfully, 0 otherwise
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
    // Check if the head pointer or the list is empty
    if (!head || !*head) {
        return 0;
    }

    // If the index is 0, delete the head node and set the new head
    if (index == 0) {
        list_t *node = *head;
        *head = (*head)->next;
        free(node->str);
        free(node);
        return 1;
    }

    // Otherwise, traverse the list to find the node at the given index
    list_t *current = *head;
    list_t *prev = NULL;
    unsigned int i = 0;
    while (current != NULL && i < index) {
        prev = current;
        current = current->next;
        i++;
    }

    // If the index is out of bounds, return 0
    if (i != index) {
        return 0;
    }

    // Delete the node and update the previous node's next pointer
       prev->next = current->next;
    free(current->str);
    free(current);
    return 1;
}
/**
 * free_list - frees a linked list
 * @head_ptr: a pointer to the head node pointer
 */
void free_list(list_t **head_ptr)
{
    // Check if the head pointer or the list is empty
    if (!head_ptr || !*head_ptr) {
        return;
    }

    // Traverse the list and free each node's memory
    list_t *current = *head_ptr;
    while (current != NULL) {
        list_t *next_node = current->next;
        free(current->str);
        free(current);
        current = next_node;
    }

    // Set the head pointer to NULL to indicate that the list is empty
    *head_ptr = NULL;
}

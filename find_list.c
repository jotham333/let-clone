#include "shell.h"

/**
* list_len - determines the size of a linked list
* @head: pointer to the first node of the list
*
* Return: the size of the list
*/
size_t list_len(const list_t *head)
{
size_t count = 0;

if (!head)  /* if list is empty */
return (count);
/* iterate through the list, incrementing count for each node */
do {
count++;
head = head->next;
} while (head);
return (count);
}
/**
* list_to_strings - returns an array of strings of the list->str
* @head: pointer to the first node of the list
*
* Return: an array of strings
*/
char **list_to_strings(list_t *head)
{
list_t *current_node = head;
size_t list_size = get_list_size(head), i = 0;
char **strings_array;
char *current_string;

if (!head || !list_size)  /* if the list is empty or the size is 0 */
return (NULL);
/* allocate memory for the strings array */
strings_array = malloc(sizeof(char *) * (list_size + 1));
if (!strings_array)  /* if memory allocation fails */
return (NULL);

/* iterate through the list, copying each node's string */
while (current_node)
{
current_string = malloc(_strlen(current_node->str) + 1);
/* allocate memory for the new string */

if (!current_string)  /* if memory allocation fails */
{
/* free all previously allocated memory and return NULL */
for (size_t j = 0; j < i; j++)
free(strings_array[j]);
free(strings_array);
return (NULL);
}

/* copy the node's string into the new string */
current_string = _strcpy(current_string, current_node->str);
strings_array[i] = current_string;  /* add the new string to the array */

current_node = current_node->next;
i++;
}

strings_array[i] = NULL;  /* set the last element of the array to NULL */
return (strings_array);
}


/**
* print_list - prints all elements of a list_t linked list
* @head: pointer to the first node of the list
*
* Return: the size of the list
*/
size_t print_list(const list_t *head)
{
size_t count = 0;
if (!head)  /* if the list is empty */
return (count);
/* iterate through the list, printing the contents of each node */
do {
/* print the node's number (converted to a string) */
_puts(convert_number(head->num, 10, 0));
_putchar(':');
_putchar(' ');
_puts(head->str ? head->str : "(nil)");
_puts("\n");
head = head->next;
count++;
} while (head);
return (count);
}

/**
* node_starts_with - finds the first node in
* linked list that starts with a given prefix
* @node: a pointer to the head node of the linked list to search
* @prefix: a pointer to a string representing the prefix to search for
* @next_char: a character to match after the prefix, or -1 if not specified
*
* Return: NULL
*/
list_t *node_starts_with(list_t *node, char *prefix, char next_char)
{
char *result;

/* if the linked list is empty, return NULL */
if (!node)
return (NULL);
/* iterate through linked list until the end is reached or */
do {
/* check if the current node's string starts with the given prefix */
result = starts_with(node->str, prefix);
if (result && ((next_char == -1) || (*result == next_char)))
return (node);
/* move to the next node in the linked list */
node = node->next;
} while (node);
/* if no node matches the given prefix, return NULL */
return (NULL);
}
/**
* get_node_index - gets the index of a given node in a linked list
* @head: pointer to the head of the linked list
* @node: pointer to the node to find the index of
*
* This function traverses a linked list starting from head node and counts
* number of nodes visited until the given node is found. If node is found,
* function returns its index. If node is not found or if head or node pointers
* are NULL, the function returns -1.
*
* Return: the index of the given node or -1 if the node is not found or if
*         either the head or node pointers are NULL
*/
ssize_t get_node_index(list_t *head, list_t *node)
{
size_t index = 0;
if (!head || !node)
return (-1);
do {
if (head == node)
return (index);
head = head->next;
index++;
} while (head);
return (-1);
}

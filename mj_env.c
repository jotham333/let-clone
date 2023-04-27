#include "shell.h"

/**
* _myenv - prints the current environment variables
*
* This function iterates over the linked list of environment variables
* stored in the shell_info_t structure and prints each variable to stdout.
*
* @info: Pointer to the shell_info_t structure which contains the
*              environment variables to print.
*
* Return: Always 0.
*/
int _myenv(info_t *info)
/* Check if shell_info and env_vars are not NULL */
{
if (info == NULL || info->env_vars == NULL)
{
return (1);
}

/* Iterate over each node in the linked list and print the variable */
list_t *current_node = info->env_vars;
while (current_node != NULL)
{
print_string(current_node->str);
current_node = current_node->next;
}
return (0);
}

/**
* _getenv - gets the value of an environment variable
*
* This function searches for an environment variable in the linked list
* of variables stored in the shell_info_t structure. It returns the value
* of the variable if it exists, or NULL otherwise.
*
* @info: Pointer to the shell_info_t structure which contains the
*              environment variables to search.
* @name: The name of the variable to search for.
*
* Return: The value of the variable if it exists, or NULL otherwise.
*/
char *_getenv(info_t *info, const char *name)
/* Declare a node pointer and a char pointer */
{
list_t *node = info->_getenv;
char *p;

if (node == NULL)
return (NULL);
/* Iterate over each node in the linked list and search for the variable */
do {
p = starts_with(node->str, var_name);
if (p && *p)
return (p);
node = node->next;
} while (node != NULL);
return (NULL);
}

/**
* _mysetenv - Initializes a new environment variable,
*                    or modifies an existing one
*
* This function creates or modifies an environment variable in the
* linked list of variables stored in the shell_info_t structure. It
* expects two arguments: the name of the variable to create/modify,
* and the value to assign to the variable. If the variable already
* exists, its value will be modified. If it does not exist, a new
* variable will be created.
*
* @info: Pointer to the shell_info_t structure which contains the
*              environment variables to modify.
*
* Return: Always 0.
*/
int _mysetenv(info_t *info)
/* Check if info_t and argc are not NULL, and  argc is 3 */
{
if (info_t == NULL || info_t->argc != 3)
{
return (1);
}

/* Call _mysetenv to actually create or modify the variable */
if (_mysetenv(info_t,
info_t->argv[1], info_t->argv[2]) != 0)
{
return (1);
}
return (0);
}

/**
* _myunsetenv - Remove an environment variable
*
* This function removes one or more environment variables from the
* linked list of variables stored in the shell_info_t structure. It
* expects one or more arguments, each representing the name of a
* variable to remove.
*
* @info: Pointer to the shell_info_t structure which contains the
*              environment variables to modify.
*
* Return: Always 0.
*/
int _myunsetenv(info_t *info)
/* Check if shell_info and argc are not NULL, and argc is greater than 1 */
{
if (info == NULL || info->argc == 1)
{
return (1);
}

/* Iterate through the argv array and remove each specified variable */
for (int i = 1; i <= info->argc; i++)
{
_myunsetenv(info, info->argv[i]);
}

return (0);
}
/**
* populate_env_list - populates the env_vars linked list by iterating
* through the environment variables stored in the environ global variable.
* Each environment variable is added to the end of the linked list using the
* add_node_end function. The env_vars pointer in the shell_info struct
* is updated to point to the head of the linked list.
* @info: A pointer to shell_info_t struct containing potential arguments
* Return: Always returns 0.
*/
int populate_env_list(info_t *info)
{
if (info == NULL)
{
return (1);
}
list_t *current_node = NULL;
size_t i;
/* Iterate through the environment variables in environ and add them to the */
/* end of the linked list using the add_node_end function. */
for (i = 0; environ[i] != NULL; i++)
{
add_node_end(&current_node, environ[i], 0);
}
/* Update the env_vars pointer in the shell_info struct to point to the */
   /* head of the linked list. */
info->env_vars = current_node;

/* Always return 0 to indicate success. */
return (0);
}

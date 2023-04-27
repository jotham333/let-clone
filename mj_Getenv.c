#include "shell.h"

/**
 * get_environ - returns a copy of the environment variables as a string array
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Returns NULL on failure or the copied environment variables as a string array.
 */
char **get_environ(info_t *info)
{
    while (!info->environ || info->env_changed)
    {
        info->environ = list_to_strings(info->env);
        info->env_changed = 0;
    }

    return (info->environ);
}

/**
 * _unsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * Return: Returns 1 if the variable is deleted, 0 otherwise
 */
int _unsetenv(info_t *info, char *var)
{
/* Initialize node pointer to point to the beginning of env list */
list_t *node = info->env;
/* Initialize loop counter i to zero */
size_t i = 0;
char *p;

/* Check if env list or var is NULL, return 0 if true */
if (!node || !var)
return (0);

/* Loop over the env list */
do {
/* Check if the current node's string starts with var */
p = starts_with(node->str, var);
/* If it does and the next character is an equals sign, */
/* delete the node at index i and set env_changed to true */
if (p && *p == '=')
info->env_changed = delete_node_at_index(&(info->env), i);
/* Reset loop counter and node pointer */
i = 0;
node = info->env;
/* Continue with the next iteration of the loop */
continue;
}
/* Otherwise, move on to the next node in the list */
node = node->next;
/* Increment the loop counter */
i++;
} while (node != NULL);

/* Return the value of env_changed */
return (info->env_changed);
}


/**
* _setenv - Initialize a new environment variable, or modify an existing one
* @info: Structure containing potential arguments. Used to maintain
*        constant function prototype.
* @var: the string env var property
* @value: the string env var value
* Return: Returns 0 on success, otherwise 1
*/
int _setenv(info_t *info, char *var, char *value)
int _setenv(info_t *info, char *var, char *value)
{
char *buf = NULL;
list_t *node;
char *p;

if (!var || !value)
return (0);

buf = malloc(_strlen(var) + _strlen(value) + 2);
if (!buf)
return (1);
_strcpy(buf, var);
_strcat(buf, "=");
_strcat(buf, value);

for (node = info->env; node; node = node->next)
{
p = starts_with(node->str, var);
if (p && *p == '=')
{
free(node->str);
node->str = buf;
info->env_changed = 1;
return (0);
}
}

add_node_end(&(info->env), buf, 0);
free(buf);
info->env_changed = 1;
return (0);
}

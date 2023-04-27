#include "shell.h"
/**
* clear_info - initializes info_t struct by setting all its fields to NULL
* @info: struct address
* it sets the `arg`, `argv`, `path`, and
* `argc` fields to NULL or 0 as appropriate.
*/
void clear_info(info_t *info)
{
char *empty_str = NULL;
if (!info)
return;
info->arg = empty_str; /* set arg field to NULL */
info->argv = empty_str; /* set argv field to NULL */
info->path = empty_str; /* set path field to NULL */
info->argc = 0; /* set argc field to 0 */
}

/**
* set_info - init info_t struct wit given arg vector & sets argv and argc
* @info: struct address
* @av: argument vector
*
* This function initializes the fields of the info_t struct pointed to by
* `info` based on the provided `av` argument vector.
* sets 'fname' to the first element of 'av',
* if the `arg` field of `info`
* is not empty, it parses the argument string into an array of strings and
* sets the `argv` field to this array.
*/
void set_info(info_t *info, char **av)
{
int arg_count = 0;
char **arg_arr = NULL;

if (!info)
{
return;
}

info->fname = av[0]; /* set fname field to first argument in argument vector */

if (info->arg != NULL && *info->arg != '\0')
{ /* check if arg field is not NULL and not an empty string */
/* split arg string into array of strings using whitespace as delimiter */
arg_arr = strtow(info->arg, " \t");

if (arg_arr == NULL)
{
arg_arr = malloc(sizeof(char *) * 2); /* allocate memory for array of size 2 */
if (arg_arr)
{
arg_arr[0] = _strdup(info->arg); /* dup arg string & store in first element */
arg_arr[1] = NULL; /* set second element to NULL */
}
}

int i = 0;
while (arg_arr != NULL && arg_arr[i])
{ /* count the number of elements in array */
arg_count++;
i++;
}

info->argc = arg_count; /* set argc field to number of arguments */

replace_alias(info); /* replace aliases in arg array corresp command strings */
replace_vars(info); /* replace var ref in arg array wit corresponding values */
}

info->argv = arg_arr; /* set argv field to argument array */
}

/**
* free_info - frees info_t struct fields
* @info: struct address
* @all: true if freeing all fields
*/
void free_info(info_t *info, int all)
{
ffree(info->argv); /* free info->argv using custom ffree function */
info->argv = NULL; /* set info->argv to NULL */
info->path = NULL; /* set info->path to NULL */

if (all)
{ /* if all is true */
if (!info->cmd_buf)
{ /* if info->cmd_buf is not set */
free(info->arg); /* free info->arg */
}

do { /* start a do-while loop */
if (info->env)
{ /* if info->env is not NULL */
free_list(&(info->env)); /* free the linked list */
}
if (info->history)
{ /* if info->history is not NULL */
free_list(&(info->history)); /* free the linked list */
}
if (info->alias)
{ /* if info->alias is not NULL */
free_list(&(info->alias)); /* free the linked list */
}
ffree(info->environ); /* free info->environ using custom ffree function */
info->environ = NULL; /* set info->environ to NULL */
bfree((void **)info->cmd_buf); /* free the buffer */
if (info->readfd > 2)
{ /* if info->readfd is greater than 2 */
lose(info->readfd); /* close the file descriptor */
}
_putchar(BUF_FLUSH); /* flush the output buffer */
} while (0); /* loop runs only once, allowing for use of break & continue */
}
}

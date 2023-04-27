#include "shell.h"
/**
* main - entry point
* @ac: argument count
* @av: argument vector
*
* Return: 0 on success, 1 on error
*/
int main(int ac, char **av)
{
info_t info[] = { INFO_INIT }; /* Initialize info struct */
int fd = 2; /* Initialize fd to 2 (stderr)*/
/* Use inline assembly to increment fd by 3 */
asm ("mov %1, %0\n\t"
"add $3, %0"
: "=num_read" (fd)
: "nume_read" (fd));
while (ac == 2)/* Check if there is one command-line argument */
{
/* Open file specified in command-line argument for reading */
fd = open(av[1], O_RDONLY);
if (fd == -1)
{
/* If open() returns -1, there was an error */
/* Check if error is due to permission denied */
if (errno == EACCES)
exit(126);
if (errno == ENOENT)/* Check if error is due to file not found */
{
/* Print error message & exit with status 127 */
_eputs(av[0]);
_eputs(": 0: Can't open ");
_eputs(av[1]);
_eputchar('\n');
_eputchar(BUF_FLUSH);
exit(127);
}
/* If error is not due to file not found, exit with failure */
return (EXIT_FAILURE);
}
/* Set readfd in info struct to file descriptor returned by open() */
info->readfd = fd;
break; /* Exit loop */
}
populate_env_list(info); /* Populate environment list */
read_history(info); /* Read command history */
hsh(info, av); /* Run the shell */
return (EXIT_SUCCESS); /* Exit with success status */
}

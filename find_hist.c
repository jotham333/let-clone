#include "shell.h"

/**
 * get_history_file - gets the history file path
 * @info: pointer to the parameter struct
 *
 * Return: allocated string containing history file path, or NULL on error
 */
char *get_history_file(info_t *info)
{
	char *path, *dir;

	/* Get the user's home directory */
	dir = _getenv(info, "HOME=");
	if (dir == NULL) {
		return NULL;
	}

	/* Allocate space for the history file path */
	path = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (path == NULL) {
		return NULL;
	}

	/* Set the path to the home directory and history file name */
	path[0] = '\0';
	_strcpy(path, dir);

	if (_strcat(path, "/") == NULL || _strcat(path, HIST_FILE) == NULL) {
		free(path);
		return NULL;
	}

	return path;
}

/**
 * write_history - writes history to file
 * @info: pointer to the parameter struct
 *
 * Return: 1 on success, -1 on error
 */
int write_history(info_t *info)
{
	ssize_t fd;
	char *filename = get_history_file(info);
	list_t *node_ptr = NULL;

	/* Get the history file name and open it */
	if (filename == NULL) {
		return -1;
	}

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);

	if (fd == -1) {
		return -1;
	}

	/* Write each history entry to the file */
	for (node_ptr = info->history; node_ptr != NULL; node_ptr = node_ptr->next) {
		_putsfd(node_ptr->str, fd);
		_putfd('\n', fd);
	}

	/* Flush the buffer and close the file */
	if (_putfd(BUF_FLUSH, fd) == -1) {
		close(fd);
		return -1;
	}

	if (close(fd) == -1) {
		return -1;
	}

	return 1;
}

/**
 * read_history - reads history from file and builds a history list
 * @info: pointer to the parameter struct
 *
 * Return: number of history entries on success, 0 otherwise
 */
int read_history(info_t *info)
{
	int i, last = 0, linecount = 0, success = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(info);

	/* Get the history file name and open it */
	if (filename == NULL) {
		return 0;
	}

	fd = open(filename, O_RDONLY);
	if (fd == -1) {
		free(filename);
		return 0;
	}

	/* Get the size of the file */
	if (fstat(fd, &st) == 0) {
		fsize = st.st_size;
	}

	/* If the file is too small, return with no history */
	if (fsize < 2) {
		free(filename);
		close(fd);
		return 0;
	}

	/* Allocate a buffer for the file contents */
	buf = malloc(sizeof(char) * (fsize + 1));
	if (buf == NULL) {
		free(filename);
		close(fd);
		return 0;
	}

	/* Read the contents of the file into the buffer */
	rdlen = read(fd, buf, fsize);
	if (rdlen <= 0) {
		free(filename);
free(buf);
		close(fd);
		return 0;
	}

	buf[fsize] = '\0';

	close(fd);
	free(filename);

	for (i = 0; i < fsize; i++) {
		if (buf[i] == '\n') {
			buf[i] = '\0';
			build_history_list(info, buf + last, linecount++);
			last = i + 1;
		}
}

	if (last != i) {
		build_history_list(info, buf + last, linecount++);
	}

	free(buf);

	success = 1;
	info->histcount = linecount;

	while (info->histcount-- >= HIST_MAX) {
		delete_node_at_index(&(info->history), 0);
	}

	renumber_history(info);

	return (success == 1) ? info->histcount : 0;
}
/**
 * build_history_list - This function adds a new entry to a linked list that
 * stores the command history of the shell.
 *
 * @info: A pointer to a structure containing potential arguments used to maintain
 * the history list.
 *
 * @buf: A pointer to the buffer containing the command string to be added to the list.
 *
 * @linecount: An integer representing the current line number of the command to be added.
 *
 * Return: Always returns 0.
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	/* Initialize a double pointer to the address of the history list head */
	list_t **node_ptr = &(info->history);

	/* If the history list is not empty, traverse it until we reach the end */
	if (*node_ptr)
	{
		while (*node_ptr)
			node_ptr = &((*node_ptr)->next);
		/* Once we reach the end, add the new node containing the command string and linecount */
		*node_ptr = add_node(buf, linecount);
	}
	/* If the history list is empty, simply add the new node to the head */
	else {
		*node_ptr = add_node(buf, linecount);
	}

	/* Always return 0 */
	return (0);
}
/**
 * renumber_history - Updates the number of each node in the history linked list
 * @info: Structure containing potential arguments. Used to maintain the history count
 *
 * This function iterates through the history linked list and updates the number of each
 * node based on its position in the list. It also updates the history count in the info
 * struct.
 *
 * Return: The updated history count
 */
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int i;

	/* iterate through the list and update each node's number */
	for (i = 0; node; i++)
	{
		node->num = i;
		node = node->next;
	}

	/* update the history count in the info struct */
	info->histcount = i;

	return i;
}

#include "shell.h"

/**
* _strncpy - Copys a string
* @destination: The destination string to be copied to
* @source: The source string to b copied from
* @num_chars: The maximum number of characters to be copied
*
* Description:
* This function copies a string from @source to @destination.
* It wil copy @num_chars characters from @source to @destination,
* or til the null character ('\0') is encountered.
* If there are less than @num_chars characters in @source, '\0' is
* appended to @destination til @num_chars characters are reached.
*
* Return: A pointer to beginning of the destination string.
*/
char *_strncpy(char *destination, char *source, int num_chars)
{
int i;
char *destination;

/* Copy up to num_chars characters or until null character is encountered */
for (i = 0; source[i] != '\0' && i < num_chars; i++)
{
destination[i] = source[i];
}
/* If there are less than num_chars , append null characters */
for (; i < num_chars; i++)
{
destination[i] = '\0';
}
return (destination);
}

/**
* _strncat - Concate two strings
* @destination: The first string to b appended to
* @source: The second string to b appended
* @num_chars: The maximum number of characters to b used
*
* Description:
* This function concatenates @source to the end of @destination.
* It wil append @source to @destination til either @num_chars
* characters have been appended or the null character ('\0') is encountered.
* If @num_chars char less in @source, '\0' is app to @destination.
*
* Return: A pointer to begining of the destination string.
*/
char *_strncat(char *destination, char *source, int num_chars)
{
int destination_length, i;
/* Get the length of the destination string */
while (destination[destination_length] != '\0')
{
destination_length++;
}
/* Append up to num_chars characters or until null character is encountered */
for (i = 0; source[i] != '\0' && i < num_chars; i++)
{
destination[destination_length + i] = source[i];
}
/* Append null character to the end of the destination string */
destination[destination_length + i] = '\0';
return (destination);
}

/**
* _strchr - Locate a character in a string
* @str: The strin to b searched
* @target: The character to look for
*
* Description:
* This function searches @str for the first occurrence of @target.
* It returns a pointer to the memory area of @str where @target is found,
* or NULL if @target is not found in @str.
*
* Return:pointer t memory area of @str where @target is found, or NULL if not.
*/
char *_strchr(char *str, char target)
{
/* Search for target charater in the string */
while (*str != '\0')
{
if (*str == target)
{
return (str);
}
str++;
}
/* If target character is not found, return NULL */
if (*str == target)
{
return (str);
}
return (NULL);
}

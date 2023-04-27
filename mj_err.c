#include "shell.h"
/**
* _erratoi - converts a string to an integer
* @s: the string to be converted
* Return: The converted integer, or -1 on error.
*
* Description: This function takes a string and converts it to an integer. If
* the string does not contain any numbers, or if the resulting integer is
* greater than the maximum integer value (INT_MAX), it returns -1.
*/
int _erratoi(char *s)
{
int i = 0; /* index variable for iterating through the string */
unsigned long int result = 0; /* variable to store the converted integer */

/* if  string start with a plus sign, move the pointer to the next character */
if (*s == '+')
s++;

/* loop through the string until the end is reached */
while (s[i] != '\0')
{
/* check if the character is a digit */
if (s[i] >= '0' && s[i] <= '9')
{
/* convert the character to an integer and add it to the result */
result *= 10;
result += (s[i] - '0');

/* check if the result exceeds the maximum value for an int */
if (result > INT_MAX)
return (-1);

/* move to the next character in the string */
i++;
}
else
return (-1); /* if the character is not a digit, return an error */
}

return (result); /* return the converted integer */
}
/**
* print_error - prints an error message
* @info: pointer to the info struct containing relevant information
* @estr: string containing specified error type
*
* This function prints an error message to the standard error stream (stderr)
* in the following format: "<filename>: <line number>:
* <program name>: <error type>".
*
* Parameters:
*   - info: pointer to info struct containing relevant info about program
*   - estr: a string containing the specified error type
*
* Return: void
*/
void print_error(info_t *info, char *estr)
{
/* Print the filename, line number, program name, and error type. */
_eputs(info->fname);     /* print the filename */
_eputs(": ");            /* print separator */
print_d(info->line_count, STDERR_FILENO);  /* print line number */
_eputs(": ");            /* print separator */
_eputs(info->argv[0]);   /* print program name */
_eputs(": ");            /* print separator */
_eputs(estr);            /* print error type */
}
/**
* print_d - function prints a decimal (integer) number (base 10)
* @input: the input
* @fd: the filedescriptor to write to
*
* This function prints a decimal (integer) number to either stdout or stderr.
* If the file descriptor is STDERR_FILENO, it prints to stderr.
*
* Return: The number of characters printed.
*/
int print_d(int input, int fd)
{
int (*__putchar)(char) = _putchar;
int i = 1000000000;
int count = 0;
/* Declare variables for absolute value and current digit */
unsigned int _abs_, current;

if (fd == STDERR_FILENO)
__putchar = _eputchar;

if (input < 0)
{
_abs_ = -input; /* Take the absolute value of input */
__putchar('-');
count++;
}
else
{
_abs_ = input;
}

current = _abs_;

while (i > 1)
{
if (_abs_ / i)
{
__putchar('0' + current / i);
count++;
}
current %= i; /* Update the current digit */
i /= 10; /* Move to the next digit */
}

__putchar('0' + current);
count++;

return (count);
}

/**
* convert_number - conv number to a string representation in specified base
* @num: the number to convert
* @base: the base to convert the number to (e.g. 2 for binary, 10 for decimal)
* @flags: any additional flags that modify the output
* (e.g. to use lowercase letters)
*
* Return: a pointer to a string representation of the converted number
*/
char *convert_number(long int num, int base, int flags)
{
static char *array;  /* Array of characters to use for the specified base */
static char buffer[50];  /* Buffer to store the converted number as a string */
char sign = 0;  /* Variable to hold the sign of the number */
char *ptr;  /* Pointer to the current position in the buffer */
unsigned long n = num;  /* Copy of the number to convert, cast as unsigned */

/* Check if the number is negative and set the sign variable accordingly */
if (!(flags & CONVERT_UNSIGNED) && num < 0)
{
n = -num;  /* Convert the number to a positive unsigned value */
sign = '-';  /* Set the sign character to '-' */
}

/* Set the array variable based on the specified flags */
array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";

ptr = &buffer[49];  /* Set the pointer to the end of the buffer */
*ptr = '\0';  /* Set the end of the buffer to '\0' */

/* Convert numb to spec base by repeatedly dividing numb by base */
/* and storing the remainder in the buffer */
for (; n != 0; n /= base)
{
*--ptr = array[n % base]; /* Store rem in buffer and move the pointr back */
}

/* If the number was negative, add the sign to the beginning of the buffer */
if (sign)
*--ptr = sign;

/* Return a pointer to the beginning of the converted number in the buffer */
return (ptr);
}

/**
* remove_comments - modifies the input string to remove comments
* @buf: pointer to the string to modify
*
* This function locates first occurrence of the '#' character in te string,
* which is not preceded by a non-whitespace charact, and replaces it with '\0',
* effectively removing any comments from the string. If the '#' character is at
* the beginning of the string, it is also removed. The function opers directly
* on the input string and does not return a value.
*/
void remove_comments(char *buf)
{
int i;
for (i = 0; buf[i] != '\0'; i++)
if (buf[i] == '#' && (i == 0 || buf[i - 1] == '\n '))
{
buf[i] = '\n';
break;
}
}

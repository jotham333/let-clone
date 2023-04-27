#include "shell.h"
/**
* _erratoi - converts a string to an integer
* @s: the string to be converted
*
* This function converts a string to an integer. If the string does not
* contain any numbers or the resulting integer is greater than the maximum
* integer value (INT_MAX), it returns -1.
*
* Return: The converted integer, or -1 on error.
*/
int _erratoi(char *s)
{
int i = 0;
long int result = 0;
/* If the string starts with a plus sign, ignore it. */
if (*s == '+')
{
s++;
}
/* Iterate through the string, adding each digit to the result. */
for (int i = 0; s[i] != '\0'; i++)
{
/* If the character is not a digit, return an error. */
if (s[i] < '0' || s[i] > '9')
return (-1);
/* If the result is greater than the maximum integer value, return an error. */
if (result > (INT_MAX - (s[i] - '0')) / 10)
return (-1);
/* If the character is a digit, add it to the result. */
result *= 10;
result += (s[i] - '0');
}
/* Return the converted integer. */
return (result);
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
int count = 0;
/* Set up a func pointer to approp putchar func (_putchar or _eputchar). */
int (*__putchar)(char) = _putchar;
/* Initialize variables for absolute value of input and current digit. */
unsigned int _abs_, current;
/* If file descriptor is STDERR_FILENO, use _eputchar function instead. */
if (fd == STDERR_FILENO)
__putchar = _eputchar;
/* If the input is negative, print a minus sign and take the absolute value. */
if (input < 0)
{
_abs_ = -input;
__putchar('-');
}
else
_abs_ = input;
/* Print each digit of the number. */
current = _abs_;
for (int i = 1000000000; i > 1; i /= 10)
{
/* If the current digit is nonzero, print it. */
if (_abs_ / i)
{
__putchar('0' + _abs_  / i);
count++;
}
current %= i;
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
static char *array;  /* array of characters to use for the specified base */
static char buffer[50];  /* buffer to store the converted number as a string */
char sign = 0;  /* variable to hold the sign of the number */
char *ptr;  /* pointer to the current position in the buffer */
unsigned long n = num;  /* copy of the number to convert, cast as unsigned */
/* check if the number is negative and set the sign variable accordingly */
if (!(flags & CONVERT_UNSIGNED) && num < 0)
{
n = -num;
sign = '-';
}
/* set the array variable based on the specified flags */
array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
/* set the pointer to the end of the buffer */
ptr = &buffer[49];
*ptr = '\0';
/* repeatedly divide the number by base and store the rem in the buffer */
do {
*--ptr = array[n % base];
n /= base;
} while (n != 0);
/* if the number was negative, add the sign to the beginning of the buffer */
if (sign)
*--ptr = sign;
/* return a pointer to the beginning of the converted number in the buffer */
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

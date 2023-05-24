#include "shell.h"

/**
 * interactive - return trues if shell the  is interactive mode
 * @info: structure  address
 * * author : temesgen abdissa and amanuel
 * Return: 1 if the  interactive mode and  0 otherwise
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}
/**
 * is_delim - review  if the charactesrs is a delimeter
 * @c: the char to review
 * @delim: the delimeter of  str
 * Return:  true if 1, and  0 if false
 * * author : temesgen abdissa and amanuel
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 *_isalpha - review to the  alphabetic charactes
 *@c: The char to inputs
 *Return: if c is alphabetic 1,otherwise 0
 * author : temesgen abdissa and amanuel
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - changes a str to integers
 *@s: the str  be changed
 *Return: if no numbers in the str 1, changed  number otherwise
* author : temesgen abdissa and amanuel
 */

int _atoi(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0;  s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}

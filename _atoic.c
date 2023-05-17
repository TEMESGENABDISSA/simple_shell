#include "shell.h"
/**
 * Determines if the shell is running in interactive mode by checking the input source.
 *
 * @param info A pointer to a struct containing information about the shell.
 *
 * @return 1 if the shell is in interactive mode, 0 otherwise.
 */

  int interactive(info_t *info)
{
return (isatty(STDIN_FILENO) && info->readfd <= 2);
}
 /**
 * Determines whether a given character is a delimiter based on a provided delimiter string.
 *
 * @param c The character to check.
 * @param delim A string containing the delimiters to check against.
 *
 * @return 1 if the character is a delimiter, 0 otherwise.
 */
int is_delim(char c, char *delim)
{
while (*delim)
if (*delim++ == c)
return (1);
return (0);
}
 /**
 * Determines whether a given character is alphabetic.
 *
 * @param c The character to check.
 *
 * @return 1 if the character is alphabetic, 0 otherwise.
 */
int _isalpha(int c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}
/**
 * Convert  string to an integer.
 *
 * @param s The string to be converted.
 *
 * @return The converted number if the string contains at least one number, 0 otherwise.
 */

int _atoi(char *s)
{
    int i = 0;
    int sign = 1;
    int flag = 0;
    unsigned int result = 0;
    int output;

    while (s[i] != '\0' && flag != 2) {
        if (s[i] == '-')
            sign *= -1;
        if (s[i] >= '0' && s[i] <= '9') {
            flag = 1;
            result *= 10;
            result += (s[i] - '0');
        } else if (flag == 1) {
            flag = 2;
        }
        i++;
    }

    if (sign == -1)
        output = -result;
    else
        output = result;

    return output;
}

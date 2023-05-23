#include "shell.h"
/**
 * **strtow - splits a string into words. Repeat delimiters are ignored
 * @str: the input string
 * @d: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow(char *str, char *d)
{
    int i = 0, j = 0, k, m, numwords = 0;
    char **s;

    if (str == NULL || str[0] == 0)
        return NULL;
    if (!d)
        d = " ";

    while (str[i] != '\0')
    {
        if (!is_delim(str[i], d) && (is_delim(str[i + 1], d) || !str[i + 1]))
            numwords++;
        i++;
    }

    if (numwords == 0)
        return NULL;

    s = malloc((1 + numwords) * sizeof(char *));
    if (!s)
        return NULL;

    i = 0, j = 0;
    while (j < numwords)
    {
        while (is_delim(str[i], d))
            i++;
        k = 0;
        while (!is_delim(str[i + k], d) && str[i + k])
            k++;
        s[j] = malloc((k + 1) * sizeof(char));
        if (!s[j])
        {
            for (k = 0; k < j; k++)
                free(s[k]);
            free(s);
            return NULL;
        }
        m = 0;
        while (m < k)
        {
            s[j][m] = str[i + m];
            m++;
        }
        s[j][m] = '\0';
        i += k;
        j++;
    }

    s[j] = NULL;
    return s;
}
/**
 * **strtow2 - split of the   string into words
 * @str: the inputs of the  strings
 * @d: the delimeters
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **strtow2(char *str, char d)
{
    if (!str || *str == '\0') {
        return NULL;
    }

    int num_words = 0;
    for (char *p = str; *p != '\0'; p++) {
        if (num_words == 0 || *(p - 1) == d) {
            num_words++;
        }
    }

    char **words = malloc((num_words + 1) * sizeof(char *));
    if (!words) {
        return NULL;
    }

    int i = 0;
    for (char *p = strtok(str, &d); p; p = strtok(NULL, &d)) {
        words[i] = strdup(p);
        if (!words[i]) {
            for (int j = 0; j < i; j++) {
                free(words[j]);
            }
            free(words);
            return NULL;
        }
        i++;
    }
    words[i] = NULL;

    return words;
}

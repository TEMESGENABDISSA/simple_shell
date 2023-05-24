#include "shell.h"

/**
 * _myenv - displays the current environment variable
 * @info: Strut contained the  potential arguments and helps to maintain
 *           the constant prototype.
 * Return: Always  returns nothing 0
 * Author : temesgen abdissa and amanuel desalegn
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - setts the value of environment  variable
 * @info: Struct contained the  potential of  arguments. helps to maintain
 * @name: envromental variable name
 * author : temesgen and amanuel
 * Return: values of the variable
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Initial  a new envi variable,
 *             or modify an existing one
 * @info: Structure having  potential arguments.helps to maintain
 *        cons  for the  function prototype.
 *  Return: Always returns nothing  0
 *  author : temesgen abdissa and amanuel desalegn
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv -delete  env variables
 * @info: Stru contain  potential argum and  Used to maintain
 *         prototype.
 *  Return: Always returns nothing zero  0
 *  author: amanuel dessalegn
 */
int _myunsetenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]);

	return (0);
}

/**
 * populate_env_list - assign  env linked list
 * @info: Struc having potential argum and helps to maintain
 *          constant the  function of the  prototype.
 * Return: Always returns nothing zero  0
 * author : amanuel dessalegn and temesgen abdissa
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}

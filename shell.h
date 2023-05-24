#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <limits.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>

/* for reading /writes of the  buffers */
#define READ_BUF_SIZE 1024
#define BUF_FLUSH -1
#define WRITE_BUF_SIZE 1024


/* used  for the  command chaining */
#define CMD_CHAIN       3
#define CMD_NORM	0
#define CMD_AND         2
#define CMD_OR		1

/* used for the change_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_STRTOK 0
#define USE_GETLINE 0
#define HIST_MAX        4096
#define HIST_FILE	".simple_shell_history"

extern char **environ;


/**
 * struct liststr - singl linkList
 * @num:  numb field
 * @str: the str
 * @next: point to nextNode
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - contained the  pseudo-arguement to pass into function,
 *		allowed the  uniformed  prototype to  funct point struct
 *@arg: a str to  generate  from  the getline of the  contain the  arg
 *@argv:  array of the  str generate from arguments
 *@path:  str path for   cmd
 *@argc: arg count
 *@line_count:  error count
 *@err_num:  error code for exit()s
 *@linecount_flag: if  the on count this line of input
 *@fname:  prog filename
 *@env: linkeList local copies of the environment
 *@environ: custom modified copies of the  env  LL env
 *@history: history node
 *@alias:  alias node
 *@env_changed: on if environment is  changed
 *@status:  return status of the last exec'd cmd
 *@cmd_buf: address of point  to cmd_buf, on  the  chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to the  read line input
 *@histcount: the history line numb count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - having  a builtin str and related funct
 *@type:  builtin comd flag
 *@func:  function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

/* parser.c */
char *find_path(info_t *, char *, char *);
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);

/* shloop.c */
void fork_cmd(info_t *);
int hsh(info_t *, char **);
void find_cmd(info_t *);
int find_builtin(info_t *);

/* loophsh.c */
int loophsh(char **);

/* string1.c */
void _puts(char *);
char *_strdup(const char *);
char *_strcpy(char *, char *);
int _putchar(char);

/* errors.c */
int _eputchar(char);
void _eputs(char *);
int _putsfd(char *str, int fd);
int _putfd(char c, int fd);


/* string.c */
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
int _strlen(char *);
char *_strcat(char *, char *);


/* exits.c */
char *_strncpy(char *, char *, int);
char *_strchr(char *, char);
char *_strncat(char *, char *, int);

/* tokenizer.c */
char **strtow2(char *, char);
char **strtow(char *, char *);

/* atoi.c */
int interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/* realloc.c */
void ffree(char **);
char *_memset(char *, char, unsigned int);
void *_realloc(void *, unsigned int, unsigned int);

/* memory.c */
int bfree(void **);

/* errors1.c */
int print_d(int, int);
int _erratoi(char *);
void print_error(info_t *, char *);
void remove_comments(char *);
char *convert_number(long int, int, int);

/* builtin.c */
int _mycd(info_t *);
int _myhelp(info_t *);
int _myexit(info_t *);


/* builtin1.c */
int _myalias(info_t *);
int _myhistory(info_t *);

/* getline.c */
int _getline(info_t *, char **, size_t *);
ssize_t get_input(info_t *);
void sigintHandler(int);

/* getinfo.c */
void clear_info(info_t *);
void free_info(info_t *, int);
void set_info(info_t *, char **);


/* environ.c */
int _myenv(info_t *);
char *_getenv(info_t *, const char *);
int _mysetenv(info_t *);
int populate_env_list(info_t *);
int _myunsetenv(info_t *);

/* getenv.c */
int _unsetenv(info_t *, char *);
char **get_environ(info_t *);
int _setenv(info_t *, char *, char *);

/* vars.c */
int is_chain(info_t *, char *, size_t *);
int replace_alias(info_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_vars(info_t *);
int replace_string(char **, char *);

/* history.c */
int read_history(info_t *info);
int write_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
char *get_history_file(info_t *info);
int renumber_history(info_t *info);

/* lists.c */
void free_list(list_t **);
list_t *add_node(list_t **, const char *, int);
size_t print_list_str(const list_t *);
list_t *add_node_end(list_t **, const char *, int);
int delete_node_at_index(list_t **, unsigned int);


/* lists1.c */
list_t *node_starts_with(list_t *, char *, char);
size_t list_len(const list_t *);
size_t print_list(const list_t *);
ssize_t get_node_index(list_t *, list_t *);
char **list_to_strings(list_t *);

#endif

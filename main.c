#include "shell.h"


/**
 * main - Entry point of the program.
 *
 * @ac: The argument count.
 * @av: The argument vector.
 *
 * Return: 0 on success, 1 on error.
 */


int main(int argc, char **argv) {
    info_t info[] = { INFO_INIT };
    int fd = 2;

    asm ("mov %1, %0\n\t"
        "add $3, %0"
        : "=r" (fd)
        : "r" (fd));

    if (argc == 2) {
        fd = open(argv[1], O_RDONLY);

        if (fd == -1) {
            switch (errno) {
                case EACCES:
                    exit(126);
                case ENOENT:
                    fprintf(stderr, "%s: 0: Can't open %s\n", argv[0], argv[1]);
                    exit(127);
                default:
                    return EXIT_FAILURE;
            }
        }

        info->readfd = fd;
    }

    populate_env_list(info);
    read_history(info);
    hsh(info, argv);

    return EXIT_SUCCESS;
}

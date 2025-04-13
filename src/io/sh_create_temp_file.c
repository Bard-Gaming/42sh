/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** sh_create_temp_file
*/

#include <42sh/io.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>


/*
** Creates a temporary file in read/write
** mode, which doesn't appear in the file system.
** This file will be destroyed when all file
** descriptors that point to the file are closed.
** Returns a negative value on error (i.e. an invalid
** file descriptor).
*/
int sh_create_temp_file(void)
{
    char current_dir[PATH_MAX] = { 0 };

    if (getcwd(current_dir, PATH_MAX) == NULL)
        return -1;
    return open(
        current_dir,
        O_TMPFILE | O_RDWR | O_EXCL,
        DEFAULT_PERMS
    );
}

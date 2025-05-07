/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** shell_interpret_redirect
*/

#include <42sh/shell.h>
#include <42sh/vector.h>
#include <42sh/string.h>
#include <42sh/data.h>
#include <42sh/io.h>
#include <42parser/ast.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


/*
** Utility function to write the standard input
** to the given file descriptor, as long as the
** reference <doc_end> string isn't given.
*/
static void write_to_file_buffer(int fd, const char *doc_end)
{
    char *line = NULL;
    size_t cap = 0;
    ssize_t read_len;

    read_len = getline(&line, &cap, stdin);
    while (read_len > 0) {
        line[read_len - 1] = '\0';
        if (strcmp(doc_end, line) == 0)
            break;
        line[read_len - 1] = '\n';
        (void)!write(fd, line, read_len);
        read_len = getline(&line, &cap, stdin);
    }
    free(line);
}

/*
** Yields a string from a parser node.
** The resulting string needs to be freed
** by the user.
**
** TODO: Add error handling for multiple elements
** in vector.
*/
static char *get_string(ast_t *ast, sh_data_t *data)
{
    sh_vector_t string_container = { 0 };
    char *result;

    shell_interpret_value(ast, data, &string_container);
    result = sh_strjoinvec((const char **)string_container.data, "");
    sh_vector_delete(&string_container, NULL);
    return result;
}

/*
** Redirects one file descriptor to
** another file descriptor. Nothing
** much to add there, is there?..
*/
static void fd_redirect(ast_redirect_t *redirect, sh_data_t *data)
{
    data->io_files[redirect->old_fd] = redirect->new_fd.fd;
}

/*
** Redirects a file path to the given
** file descriptor. The new file descriptor
** needs to be closed, which is why the
** should_close field is set to true for
** the given file descriptor.
**
** Note: The call to free() may not be placed
** before the error handling, as it may modify
** the errno variable and thus mess up the
** error message.
*/
static void file_redirect(ast_redirect_t *redirect, sh_data_t *data)
{
    char *path = get_string(redirect->new_fd.path, data);
    int new_fd = open(path, redirect->open_flags, 0664);

    if (new_fd >= 0) {
        data->io_files[redirect->old_fd] = new_fd;
        data->should_close[redirect->old_fd] = true;
    } else {
        sh_perror(path);
        data->success = false;
    }
    free(path);
}

/*
** Redirects a here-document to the standard
** input. Currently, here-documents only support
** redirecting to stdin, as the io file buffer only
** contains stdin, stdout, and stderr.
** The new file descriptor references a temporary file,
** and should be closed after use (hence why the should_close
** is set to true).
*/
static void heredoc_redirect(ast_redirect_t *redirect, sh_data_t *data)
{
    char *doc_end = get_string(redirect->new_fd.heredoc_end, data);
    int file_buffer = sh_create_temp_file();

    write_to_file_buffer(file_buffer, doc_end);
    free(doc_end);
    lseek(file_buffer, 0, SEEK_SET);
    data->io_files[0] = file_buffer;
    data->should_close[0] = true;
}

/*
** Redirects a string to the standard input.
** As with here-documents, here-string redirections
** only support redirecting to the standard input,
** as the shell's io file buffer only contains redirections
** to stdin, stdout, and stderr as of now.
** The new file descriptor references a temporary file,
** and should be closed after use (hence why the should_close
** is set to true).
*/
static void herestring_redirect(ast_redirect_t *redirect, sh_data_t *data)
{
    char *string = get_string(redirect->new_fd.path, data);
    int file_buffer = sh_create_temp_file();

    sh_dputs(file_buffer, string);
    sh_dputs(file_buffer, "\n");
    free(string);
    lseek(file_buffer, 0, SEEK_SET);
    data->io_files[0] = file_buffer;
    data->should_close[0] = true;
}

/*
** Interprets a command redirection.
** This opens file when necessary, but
** doesn't actually apply any redirections,
** as that is something the shell_exec_command
** function does later on.
*/
void shell_interpret_redirect(ast_t *ast, sh_data_t *data,
    UNUSED sh_vector_t *argv)
{
    ast_redirect_t *redirect = ast->data;

    switch (redirect->type) {
    case RT_FILE_DESCRIPTOR:
        return fd_redirect(redirect, data);
    case RT_FILE_PATH:
        return file_redirect(redirect, data);
    case RT_HEREDOC_END:
        return heredoc_redirect(redirect, data);
    case RT_HERESTRING:
        return herestring_redirect(redirect, data);
    }
}

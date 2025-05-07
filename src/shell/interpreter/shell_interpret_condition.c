/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** shell_interpret_condition
*/

#include <42sh/shell.h>
#include <42sh/vector.h>
#include <42sh/string.h>
#include <42sh/data.h>


/*
** Runs the test command with the
** parsed arguments. This allows
** for conditions such as:
** ( a == b )
** ( 3 -gt 2 )
** etc...
**
*/
static bool test_condition(ast_node_buffer_t *args, sh_data_t *data)
{
    sh_vector_t argv = { 0 };
    int status;

    sh_vector_push_back(&argv, sh_strdup("test"));
    for (size_t i = 0; i < args->count; i++)
        shell_interpret_value(args->nodes[i], data, &argv);
    status = shell_exec_command((char **)argv.data, data);
    sh_vector_delete(&argv, NULL);
    return status == 0;
}

/*
** Interprets a condition.
** This functions isn't really a node interpretation
** function, but more of a helper function to facilitate
** the interpretation of ast nodes.
*/
bool shell_interpret_condition(ast_condition_t *condition, sh_data_t *data)
{
    if (!condition->is_command)
        return test_condition(condition->condition.test_args, data);
    shell_interpret(condition->condition.command, data);
    return data->exit_status == 0;
}

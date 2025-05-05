/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** sh_data_register &&
** sh_data_get
*/

#include <42sh/data.h>

/*
** Static getter function for the data pointer,
** which is required as it can't get passed as
** an argument by the parser.
*/
static sh_data_t **get_data_ptr(void)
{
    static sh_data_t *data = NULL;

    return &data;
}

/*
** Setter function for the data singleton.
** This registers the given data ptr to be
** the one used by the global singleton.
*/
void sh_data_register(sh_data_t *data)
{
    *get_data_ptr() = data;
}

/*
** Getter function for the data singleton.
** Retrieves the data pointer registered
** using the sh_data_register function.
*/
sh_data_t *sh_data_get(void)
{
    return *get_data_ptr();
}

/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** symbol_table_create
*/

#include <42sh/symbols.h>
#include <stdlib.h>


/*
** Create a symbol table with default
** values. Returns NULL on error.
*/
sh_symbols_t *sh_symbols_create(void)
{
    sh_symbols_t *table = malloc(sizeof(sh_symbols_t));

    if (table == NULL)
        return NULL;
    table->data = NULL;
    table->count = 0;
    table->capacity = 0;
    return table;
}

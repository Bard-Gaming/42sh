/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** symbol_table_create
*/

#include <42sh/symbols.h>
#include <42sh/memory.h>


/*
** Create a symbol table with default
** values.
*/
sh_symbols_t *sh_symbols_create(void)
{
    sh_symbols_t *table = shmalloc(sizeof(sh_symbols_t));

    table->data = NULL;
    table->count = 0;
    table->capacity = 0;
    return table;
}

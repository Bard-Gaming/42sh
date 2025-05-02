/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** sh_symbols_unset
*/

#include <42sh/symbols.h>
#include <stdlib.h>


/*
** Unsets a given symbol from the symbol
** table. Does nothing if the given symbol
** doesn't exist.
*/
void sh_symbols_unset(sh_symbols_t *table, const char *name)
{
    size_t index;

    if (table->capacity == 0)
        return;
    index = sh_symbols_hash(table, name);
    if (table->data[index].name == NULL)
        return;
    free(table->data[index].name);
    free(table->data[index].value);
    table->data[index].name = NULL;
    table->data[index].value = NULL;
    table->count--;
}

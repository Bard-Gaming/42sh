/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** sh_symbols_get
*/

#include <42sh/symbols.h>


/*
** Returns a symbol's value based on the
** given symbol name.
** If the symbol name doesn't exist, NULL
** is returned instead.
*/
const char *sh_symbols_get(const sh_symbols_t *table, const char *name)
{
    size_t index;

    if (table->capacity == 0 || table->count == 0)
        return NULL;
    index = sh_symbols_hash(table, name);
    return table->data[index].value;
}

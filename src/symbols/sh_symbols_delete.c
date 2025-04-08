/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** sh_symbols_delete
*/

#include <42sh/symbols.h>
#include <stdlib.h>


/*
** Deletes a symbol table, as well
** as all of its allocated data.
** Does nothing if the given ptr is NULL.
*/
void sh_symbols_delete(sh_symbols_t *table)
{
    if (table == NULL)
        return;
    for (size_t i = 0; i < table->capacity; i++) {
        free(table->data[i].name);
        free(table->data[i].value);
    }
    free(table->data);
    free(table);
}

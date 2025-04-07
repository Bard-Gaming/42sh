/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** sh_symbols_dup
*/

#include <42sh/symbols.h>
#include <stdlib.h>
#include <string.h>


/*
** Create an independent copy / duplicate
** of a given symbol table.
*/
sh_symbols_t *sh_symbols_dup(const sh_symbols_t *ref_table)
{
    sh_symbols_t *dup = sh_symbols_create();

    dup->count = ref_table->count;
    dup->capacity = ref_table->capacity;
    dup->data = calloc(dup->capacity, sizeof(struct sh_symbol_bucket));
    for (size_t i = 0; i < dup->capacity; i++) {
        if (ref_table->data[i].name == NULL)
            continue;
        dup->data[i].name = strdup(ref_table->data[i].name);
        dup->data[i].value = strdup(ref_table->data[i].value);
    }
    return dup;
}

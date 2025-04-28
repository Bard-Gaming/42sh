/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** sh_symbols_dup
*/

#include <42sh/symbols.h>
#include <42sh/memory.h>
#include <string.h>


/*
** Create an independent copy / duplicate
** of a given symbol table.
*/
sh_symbols_t *sh_symbols_dup(const sh_symbols_t *ref_table)
{
    sh_symbols_t *dup = shmalloc(sizeof(sh_symbols_t));

    dup->count = ref_table->count;
    dup->capacity = ref_table->capacity;
    dup->data = shcalloc(ref_table->capacity, sizeof(struct sh_symbol_bucket));
    for (size_t i = 0; i < ref_table->capacity; i++) {
        if (ref_table->data[i].name == NULL)
            continue;
        dup->data[i].name = strdup(ref_table->data[i].name);
        dup->data[i].value = strdup(ref_table->data[i].value);
    }
    return dup;
}

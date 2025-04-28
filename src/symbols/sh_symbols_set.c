/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** sh_symbols_set
*/

#include <42sh/symbols.h>
#include <42sh/memory.h>
#include <stdlib.h>
#include <string.h>


/*
** Grows the table's buffer by the
** SH_SYMBOLS_GROWTH_FACTOR constant.
*/
static void grow_table(sh_symbols_t *table)
{
    struct sh_symbol_bucket *old_buffer = table->data;
    size_t old_capacity = table->capacity;
    size_t new_index;

    table->capacity = old_capacity == 0 ? SH_SYMBOLS_INIT_CAP :
        old_capacity * SH_SYMBOLS_GROWTH_FACTOR;
    table->data = shcalloc(table->capacity, sizeof(struct sh_symbol_bucket));
    for (size_t i = 0; i < old_capacity; i++) {
        if (old_buffer[i].name == NULL)
            continue;
        new_index = sh_symbols_hash(table, old_buffer[i].name);
        table->data[new_index].name = old_buffer[i].name;
        table->data[new_index].value = old_buffer[i].value;
    }
    free(old_buffer);
}

/*
** Sets a value in the symbol table.
** If the given value is already set,
** the old value is overwritten.
*/
void sh_symbols_set(sh_symbols_t *table, const char *name, const char *value)
{
    size_t index;

    if ((double)table->count >= SH_SYMBOLS_LOAD_FACTOR * table->capacity)
        grow_table(table);
    index = sh_symbols_hash(table, name);
    if (table->data[index].name == NULL) {
        table->data[index].name = strdup(name);
        table->count++;
    }
    free(table->data[index].value);
    table->data[index].value = strdup(value);
}

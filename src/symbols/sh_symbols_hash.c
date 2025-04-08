/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** sh_symbols_hash
*/

#include <42sh/symbols.h>
#include <string.h>


/*
** Hash a given name into a usable index
** between 0 and the given capacity (exclusive)
*/
static size_t hash(const char *restrict name, size_t cap)
{
    size_t hash = 0;

    for (size_t i = 0; name[i] != '\0'; i++)
        hash = (hash + name[i] + i) * 13;
    return hash % cap;
}

/*
** Determines whether or not a given index
** is a valid candidate for the name.
** An index is a valid slot for the name if:
** - The slot is empty
** - The slot is storing a value of the same name
*/
static bool is_valid_slot(const sh_symbols_t *tb, const char *name, size_t i)
{
    return
        tb->data[i].name == NULL ||
        strcmp(tb->data[i].name, name) == 0;
}

/*
** Hashes a name into a usable table entry
** index.
*/
size_t sh_symbols_hash(const sh_symbols_t *table, const char *name)
{
    size_t index = hash(name, table->capacity);

    while (!is_valid_slot(table, name, index))
        index = (index + 1) % table->capacity;
    return index;
}

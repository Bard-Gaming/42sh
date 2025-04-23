/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** sh_symbols_print
*/

#include <42sh/symbols.h>
#include <stdio.h>


/*
** Prints all symbols from the symbol
** table in the following format:
** <name> <sep> <value>
** where sep is user-defined.
*/
void sh_symbols_print(const sh_symbols_t *table, const char *sep)
{
    for (size_t i = 0; i < table->capacity; i++) {
        if (table->data[i].name == NULL)
            continue;
        printf("%s%s%s\n", table->data[i].name, sep, table->data[i].value);
    }
}

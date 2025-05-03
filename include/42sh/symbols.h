/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Header file for everything
** related to the shell's symbol
** tables (used for local and env
** variables)
*/

#ifndef SHELL_SYMBOL_TABLE_H
    #define SHELL_SYMBOL_TABLE_H

    #define SH_SYMBOLS_INIT_CAP 20
    #define SH_SYMBOLS_GROWTH_FACTOR 1.5
    #define SH_SYMBOLS_LOAD_FACTOR 0.8

    #include <42sh/types.h>
    #include <stddef.h>


struct sh_symbol_bucket {
    char *name;
    char *value;
};


struct sh_symbols {
    struct sh_symbol_bucket *data;
    size_t capacity;
    size_t count;
};


// Table creation / deletion:
sh_symbols_t *sh_symbols_create(void);
void sh_symbols_delete(sh_symbols_t *table);

// Basic operations:
sh_symbols_t *sh_symbols_dup(const sh_symbols_t *ref_table);
void sh_symbols_set(sh_symbols_t *table, const char *name, const char *value);
const char *sh_symbols_get(const sh_symbols_t *table, const char *name);
void sh_symbols_unset(sh_symbols_t *table, const char *name);
void sh_symbols_print(const sh_symbols_t *table, const char *sep);
bool sh_symbols_parse(sh_symbols_t *table, const char *args[]);

// Internal:
size_t sh_symbols_hash(const sh_symbols_t *table, const char *name);


#endif

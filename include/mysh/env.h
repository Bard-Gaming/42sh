/*
** EPITECH PROJECT, 2024
** Project - Minishell 1
** File description:
** Header file for everything
** related to env management
*/

#ifndef MYSH_ENV_H
    #define MYSH_ENV_H
    #include <stddef.h>
    #include <mysh/types.h>
    #define SH_ENV_INITIAL_CAPACITY 5
    #define SH_ENV_GROWTH_FACTOR 1.5


struct sh_env_item {
    char *variable;
    const char *value;
};


struct sh_env {
    struct sh_env_item *items;
    size_t count;
    size_t capacity;
};


sh_env_t *sh_env_create(void);
void sh_env_delete(sh_env_t *env);

// Reading from env:
const char *sh_env_get(const sh_env_t *env, const char *name);

// Update existing env:
void sh_env_set(sh_env_t *env, const char *name, const char *value);
void sh_env_put(sh_env_t *env, const char *item_value);
void sh_env_unset(sh_env_t *env, const char *name);

// Unix env:
char **sh_env_to_unix(const sh_env_t *env);
sh_env_t *sh_env_from_unix(const char **unix_env);
void sh_env_delete_unix(char **env);


#endif

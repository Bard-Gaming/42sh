/*
** EPITECH PROJECT, 2024
** Project - 42sh
** File description:
** Header file for everything
** related to local shell data
*/

#ifndef MYSH_DATA_H
    #define MYSH_DATA_H
    #include <mysh/types.h>


struct sh_data {
    sh_env_t *env;              // own env (def: NULL)
    unsigned char exit_status;  // exit status of last exec (def: 0)

    // Internal data:
    char *home_dir;
    char *previous_dir;
    int io_files[3];
};


sh_data_t *sh_data_create(void);
void sh_data_delete(sh_data_t *data);
sh_data_t *sh_data_from_unix_env(char *envp[]);


#endif

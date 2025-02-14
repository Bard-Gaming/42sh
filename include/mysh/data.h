/*
** EPITECH PROJECT, 2024
** Project - Minishell 1
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
};


sh_data_t *sh_data_create(void);
void sh_data_delete(sh_data_t *data);


#endif

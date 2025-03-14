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

    #define IS_PIPE_IN(state) (state & CS_PIPE_IN)
    #define IS_PIPE_OUT(state) (state & CS_PIPE_OUT)


enum sh_command_state {
    CS_NORMAL,  // keep first

    CS_PIPE_IN = 1,      // 2^0 -> 01
    CS_PIPE_OUT = 2,     // 2^1 -> 10
    CS_PIPE_IN_OUT = 3,  // IN + OUT -> 2^1 + 2^0 -> 11
};


struct sh_data {
    sh_env_t *env;              // own env (def: NULL)
    unsigned char exit_status;  // exit status of last exec (def: 0)

    // Internal data:
    char *home_dir;
    char *previous_dir;

    // Redirections:
    sh_command_state_t cmd_state;
    int read_file;
    int write_file;
};


sh_data_t *sh_data_create(void);
void sh_data_delete(sh_data_t *data);
sh_data_t *sh_data_from_unix_env(char *envp[]);


#endif

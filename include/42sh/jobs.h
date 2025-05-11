/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Header file for the shell's
** jobs
*/

#ifndef SHELL_JOBS_H
    #define SHELL_JOBS_H
    #include <42sh/types.h>
    #include <sys/types.h>


struct sh_job {
    pid_t pid;
    char state;
    char *command;
};


sh_job_t *sh_job_create(pid_t pid);
void sh_job_update_state(sh_job_t *job);
void sh_job_update_command(sh_job_t *job);
void sh_job_delete(sh_job_t *job);


#endif

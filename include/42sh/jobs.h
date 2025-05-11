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


enum sh_job_state {
    JS_RUNNING,
    JS_STOPPED,
    JS_DONE,
};


struct sh_job {
    pid_t pid;
    sh_job_state_t state;
};


sh_job_t *sh_job_create(pid_t pid);
void sh_job_update_state(sh_job_t *job);
char *sh_job_get_command(const sh_job_t *job);


#endif

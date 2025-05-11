/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** sh_job_create
*/

#include <42sh/jobs.h>
#include <42sh/memory.h>


/*
** Creates a job from the given process id.
*/
sh_job_t *sh_job_create(pid_t pid)
{
    sh_job_t *job = shmalloc(sizeof(sh_job_t));

    job->pid = pid;
    sh_job_update_state(job);
    return job;
}

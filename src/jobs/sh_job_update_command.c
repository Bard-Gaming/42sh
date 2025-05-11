/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** sh_job_update_command
*/

#include <42sh/jobs.h>
#include <42sh/memory.h>
#include <string.h>
#include <stdio.h>



/*
** Opens the file in the proc file system
** that corresponds with the job's processes'
** stat file.
**
** Technical Addendum:
** A maximum length of 25 is chosen, as it is
** the maximum possible amount of characters required
** to store the given path format (an integer has
** at most 11 chars, with the remaining 10 being
** the "/proc" and "/cmdline", as well as the terminating
** null byte).
**
*/
static FILE *job_cmdline_open(const sh_job_t *job, const char *modes)
{
    char path[25];

    snprintf(path, 25, "/proc/%d/cmdline", job->pid);
    return fopen(path, modes);
}

/*
** Function to return when the given
** line is in an invalid format.
*/
static short invalid_line(char *line)
{
    free(line);
    return -1;
}

/*
** Searches the proc file system
** for the processes' command.
** This returns a valid, null-terminated
** string if successful, and NULL if not.
*/
static char *query_job_command(const sh_job_t *job)
{
    FILE *file = job_cmdline_open(job, "rt");

    if (file == NULL)
        return NULL;

}

/*
** Function to return when the job's command
** is unknown.
*/
static void unknown_command(sh_job_t *job)
{
    job->command = NULL;
}

/*
** Updates a job's command.
** The command is updated using information
** from the proc file system.
** If updating the job's command fails, its
** command field will be set to NULL.
*/
void sh_job_update_command(sh_job_t *job)
{
    if (job->pid < 0)
        return unknown_command(job);
    job->command = query_job_command(job);
}

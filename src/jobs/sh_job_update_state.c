/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** sh_job_update_state
*/

#include <42sh/jobs.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdio.h>


/*
** Opens the file in the proc file system
** that corresponds with the job's processes'
** stat file.
**
** Technical Addendum:
** A maximum length of 22 is chosen, as it is
** the maximum possible amount of characters required
** to store the given path format (an integer has
** at most 11 chars, with the remaining 10 being
** the "/proc" and "/stat", as well as the terminating
** null byte).
**
*/
static FILE *job_stat_open(const sh_job_t *job, const char *modes)
{
    char path[22];

    snprintf(path, 22, "/proc/%d/stat", job->pid);
    return fopen(path, modes);
}

/*
** Searches the proc file system
** for a process state. This returns the
** state character if successful, and -1 if
** not.
** If this function is successful, the result
** is guaranteed to be in the range of [0; 127].
*/
static short query_job_state(const sh_job_t *job)
{
    FILE *stat_file = job_stat_open(job, "rt");
    short result;
    char state;

    if (stat_file == NULL)
        return -1;
    result =
        fscanf(stat_file, "%*d %*s %c", &state) == 1 ?
        state : -1;
    fclose(stat_file);
    return result;
}

/*
** Function to return when the state
** of the job is unknown.
*/
static void unknown_state(sh_job_t *job)
{
    job->state = 'U';
}

/*
** Updates a job's state using its
** process ID and the /proc filesystem.
** If the state couldn't be determines,
** it will be set to 'U' (for "Unknown").
*/
void sh_job_update_state(sh_job_t *job)
{
    short state;

    if (job->pid < 0)
        return unknown_state(job);
    state = query_job_state(job);
    if (state < 0)
        return unknown_state(job);
    job->state = state;
}

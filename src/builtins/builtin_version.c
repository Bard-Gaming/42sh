/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** builtin_version
*/

#include <42sh/builtins.h>
#include <42sh/symbols.h>
#include <42sh/string.h>
#include <42sh/shell.h>
#include <42sh/data.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


/*
** Note: I know this looks like garbage,
** but it looks good when using the shell,
** I promise!
**
** Other note:
** The empty string ("") after the equals
** sign is required so not as to trip up
** the coding style checker...
**
** (formatted using script)
*/
static const char *version_format = ""
    "____________/\\\\\\_______/\\\\\\\\\\\\\\\\\\___________________/\\\\\\__"
    "_______            \033[1;94m%s\033[0m@\033[1;94m%s\033[0m\n __________/"
    "\\\\\\\\\\_____/\\\\\\///////\\\\\\________________\\/\\\\\\_________    "
    "       ----------------\n  ________/\\\\\\/\\\\\\____\\///______\\//\\\\"
    "\\_______________\\/\\\\\\_________          \033[1;92mShell\033[0m: 42sh"
    "\n   ______/\\\\\\/\\/\\\\\\______________/\\\\\\/____/\\\\\\\\\\\\\\\\\\"
    "\\_\\/\\\\\\_________         \033[1;92mVersion\033[0m: %s\n    ____/\\\\"
    "\\/__\\/\\\\\\___________/\\\\\\//_____\\/\\\\\\//////__\\/\\\\\\\\\\\\\\"
    "\\\\\\__        \033[1;92mShell Path\033[0m: %s\n     __/\\\\\\\\\\\\\\\\"
    "\\\\\\\\\\\\\\\\_____/\\\\\\//________\\/\\\\\\\\\\\\\\\\\\\\_\\/\\\\\\//"
    "///\\\\\\_       \033[1;92mConfig Files\033[0m: %s\n      _\\///////////"
    "\\\\\\//____/\\\\\\/___________\\////////\\\\\\_\\/\\\\\\___\\/\\\\\\_   "
    "   \033[1;92mLogin shell\033[0m: %s\n       ___________\\/\\\\\\_____/\\"
    "\\\\\\\\\\\\\\\\\\\\\\\\\\\\__/\\\\\\\\\\\\\\\\\\\\_\\/\\\\\\___\\/\\\\\\"
    "_     \033[1;92mInteractive\033[0m: %s\n        ___________\\///_____\\//"
    "/////////////__\\//////////__\\///____\\///__    \033[1;92mHistory size"
    "\033[0m: \033[1;93m%lu\033[0m\n                                          "
    "                                   \033[1;92mWork Directory\033[0m: %s\n "
    "               __  __       _ _   _     _          _ _                   "
    "   \033[1;92mEnvironment Variables\033[0m: \033[1;93m%lu\033[0m\n        "
    "       |  \\/  |     | | | (_)   | |        | | |                     "
    "\033[1;92mLocal Variables\033[0m: \033[1;93m%lu\033[0m\n               | "
    "\\  / |_   _| | |_ _ ___| |__   ___| | |                     \033[1;92mAl"
    "iases\033[0m: \033[1;93m%lu\033[0m\n               | |\\/| | | | | | __| "
    "/ __| '_ \\ / _ \\ | |                     \033[1;92mPID\033[0m: "
    "\033[1;93m%d\033[0m\n               | |  | | |_| | | |_| \\__ \\ | | |  _"
    "_/ | |\n               |_|  |_|\\__,_|_|\\__|_|___/_| |_|\\___|_|_|\n\n\n"
;


/*
** Retrieves the hostname from
** /etc/hostname
*/
static char *get_hostname(void)
{
    FILE *hostfile = fopen("/etc/hostname", "rt");
    char *result = NULL;
    ssize_t read_len;
    size_t cap = 0;

    if (hostfile == NULL)
        return sh_strdup("unknown");
    read_len = getline(&result, &cap, hostfile);
    fclose(hostfile);
    if (read_len <= 0) {
        free(result);
        return sh_strdup("unknown");
    }
    result[read_len - 1] = '\0';
    return result;
}

static char *get_config_file(const sh_data_t *data)
{
    struct stat stat_buf = { 0 };
    const char *home_dir = sh_data_getvar(data, "HOME");
    char *config_path = sh_strjoin(home_dir, SHELL_RC_PATH);

    if (stat(config_path, &stat_buf) != 0) {
        free(config_path);
        return sh_strdup("None");
    }
    free(config_path);
    return sh_strjoin("~", SHELL_RC_PATH);
}

/*
** Determines whether or not 42sh
** is the user's login shell.
*/
static bool is_login_shell(const sh_data_t *data)
{
    const char *login_shell = sh_symbols_get(data->env_internal, "SHELL");
    char *login_shell_basename = sh_basename(login_shell);
    bool result = strcmp(login_shell_basename, "42sh") == 0;

    free(login_shell_basename);
    return result;
}

/*
** Implementation for the shell's builtin
** version command.
** This command displays shell information
** in a nice format.
*/
int builtin_version(UNUSED char *args[], sh_data_t *data)
{
    char *hostname = get_hostname();
    char *cwd = shell_getcwd(data, false);
    char *config_file = get_config_file(data);
    bool is_login = is_login_shell(data);

    printf(
        version_format,
        sh_data_getvar(data, "USER"), hostname,
        SHELL_VERSION, data->shell_path, config_file,
        is_login ? "yes" : "no", isatty(0) ? "yes" : "no",
        shell_history_count(), cwd, data->env->count,
        data->local_vars->count, data->aliases->count, getpid()
    );
    free(cwd);
    free(hostname);
    free(config_file);
    return 0;
}

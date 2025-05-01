/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** builtin_version
*/

#include <42sh/builtins.h>
#include <42sh/symbols.h>
#include <42sh/shell.h>
#include <42sh/data.h>
#include <unistd.h>
#include <stdio.h>


static const char *version_format =
R"(____________/\\\_______/\\\\\\\\\___________________/\\\_________)"
"            %s@%s\n"
R"( __________/\\\\\_____/\\\///////\\\________________\/\\\_________)"
"           ----------------\n"
R"(  ________/\\\/\\\____\///______\//\\\_______________\/\\\_________)"
"          Shell: 42sh\n"
R"(   ______/\\\/\/\\\______________/\\\/____/\\\\\\\\\\_\/\\\_________)"
"         Version: %s\n"
R"(    ____/\\\/__\/\\\___________/\\\//_____\/\\\//////__\/\\\\\\\\\\__)"
"        Shell Path: %s\n"
R"(     __/\\\\\\\\\\\\\\\\_____/\\\//________\/\\\\\\\\\\_\/\\\/////\\\_)"
"       Sourcing Files: %s\n"
R"(      _\///////////\\\//____/\\\/___________\////////\\\_\/\\\___\/\\\_)"
"      Login shell: %s\n"
R"(       ___________\/\\\_____/\\\\\\\\\\\\\\\__/\\\\\\\\\\_\/\\\___\/\\\_)"
"     Interactive: %s\n"
R"(        ___________\///_____\///////////////__\//////////__\///____\///__)"
"    History size: %lu\n"
"                                                                             "
"Work Directory: %s\n"
R"(                __  __       _ _   _     _          _ _)"
"                      Environment Variables: %lu\n"
R"(               |  \/  |     | | | (_)   | |        | | |)"
"                     Local Variables: %lu\n"
R"(               | \  / |_   _| | |_ _ ___| |__   ___| | |)"
"                     Aliases: %lu\n"
R"(               | |\/| | | | | | __| / __| '_ \ / _ \ | |)"
"                     PID: %d\n"
R"(               | |  | | |_| | | |_| \__ \ | | |  __/ | |)""\n"
R"(               |_|  |_|\__,_|_|\__|_|___/_| |_|\___|_|_|)""\n\n\n";


/*
** Implementation for the shell's builtin
** version command.
** This command displays shell information
** in a nice format.
*/
int builtin_version(char *args[], sh_data_t *data)
{
    (void)args;
    printf(
        version_format,
        sh_data_getvar(data, "USER"), "TEMP",
        SHELL_VERSION, data->shell_path, SHELL_RC_PATH,
        "yes", isatty(0) ? "yes" : "no", 1000, "~",
        data->env->count, data->local_vars->count,
        0, getpid()
    );
    return 0;
}

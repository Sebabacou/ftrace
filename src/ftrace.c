/*
** EPITECH PROJECT, 2024
** B-PSU-400-REN-4-1-ftrace-hugo.murat
** File description:
** trace
*/

#include "ftrace.h"
#include "utils.h"

static void set_trace(char **args)
{
    int pt_err;
    int ex_err;

    pt_err = ptrace(PT_TRACE_ME, 0, NULL, NULL);
    ex_err = execvp(args[0], args);
    if (pt_err == -1 || ex_err == -1)
        exit_error(UNDEF_ERR);
}

void run_ftrace(char **args)
{
    pid_t child_pid = fork();

    if (child_pid == -1)
        exit_error(UNDEF_ERR);
    if (child_pid == 0) {
        set_trace(args);
    } else {
        return;
    }
}

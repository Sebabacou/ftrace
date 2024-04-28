/*
** EPITECH PROJECT, 2024
** ftrace-mirror
** File description:
** signal
*/

#include "c_syscall.h"
#include "ftrace.h"
#include "utils.h"
#include "call_type.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

void print_sig(int sig)
{
    fprintf(stderr, "Received signal %s\n", strsignal(sig));
}

void exit_program_sig(int sig)
{
    fprintf(stderr, "Received signal %s\n", strsignal(sig));
    exit(84);
}

void signal_handler(int status, pid_t child_pid) {
    int term_sig;
    int stop_sig;

    if (WIFSIGNALED(status)) {
        term_sig = WTERMSIG(status);
        if (term_sig != SIGTRAP) {
            fprintf(stderr, "Received signal %s\n", strsignal(term_sig));
            exit(84);
        }
    }
    if (WIFSTOPPED(status)) {
        stop_sig = WSTOPSIG(status);
        if (stop_sig == SIGTRAP)
            return;
        if (stop_sig == SIGCONT || stop_sig == SIGWINCH || stop_sig == SIGCHLD
        || stop_sig == SIGUSR1 || stop_sig == SIGUSR2 || stop_sig == SIGHUP ||
        stop_sig == SIGALRM)
            print_sig(stop_sig);
        else
            exit_program_sig(stop_sig);
        }
}

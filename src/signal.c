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
        stop_sig = WSTOPSIG(status);
        if (stop_sig == SIGTRAP)
            return;
        if (stop_sig == SIGABRT || stop_sig == SIGFPE || stop_sig == SIGILL
        || stop_sig == SIGINT || stop_sig == SIGSEGV || stop_sig == SIGQUIT
        || stop_sig == SIGBUS || stop_sig == SIGQUIT || stop_sig == stop_sig 
        || stop_sig == SIGXCPU || stop_sig == SIGXFSZ || stop_sig == SIGPIPE
        || stop_sig == SIGTERM)
            exit_program_sig(stop_sig);
        else
            print_sig(stop_sig);
    }
    if (WIFSTOPPED(status)) {
        stop_sig = WSTOPSIG(status);
        if (stop_sig == SIGTRAP)
            return;
        if (stop_sig == SIGABRT || stop_sig == SIGFPE || stop_sig == SIGILL
        || stop_sig == SIGINT || stop_sig == SIGSEGV || stop_sig == SIGQUIT
        || stop_sig == SIGBUS || stop_sig == SIGQUIT || stop_sig == stop_sig 
        || stop_sig == SIGXCPU || stop_sig == SIGXFSZ || stop_sig == SIGPIPE
        || stop_sig == SIGTERM)
            exit_program_sig(stop_sig);
        else
            print_sig(stop_sig);
    }
}

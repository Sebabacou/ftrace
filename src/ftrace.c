/*
** EPITECH PROJECT, 2024
** B-PSU-400-REN-4-1-ftrace-hugo.murat
** File description:
** trace
*/

#include "c_syscall.h"
#include "ftrace.h"
#include "utils.h"
#include "call_type.h"

static void set_trace(char **args)
{
    int pt_err;
    int ex_err;

    pt_err = ptrace(PT_TRACE_ME, 0, NULL, NULL);
    ex_err = execvp(args[0], args);
    if (pt_err == -1 || ex_err == -1)
        exit_error(UNDEF_ERR);
}

static void find_call_type(int pid, char *argv, struct user_regs_struct *regs)
{
    int status;
    unsigned long instruction;

    instruction = ptrace(PTRACE_PEEKTEXT, pid, regs->rip, NULL);
    switch (instruction & 0xFF) {
        case 0xe8:
            e8_finder(instruction, pid, regs, argv);
            break;
        default:
            break;
        }
}

static void trace(char *args, pid_t child_pid)
{
    struct user_regs_struct regs;
    int status;
    int pt_err;

    do {
        pt_err = ptrace(PTRACE_GETREGS, child_pid, NULL, &regs);
        if (pt_err == -1)
            exit_error(UNDEF_ERR);
        if ((int) regs.orig_rax != -1) {
            print_syscall(&regs);
        } else {
            find_call_type(child_pid, args, &regs);
        }
        pt_err = ptrace(PTRACE_SINGLESTEP, child_pid, NULL, NULL);
        if (pt_err == -1)
            exit_error(UNDEF_ERR);
        wait4(child_pid, &status, 0, NULL);
    } while (!WIFEXITED(status));
}

void run_ftrace(char *args)
{
    pid_t child_pid = fork();
    int status;
    int pt_err;

    if (child_pid == -1)
        exit_error(UNDEF_ERR);
    if (child_pid == 0) {
        set_trace(&args);
    } else {
        wait4(child_pid, &status, 0, NULL);
        pt_err = ptrace(PTRACE_SETOPTIONS, child_pid, NULL,
            PTRACE_O_TRACEEXIT);
        if (pt_err == -1)
            exit_error(UNDEF_ERR);
        trace(args, child_pid);
    }
}

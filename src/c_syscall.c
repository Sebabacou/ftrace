/*
** EPITECH PROJECT, 2024
** ftrace [WSL: Ubuntu]
** File description:
** syscall
*/

#include "c_syscall.h"

static void print_unknown(ullong_t orig_rax, ullong_t *regs, ullong_t rax)
{
    fprintf(stderr, "syscall_0x%lld(", orig_rax);
    for (size_t i = 0; i < 6; i++) {
        if (i > 0)
            fprintf(stderr, ", ");
        fprintf(stderr, "0x%llx", regs[i]);
    }
    fprintf(stderr, ") = 0x%llx\n", rax);
}

static void print_hexa(syscall_t *syscall, ullong_t *regs, ullong_t rax)
{
    size_t i = 0;

    while (i < syscall->param_nb) {
        if (i > 0)
            fprintf(stderr, ", ");
        fprintf(stderr, "0x%llx", regs[i]);
        i++;
    }
    if (syscall->params[i] == VOID) {
        fprintf(stderr, ") = ?\n");
    } else {
        fprintf(stderr, ") = 0x%llx\n", rax);
    }
}

void print_syscall(struct user_regs_struct *regs)
{
    ullong_t regs_arr[6] = {regs->rdi, regs->rsi, regs->rdx, regs->rcx,
        regs->r8, regs->r9};

    if (regs->orig_rax > MAX_SYSCALL) {
        print_unknown(regs->orig_rax, regs_arr, regs->rax);
        return;
    }
    fprintf(stderr, "Syscall %s(", TABLE[regs->orig_rax].name);
    print_hexa(&TABLE[regs->orig_rax], regs_arr, regs->rax);
}

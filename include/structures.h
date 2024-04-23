/*
** EPITECH PROJECT, 2024
** B-PSU-400-REN-4-1-strace-hugo.murat [WSL: Ubuntu]
** File description:
** structures
*/

#pragma once

#include "commons.h"

/* Structure defined to contain informations about a syscall. */
typedef struct syscall_s {
    size_t num;
    char *name;
    size_t param_nb;
    size_t params[7];
} syscall_t;

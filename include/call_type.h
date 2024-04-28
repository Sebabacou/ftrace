/*
** EPITECH PROJECT, 2024
** ftrace
** File description:
** call_type.h
*/

#pragma once

#include "stack.h"

/**
 * @brief structure for the finder
 *
 * @param instruction instruction to check
 * @param pid process id
 * @param regs registers
 * @param argv name of the file
 * @param stack stack of the functions
 */
typedef struct finder_s {
    unsigned long instruction;
    int pid;
    struct user_regs_struct *regs;
    char *argv;
    fstack_t **stack;
} finder_t;

/**
 * @brief find the e8 call in the instruction
 *
 * @param finder structure with the instruction
 * @return true if the call is found
 */
bool e8_finder(finder_t *finder);

/*
** EPITECH PROJECT, 2024
** ftrace
** File description:
** call_type.h
*/

#pragma once

/**
 * @brief find the e8 call in the instruction
 *
 * @param instruction instruction to check
 * @param pid process id
 * @param regs registers
 * @param argv name of the file
 * @return true if the call is found
 */
bool e8_finder(unsigned long instruction, int pid, struct user_regs_struct
    *regs, char *argv);

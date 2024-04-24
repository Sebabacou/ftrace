/*
** EPITECH PROJECT, 2024
** B-PSU-400-REN-4-1-ftrace-hugo.murat
** File description:
** trace
*/

#pragma once

#include "commons.h"

/**
 * @brief Run the ftrace program.
 *
 * @param args Array of string containing
 * the command to trace and its arguments.
 */
void run_ftrace(char **args);

/**
 * @brief Find the symbol corresponding to the given address.
 *
 * @param filename The filename of the elf file.
 * @param addr The address to find.
 * @return true If the symbol is found.
 */
bool find_symbol(char *filename, Elf64_Addr addr);

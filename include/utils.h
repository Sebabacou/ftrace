/*
** EPITECH PROJECT, 2024
** B-PSU-400-REN-4-1-ftrace-hugo.murat
** File description:
** utils
*/

#pragma once

#include "commons.h"


#define USAGE_MSG "USAGE: ftrace <command>\n"


/* Undefined error. */
#define UNDEF_ERR 0
/* Invalid number of arguments passed to the program. */
#define INV_ARG_NB 1


/**
 * @brief Exit the program with a `84` code an display an
 * error message depending on the flag passed as parameter.
 *
 * @param reason Flag specifying the error.
 */
void exit_error(int reason);


/**
 * @brief Check if the given string is the help flag. If so,
 * display help message and leave the program with `0` code.
 *
 * @param str String to check.
 */
void check_help_flag(const char *str);


/**
 * @brief Display an usage message about the program.
 *
 */
void display_help(void);

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
/* Error during memory allocation. */
#define MALLOC_ERR 2

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


/**
 * @brief Split a string into an array of words.
 *
 * @param str The string to split.
 * @param token The token to split the string with.
 * @return char** The array of words.
 */
char **my_str_to_word_array(char const *str, char *token);

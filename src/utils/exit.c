/*
** EPITECH PROJECT, 2024
** B-PSU-400-REN-4-1-ftrace-hugo.murat
** File description:
** exit
*/

#include "utils.h"

void exit_error(int reason)
{
    if (reason == UNDEF_ERR)
        fprintf(stderr, "An error occurred during execution.\n");
    if (reason == INV_ARG_NB)
        fprintf(stderr, "Missing argument.\n");
    if (reason == MALLOC_ERR)
        fprintf(stderr, "An error occurred during memory allocation.\n");
    exit(84);
}

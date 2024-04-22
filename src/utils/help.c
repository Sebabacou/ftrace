/*
** EPITECH PROJECT, 2024
** B-PSU-400-REN-4-1-ftrace-hugo.murat
** File description:
** help
*/

#include "utils.h"

void display_help(void)
{
    printf(USAGE_MSG);
}

void check_help_flag(const char *str)
{
    int cmp = strcmp(str, "-h");

    if (cmp != 0) {
        cmp = strcmp(str, "--help");
        if (cmp != 0)
            return;
    }
    display_help();
    exit(0);
}

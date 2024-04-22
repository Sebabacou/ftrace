/*
** EPITECH PROJECT, 2024
** B-PSU-400-REN-4-1-ftrace-hugo.murat
** File description:
** main
*/

#include "ftrace.h"
#include "utils.h"

int main(int ac, char **av)
{
    if (ac < 2)
        exit_error(INV_ARG_NB);
    check_help_flag(av[1]);
    run_ftrace(&av[1]);
    return 0;
}

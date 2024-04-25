/*
** EPITECH PROJECT, 2024
** ftrace
** File description:
** 0xe8_finder.c
*/

#include "ftrace.h"
#include "commons.h"
#include "utils.h"

static bool loop_through_maps(int pid, long reg_offset, char *argv,
    FILE *maps_file)
{
    char line[256];
    char **tab;
    long start;
    long end;

    while (fgets(line, sizeof(line), maps_file) != NULL) {
        tab = my_str_to_word_array(line, " ");
        sscanf(tab[0], "%lx-%lx", &start, &end);
        if (reg_offset >= start && reg_offset <= end) {
            reg_offset = reg_offset - start + strtol(tab[2], NULL, 16);
            find_symbol(argv, reg_offset);
            return true;
        }
    }
    return false;
}

static bool parse_proc_maps(int pid, long reg_offset, char *argv)
{
    char path[256];
    FILE *maps_file;
    bool found;

    sprintf(path, "/proc/%d/maps", pid);
    maps_file = fopen(path, "r");
    if (maps_file == NULL) {
        perror("fopen");
        return false;
    }
    found = loop_through_maps(pid, reg_offset, argv, maps_file);
    fclose(maps_file);
    if (found == false)
        return false;
    return true;
}

bool e8_finder(unsigned long instruction, int pid, struct user_regs_struct
    *regs, char *argv)
{
    long reg_offset;

    reg_offset = (int) instruction >> 8;
    reg_offset = reg_offset + 4 + 1 + regs->rip;
    return parse_proc_maps(pid, reg_offset, argv);
}

/*
** EPITECH PROJECT, 2024
** ftrace
** File description:
** 0xe8_finder.c
*/

#include "ftrace.h"
#include "utils.h"
#include "call_type.h"

static bool loop_through_maps(long reg_offset, FILE *maps_file, finder_t
    *finder)
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
            find_symbol(finder->argv, reg_offset, finder->stack);
            return true;
        }
    }
    return false;
}

static bool parse_proc_maps(finder_t *finder, long reg_offset)
{
    char path[256];
    FILE *maps_file;
    bool found;

    sprintf(path, "/proc/%d/maps", finder->pid);
    maps_file = fopen(path, "r");
    if (maps_file == NULL) {
        perror("fopen");
        return false;
    }
    found = loop_through_maps(reg_offset, maps_file, finder);
    fclose(maps_file);
    if (found == false)
        return false;
    return true;
}

bool e8_finder(finder_t *finder)
{
    long reg_offset;

    reg_offset = (int) finder->instruction >> 8;
    reg_offset = reg_offset + 4 + 1 + finder->regs->rip;
    return parse_proc_maps(finder, reg_offset);
}

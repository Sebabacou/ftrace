/*
** EPITECH PROJECT, 2024
** ftrace
** File description:
** 9a_finder.c
*/

#include "ftrace.h"
#include "utils.h"
#include "call_type.h"

static bool loop_through_maps_9a(long reg_offset, long segment, FILE *maps_file, finder_t *finder)
{
    char line[256];
    char **tab;
    long start;
    long end;

    while (fgets(line, sizeof(line), maps_file) != NULL) {
        tab = my_str_to_word_array(line, " ");
        sscanf(tab[0], "%lx-%lx", &start, &end);
        if (reg_offset >= start && reg_offset <= end && segment == strtol(tab[1], NULL, 16)) {
            reg_offset = reg_offset - start + strtol(tab[2], NULL, 16);
            find_symbol(finder->argv, reg_offset, finder->stack);
            return true;
        }
    }
    return false;
}

bool parse_proc_maps_9a(finder_t *finder, long reg_offset, long segment)
{
    FILE *maps_file;
    char maps_path[256];
    bool found = false;

    sprintf(maps_path, "/proc/%d/maps", finder->pid);
    maps_file = fopen(maps_path, "r");
    if (maps_file == NULL) {
        perror("fopen");
        return false;
    }
    found = loop_through_maps_9a(reg_offset, segment, maps_file, finder);
    fclose(maps_file);
    return found;
}

bool _9a_finder(finder_t *finder)
{
    long reg_offset;
    long segment;

    reg_offset = (int) (finder->instruction & 0xFFFF);
    segment = (int) ((finder->instruction >> 16) & 0xFFFF);

    reg_offset += segment << 4;

    return parse_proc_maps_9a(finder, reg_offset, segment);
}
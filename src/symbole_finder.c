/*
** EPITECH PROJECT, 2024
** bs
** File description:
** symbole_finder.c
*/

#include "commons.h"
#include "ftrace.h"

static bool checker(char *filename, Elf **elf, int *fd)
{
    if (elf_version(EV_CURRENT) == EV_NONE) {
        perror("elf_version");
        return false;
    }
    *fd = open(filename, O_RDONLY);
    if (*fd < 0) {
        perror("open");
        return false;
    }
    *elf = elf_begin(*fd, ELF_C_READ, NULL);
    if (*elf == NULL) {
        perror("elf_begin");
        return false;
    }
    return true;
}

static bool loop_elf(sym_finder_t *sym_f, int count, Elf64_Addr addr)
{
    int i = 0;

    for (i = 0; i < count; ++i) {
        gelf_getsym(sym_f->data, i, &sym_f->sym);
        if (sym_f->sym.st_value == addr) {
            dprintf(2, "Symbol found: %s\n", elf_strptr(sym_f->elf,
                sym_f->shdr.sh_link, sym_f->sym.st_name));
            return true;
        }
    }
    return false;
}

bool find_symbol(char *filename, Elf64_Addr addr)
{
    sym_finder_t sym_f;
    int fd;
    int count;

    if (!checker(filename, &sym_f.elf, &fd))
        return false;
    sym_f.scn = elf_nextscn(sym_f.elf, sym_f.scn);
    while (sym_f.scn != NULL) {
        gelf_getshdr(sym_f.scn, &sym_f.shdr);
        if (sym_f.shdr.sh_type != SHT_SYMTAB)
            continue;
        sym_f.data = elf_getdata(sym_f.scn, NULL);
        count = sym_f.shdr.sh_size / sym_f.shdr.sh_entsize;
        if (loop_elf(&sym_f, count, addr) == true)
            return true;
        sym_f.scn = elf_nextscn(sym_f.elf, sym_f.scn);
    }
    dprintf(2, "Symbol not found.\n");
    return false;
}

/*
** EPITECH PROJECT, 2024
** bs
** File description:
** symbole_finder.c
*/

#include "commons.h"


bool checker(char *filename, Elf **elf)
{
    int fd;

    if (elf_version(EV_CURRENT) == EV_NONE) {
        perror("elf_version");
        return false;
    }
    fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("open");
        return false;
    }
    *elf = elf_begin(fd, ELF_C_READ, NULL);
    if (*elf == NULL) {
        perror("elf_begin");
        return false;
    }
    return true;
}

bool loop_symbols(Elf *elf, Elf_Scn *scn, Elf64_Addr addr)
{
    GElf_Shdr shdr;
    Elf_Data *data;
    int i;
    int count;
    GElf_Sym sym;

    gelf_getshdr(scn, &shdr);
    if (shdr.sh_type != SHT_SYMTAB)
        return false;
    data = elf_getdata(scn, NULL);
    count = shdr.sh_size / shdr.sh_entsize;
    for (i = 0; i < count; ++i) {
        gelf_getsym(data, i, &sym);
        if (sym.st_value == addr) {
            dprintf(2, "Entering function %s at 0x%lx\n", elf_strptr(elf,
                shdr.sh_link, sym.st_name), addr);
            return true;
        }
    }
    return false;
}

int find_symbol(char *filename, Elf64_Addr addr)
{
    Elf *elf;
    Elf_Scn *scn = NULL;

    checker(filename, &elf);
    scn = elf_nextscn(elf, scn);
    while (scn != NULL) {
        if (loop_symbols(elf, scn, addr))
            return true;
        scn = elf_nextscn(elf, scn);
    }
    dprintf(2, "Symbol not found.\n");
    return false;
}

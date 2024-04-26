/*
** EPITECH PROJECT, 2024
** ftrace
** File description:
** stack.c
*/

#include "stack.h"
#include "utils.h"

void fstack_push(fstack_t **stack, char *function_name, Elf64_Addr address)
{
    fstack_t *new_node = (fstack_t *)malloc(sizeof(fstack_t));

    if (new_node == NULL) {
        dprintf(2, "Erreur d'allocation de mémoire\n");
        exit_error(MALLOC_ERR);
    }
    new_node->function_name = function_name;
    new_node->address = address;
    new_node->next = *stack;
    dprintf(2, "Entering function %s at 0x%lx\n", function_name, address);
    *stack = new_node;
}

void fstack_pop(fstack_t **stack)
{
    fstack_t *temp;

    if (*stack == NULL) {
        return;
    }
    temp = *stack;
    *stack = (*stack)->next;
    dprintf(2, "Leaving function %s\n", temp->function_name);
    free(temp);
}

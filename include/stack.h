/*
** EPITECH PROJECT, 2024
** ftrace
** File description:
** stack.h
*/

#pragma once

#include <elf.h>

/*
 * @brief Structure for the stack
 *
 * @param function_name The name of the function
 * @param address The address of the function
 * @param next The next element of the stack
 */
typedef struct fstack_s {
    char *function_name;
    Elf64_Addr address;
    struct fstack_s *next;
} fstack_t;

/*
 * @brief Push a new element to the stack
 *
 * @param stack The stack to push to
 * @param function_name The name of the function
 * @param address The address of the function
 */
void fstack_push(fstack_t **stack, char *function_name, Elf64_Addr address);

/*
 * @brief Pop the first element of the stack
 *
 * @param stack The stack to pop
 */
void fstack_pop(fstack_t **stack);

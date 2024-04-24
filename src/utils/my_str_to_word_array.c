/*
** EPITECH PROJECT, 2024
** myftp
** File description:
** my_str_to_word_array.c
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

void free_tab(char **tab)
{
    int i = 0;

    if (tab == NULL)
        return;
    for (i = 0; tab[i]; i++)
        free(tab[i]);
    free(tab);
}

int is_token(char const *token, char letter)
{
    for (int i = 0; token[i]; i++) {
        if (token[i] == letter)
            return 1;
    }
    return 0;
}

int count_word(char const *str, char *token)
{
    int count = 0;
    size_t len = strlen(str);

    if (str == NULL)
        return 0;
    for (size_t i = 0; i < len; i++) {
        if (is_token(token, str[i]) &&
            !is_token(token, str[i + 1]))
            count++;
    }
    return count + (len > 0 && !is_token(token, str[len - 1]));
}

static size_t token_skip(char const *token, size_t len, char const *str,
    size_t *save)
{
    size_t i = 0;

    for (i = 0; is_token(token, str[i]) && i < len; i++)
        *save += 1;
    return i;
}

static size_t set_check(int *check, size_t len, char const *str,
    char const *token)
{
    size_t i = 0;

    for (i = 0; !is_token(token, str[i]) && i < len; *check += 1)
        i++;
    return i;
}

static int put_in_tab(char **tab, size_t len, char const *str, char *token)
{
    int z = 0;
    int check;
    size_t save;

    for (size_t i = 0; i < len; i++) {
        check = 0;
        save = i;
        i += token_skip(token, len - i, &str[i], &save);
        i += set_check(&check, len - i, &str[i], token);
        tab[z] = malloc(sizeof(char) * (check + 1));
        if (tab[z] == NULL)
            return 84;
        for (int j = 0; j != check; save++) {
            tab[z][j] = str[save];
            j++;
        }
        tab[z][check] = '\0';
        z++;
    }
    return 0;
}

char **my_str_to_word_array(char const *str, char *token)
{
    size_t len = strlen(str);
    int nb_word = count_word(str, token);
    char **tab = malloc(sizeof(char *) * (nb_word + 1));

    for (int i = 0; i <= nb_word; i++)
        tab[i] = NULL;
    if (tab == NULL || str == NULL || str[0] == '\0') {
        free(tab);
        return NULL;
    }
    if (put_in_tab(tab, len, str, token) == 84) {
        free_tab(tab);
        return NULL;
    }
    if (tab[nb_word - 1] != NULL && tab[nb_word -1][0] == '\0')
        tab[nb_word -1] = NULL;
    tab[nb_word] = NULL;
    return tab;
}

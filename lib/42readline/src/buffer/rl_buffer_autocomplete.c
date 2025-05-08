/*
** EPITECH PROJECT, 2025
** Project - 42readline
** File description:
** Implementation for
** rl_prompt_autcomplete
*/

#include <readline/buffer.h>
#include <readline/internal.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


/*
** Retrieves the index of the beginning of
** the currently selected word.
*/
static size_t get_word_start(const char *str, size_t start_index)
{
    if (start_index != 0)
        start_index--;
    if (*str == '\0')
        return 0;
    while (start_index > 0 && rl_is_word_char(str[start_index]))
        start_index--;
    return start_index + !rl_is_word_char(str[start_index]);
}

/*
** Essentially a strdup(), except that this
** function stops at the first occurrence of
** a non-word character.
*/
static char *duplicate_word(const char *buffer)
{
    size_t len;

    for (len = 0; buffer[len] != '\0' && rl_is_word_char(buffer[len]); len++);
    return strndup(buffer, len);
}

/*
** Autocompletes the selected word
** in the string buffer.
*/
void rl_buffer_autocomplete(void)
{
    string_buffer_t *buffer = rl_buffer_get();
    size_t word_start = get_word_start(buffer->data, buffer->arrow_index);
    char *word = duplicate_word(buffer->data + word_start);
    char *autocompletion = buffer->autocomplete(word);
    size_t word_len;

    if (autocompletion == NULL)
        return;
    word_len = strlen(word);
    free(word);
    buffer->arrow_index = word_start + word_len;
    for (size_t i = word_len; autocompletion[i] != '\0'; i++)
        rl_buffer_add_char(autocompletion[i]);
    free(autocompletion);
}

/*
** Long autocompletion.
** This doesn't actually autocomplete anything,
** but prints all possible autocompletions.
*/
void rl_buffer_autocomplete_long(void)
{
    string_buffer_t *buffer = rl_buffer_get();
    size_t word_start = get_word_start(buffer->data, buffer->arrow_index);
    char *word = duplicate_word(buffer->data + word_start);

    putchar('\n');
    buffer->autocomplete_long(word);
    free(word);
}

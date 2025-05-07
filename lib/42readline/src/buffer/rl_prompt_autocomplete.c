/*
** EPITECH PROJECT, 2025
** multishell
** File description:
** rl_prompt_autcomplete
*/

#include <readline.h>
#include <readline/buffer.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static size_t get_last_word_index(const char *str)
{
    size_t len = strlen(str);

    while (len > 0 && str[len - 1] != ' ' && str[len - 1] != '\t' &&
        str[len - 1] != '|' && str[len - 1] != ';')
        len--;
    return len;
}

static void replace_last_word(string_buffer_t *buffer,
    const char *replacement, size_t start)
{
    size_t new_len = start + strlen(replacement);
    char *new_buffer = malloc(new_len + 1);

    if (!new_buffer)
        return;
    strncpy(new_buffer, buffer->data, start);
    strcpy(new_buffer + start, replacement);
    new_buffer[new_len] = '\0';
    free(buffer->data);
    buffer->data = new_buffer;
    buffer->count = new_len;
    buffer->arrow_index = new_len;
}

void rl_handle_autocompletion(void)
{
    string_buffer_t *buffer = rl_buffer_get();
    size_t start;
    char *prefix;
    char *temp;

    buffer->tabulation_count += 1;
    start = get_last_word_index(buffer->data);
    prefix = strdup(&buffer->data[start]);
    temp = buffer->autocomplete(prefix, buffer->tabulation_count);
    free(prefix);
    if (!temp)
        return;
    replace_last_word(buffer, temp, start);
    free(temp);
}

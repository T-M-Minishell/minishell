/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 19:17:27 by tlupu             #+#    #+#             */
/*   Updated: 2024/07/04 18:19:18 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int words_count(const char *str, char c)
{
    int i;
    int word;
    bool is_quote;
    i = 0;
    word = 0;
    is_quote = false;
    while (str[i] != '\0')
    {
        if (str[i] == '\"')
        {
            is_quote = !is_quote;
            if (is_quote)
                word++;
        }
        else if (!is_quote && ((i == 0 || str[i - 1] == c || str[i] == '|') && str[i] != c))
            word++;
        i++;
    }
    if (is_quote)
    {
        printf("Error: missing quote\n");
        return (-1);
    }
    return (word);
}
int allocate_for_strings(const char *str, char c)
{
    int i;
    int l;
    int keep_quotes;
    bool is_quote;
    i = 0;
    l = 0;
    keep_quotes = 0;
    is_quote = false;
    while (str[i] != '\0' && (is_quote || str[i] != c))
    {
        if (str[i] == '\"')
        {
            keep_quotes++;
            is_quote = !is_quote;
            i++;
            continue;
        }
        else if (str[i] == '|')
        {
            i++;
            break;
        }
        l++;
        i++;
    }
    return (l);
}
// looks for the desired string keeping in mind all the special operators such as "",
t_word_info string_gen(const char *str, char c)
{
    int i;
    bool is_quote;
    int j;
    int alloc;
    t_word_info word_info;
    word_info.word = NULL;
    i = 0;
    j = 0;
    is_quote = false;
    alloc = 0;
    alloc = allocate_for_strings(str, c);
    word_info.word = (char *)malloc(sizeof(char) * (alloc + 1));
    if (!word_info.word)
        return word_info;
    while (str[i] != '\0' && (is_quote || str[i] != c))
    {

        if (str[i] == '"')
        {
            if (is_quote && str[i + 1] != ' ' && str[i + 1] != '\0')
            {
                word_info.word[j] = str[i];
            }
            is_quote = !is_quote;
            i++;
            continue;
        }
        else if (str[i] == '|')
        {
            word_info.word[j++] = str[i++];
            word_info.details = PIPE_PRES;
        }
        if (str[i] != '\0' && (is_quote || str[i] != c))
        {
            word_info.word[j++] = str[i++];
        }
    }
    // printf("j is :%d\n", j);
    word_info.word[j] = '\0';
    word_info.char_counted = i;
    return (word_info);
}

char **custom_split(const char *str, char c)
{
    int i;
    int index_array;
    char **arr;
    int word_length;
    t_word_info word_info;
    i = 0;
    index_array = 0;
    word_length = words_count(str, c);
    if (word_length == -1)
        return (NULL);
    arr = (char **)malloc(sizeof(char *) * (word_length + 1));
    if (!arr)
    {
        printf("Allocation has failed\n");
        return (NULL);
    }
    while (index_array < word_length)
    {
        word_info = string_gen((char *)(str + i), c);
        if (word_info.details == PIPE_PRES)
        {
            
            word_info.details = NO_PIPPE_PRES;
        }
        
        arr[index_array] = word_info.word;
        // printf("arr contents are: %s\n", arr[index_array]);
        i += word_info.char_counted;
        while (str[i] == c)
            i++;
        index_array++;
    }
    arr[word_length] = NULL;
    return (arr);
}

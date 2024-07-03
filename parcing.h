/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlupu <tlupu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:51:28 by tlupu             #+#    #+#             */
/*   Updated: 2024/07/02 11:01:08 by tlupu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARCING_H
# define PARCING_H

// # include "minishell.h"

typedef enum s_token_type
{
	END,
	ERROR,
	PIPE,
	WORD,
	REDIRECT,
	QUOTE,
}						t_token_type;

typedef struct s_list_token
{
	t_token_type		type;
	int					index;
	
	char				*word;
	char 				**arr;

	struct s_list_token	*next;
	struct s_list_token	*prev;
}						t_list_token;

typedef struct s_word_info
{
    char    *word;
    int     char_counted;
}           t_word_info;

typedef struct s_word_info_redirect
{
    char    **arr;
	t_token_type token;
	struct  s_word_info_redirect *next;
}           t_word_info_redirect;

#endif

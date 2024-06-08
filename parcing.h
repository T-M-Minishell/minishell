/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlupu <tlupu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:51:28 by tlupu             #+#    #+#             */
/*   Updated: 2024/06/03 17:08:00 by tlupu            ###   ########.fr       */
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
	int					type;
	int					index;
	char				*word;
	char				*arr;
	char 				*pipe;
	char 				*redirect;
    char                *input;
    char                *output;
	char				*quotes;
	struct s_list_token	*next;
	struct s_list_token	*prev;
}						t_list_token;

#endif

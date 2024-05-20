#ifndef PARCING_H
# define PARCING_H

# include "minishell.h"

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
	char				**arr;
	char 				*pipe;
	char 				*redirect;
    char                *input;
    char                *output;
	char				*quotes;
	struct s_list_token	*next;
	struct s_list_token	*prev;
}						t_list_token;

#endif

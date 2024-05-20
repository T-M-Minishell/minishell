#include "minishell.h"

t_list_token	*ft_lstnew_init(void)
{
	t_list_token *new;

	new = (t_list_token *)malloc(sizeof(t_list_token));
	if (!new)
		return (NULL);
	new->index = 0;
	new->type = 0;
	new->arr = NULL;
	new->quotes = NULL;
	new->word = NULL;
	new->pipe = NULL;
	new->redirect = NULL;
	new->input = NULL;
	new->output = NULL;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}
#include "minishell.h"

//debug functions

void print_node(t_list_token *node) {
    if (node == NULL) {
        printf("Node is NULL\n");
        return;
    }

    printf("Node content:\n");
    printf("Index: %d\n", node->index);
    printf("Type: %d\n", node->type);
    printf("Quotes: %s\n", node->quotes);
    printf("Word: %s\n", node->word);
    printf("Pipe: %s\n", node->pipe);
    printf("Redirect: %s\n", node->redirect);
    printf("Input: %s\n", node->input);
    printf("Output: %s\n", node->output);
    // Print other fields as needed
}

void	assign_token_to_redirect(char *line, t_list_token **data,
		t_token_type token)
{
	int				start_index;
	char			*str_token;
	t_list_token	*new_node;

	start_index = (*data)->index;
	/// De vazut cum fac cu multiple redirecturi
	while (line[(*data)->index] != '\0')
		(*data)->index++;
	str_token = ft_strdnup(line + start_index, (*data)->index - start_index);
	new_node = ft_lstnew(str_token, token);
	if (new_node == NULL)
	{
		free(str_token);
		free_token_list(data);
		return ;
	}
	new_node->index = (*data)->index;
	ft_lstadd_back(data, new_node);
	// ask sazymon how to handle multiple pipes if anything else shohulkd be skipped here in the end
}

void	assign_token_to_pipe(char *line, t_list_token **data,
		t_token_type token)
{
	int				start_index;
	char			*str_token;
	t_list_token	*new_node;

	start_index = (*data)->index;
	//De vazut cum fac cu multiple pipeuri
	while (line[(*data)->index] != '\0')
		(*data)->index++;
	str_token = ft_strdnup(line + start_index, (*data)->index - start_index);
	new_node = ft_lstnew(str_token, token);
	if (new_node == NULL)
	{
		free(str_token);
		free_token_list(data);
		return ;
	}
	new_node->index = (*data)->index;
	ft_lstadd_back(data, new_node);
	// ask sazymon how to handle multiple pipes if anything else shohulkd be skipped here in the end
}


void	assign_token_to_quote(char *line, t_list_token **data,
		t_token_type token)
{
	int				start_index;
	char			*str_token;
	t_list_token	*new_node;

	(*data)->index++;
	start_index = (*data)->index; 
	printf("from here :%d\n", start_index);
	while (line[(*data)->index] != '"' && line[(*data)->index] != '\0')
		(*data)->index++;
	printf("to here :%d\n\n", (*data)->index);
	str_token = ft_strdnup(line + start_index, (*data)->index - start_index);
	printf("str_tok is :%s\n\n\n", str_token);
	new_node = ft_lstnew(str_token, token);
	// print_node(new_node);
	if (new_node == NULL)
	{
		free(str_token);
		free_token_list(data);
		return ;
	}
	new_node->index = (*data)->index;
	ft_lstadd_back(data, new_node);
	(*data)->index++;
}

//assign to word

void	assign_token_to_word(char *line, t_list_token **data,
		t_token_type token)
{
	int				start_index;
	char			*str_token;
	t_list_token	*new_node;

	start_index = (*data)->index;
	while (line[(*data)->index] != ' ' && line[(*data)->index] != '\0')
		(*data)->index++;
	str_token = ft_strdnup(line + start_index, (*data)->index - start_index);
	new_node = ft_lstnew(str_token, token);
	if (new_node == NULL)
	{
		free(str_token);
		free_token_list(data);
		return ;
	}
	new_node->index = (*data)->index;
	ft_lstadd_back(data, new_node);
	while (line[(*data)->index] == ' ')
	{
		if (line[(*data)->index] == '\0')
			return ;
		(*data)->index++;
	}
}

// O functie ajutatatuare pt redus de liniim, practic trimite individual,
// bazat pe ce tip de data avem,
// catre o functie care va assignui ce in now catre tipul corespunzator de data

void	assign_token_to_list(char *line, t_token_type token,
		t_list_token **data)
{
	if (token == QUOTE)
		assign_token_to_quote(line, data, token);
	else if (token == WORD)
		assign_token_to_word(line, data, token);
	else if (token == PIPE)
		assign_token_to_pipe(line, data, token);
	else if (token == REDIRECT)
		assign_token_to_redirect(line, data, token);
}
// This function checks for the data type by assigning enum values and returns them back to main
// These "<" || ">" || "|" IF NOT any of these => WORD
t_token_type	check_token(char *str, t_list_token **data)
{
	while ((is_space(&str[(*data)->index])))
		(*data)->index++;
	while (str[(*data)->index] != '\0')
	{
		while ((is_space(&str[(*data)->index])))
		{
			if (str[(*data)->index] == '\0')
				return (END);
			(*data)->index++;
		}
		if (str[(*data)->index] == '"')
			return (QUOTE);
		else if (str[(*data)->index] != '|' && str[(*data)->index] != '<'
			&& str[(*data)->index] != '>' && str[(*data)->index] != '"')
			return (WORD);
		else if (str[(*data)->index] == '|')
			return (PIPE);
		else if (str[(*data)->index] == '>' || str[(*data)->index] == '<')
			return (REDIRECT);
		(*data)->index++;
	}
	return (END);
}

// int	main(void)
// {
// 	char			*prompt;
// 	char			*line1;
// 	t_token_type	token;
// 	t_list_token	*data;
// 	t_list_token	*curr;

// 	prompt = "minishell$";
// 	data = NULL;
// 	line1 = NULL;
// 	data = ft_lstnew_init();
// 	while (1)
// 	{
// 		printf("%s ", prompt);
// 		line1 = readline("");
// 		token = END;
// 		while ((token = check_token(line1, &data)) != END)
// 			assign_token_to_list(line1, token, &data);
// 		curr = data->next;
// 		while (curr != NULL && curr->quotes != NULL)
// 		{
// 			printf("%s\n", curr->quotes);
// 			curr = curr->next;
// 		}
// 		if (line1 == NULL)
// 			break ;
// 		add_history(line1);
// 		free(line1);
// 	}
// 	return (0);
// }

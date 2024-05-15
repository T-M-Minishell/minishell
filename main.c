
#include "minishell.h"


///assignation

void	assign_token_to_word(char *line, t_list_token **data)
{
	int				start_index;
	char			*str_token;
	t_list_token	*new_node;

	start_index = (*data)->index;
	while (line[(*data)->index] != ' ' && line[(*data)->index] != '\0')
		(*data)->index++;
	str_token = ft_strdnup(line + start_index, (*data)->index - start_index);
	new_node = ft_lstnew(str_token);
	if (new_node == NULL)
	{
		free(str_token);
		free_token_list(data);
		return ;
	}
	new_node->word = str_token;
	new_node->index = (*data)->index;
	ft_lstadd_back(data, new_node);
	while (line[(*data)->index] == ' ' && line[(*data)->index] != '\0')
		(*data)->index++;
}

// O functie ajutatatuare pt redus de liniim, practic trimite individual,
// bazat pe ce tip de data avem,
// catre o functie care va assignui ce in now catre tipul corespunzator de data

void	assign_token_to_list(char *line, t_token_type token,
		t_list_token **data)
{
	if (token == WORD)
		assign_token_to_word(line, data);
	// else if (token == WORD)
	// 	assign_token_to_word(line, data);
	// else if (token == PIPE)
	// 	assign_token_to_pipe(line, data);
	// else if (token == REDIRECT)
	// 	assign_token_to_redirect(line, data);
	// else if (token == END)
	// 	fct_to_handle(line, data);
}
// This function checks for the data type by assigning enum values and returns them back to main
// These "<" || ">" || "|" IF NOT any of these => WORD
t_token_type	check_token(char *str, t_list_token **data)
{
	// if (str[(*data)->index] == '\0')
	// 	return (END);
	while (str[(*data)->index] != '\0')
	{
		while (str[(*data)->index] == ' ')
		{
			if (str[(*data)->index] == '\0')
				return (END);
			(*data)->index++;
		}
		if (str[(*data)->index] == '"')
			return (QUOTE);
		else if (str[(*data)->index] != '|' && str[(*data)->index] != '<'
			&& str[(*data)->index] != '>' && str[(*data)->index] != '"')
			{
				return (WORD);
				continue;
			}
		else if (str[(*data)->index] == '|')
			return (PIPE);
		else if (str[(*data)->index] == '>' || str[(*data)->index] == '<')
			return (REDIRECT);
		// intamplat enumeratia, practic mergem cu fata de la fiecare return
		// de continuat de folosit indexul din struct, pt a avea exact unde s a
		(*data)->index++;
	}
	return (END);
}

int	main(void)
{
	char			*prompt;
	char			*line1;
	t_token_type	token;
	t_list_token	*data;
	t_list_token 	*curr;

	prompt = "minishell$";
	data = NULL;
	line1 = NULL;
	data = ft_lstnew(NULL);
	data->index = 0;
	while (1)
	{
		printf("%s ", prompt);
		line1 = readline("");
		token = check_token(line1, &data); // Check input type
		assign_token_to_list(line1, token, &data);
		curr = data->next;
		while (curr != NULL && curr->word != NULL)
		{
			printf("%s\n",curr->word);
			curr = curr->next;
		}
		if (line1 == NULL)
			break ;
		add_history(line1);
		free(line1);
	}
	return (0);
}
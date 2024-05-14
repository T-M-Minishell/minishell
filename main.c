
#include "minishell.h"

void 	assign_token_to_list(char *line, t_token_type token, t_list_token **data)
{
	//bazat pe indexul din struct imi pot da seama ce tip de variabila am si unde sa o pun in lista.
	//este correct
}

t_token_type 	check_token(char *str, t_list_token **data)   //This function checks for the data type by assigning enum values and returns them back to main
{
	int i;

	i = 0;
	if (str[(*data)->index] == '\0')
				return(END);
	while (str[(*data)->index] != '\0')
	{
		while (str[(*data)->index] == ' ')
		{
			if (str[(*data)->index] == '\0')
				return(END);
			i++;
		}
		if (str[(*data)->index] != '|' && str[(*data)->index] != '<' && str[(*data)->index] != '>') //These "<" || ">" || "|" IF NOT any of these => WORD	 
			return(WORD);
		else if (str[(*data)->index] == '|')
			return(PIPE);
		else if (str[(*data)->index] == '>' || str[(*data)->index] == '<')
			return(REDIRECT);
		
	}
	return(END); ////de continuat de folosit indexul din struct, pt a avea exact unde s a intamplat enumeratia, practic mergem inapoi cu spatele de la fiecare return 
}

int main() {
	char *prompt = "minishell$ ";
	char *line1;
	t_token_type token;
	t_list_token *data;

	data = NULL;
	while (1) {
		printf("%s ", prompt);
		line1 = readline("");
		token = check_token(line1, &data); //Check input type
		assign_token_to_list(line1 ,token, &data);
		if (line1 == NULL) 
			break;
		add_history(line1);
		free(line1);
	}
	return 0;
}

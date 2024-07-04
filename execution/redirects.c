/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 15:17:35 by msacaliu          #+#    #+#             */
/*   Updated: 2024/07/03 17:43:27 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redirect_output(char *command, char *output)
{
	int fd = open(output,O_WRONLY | O_CREAT, 0777);
	if(fd == -1)
	{
		perror("error fd\n");
		return ;
	}
	int fd2 = dup2(fd,STDOUT_FILENO);

	if(fd2 == -1)
	{
		perror("fd2 error\n");
		return ;
	}
	printf("%s\n",command);
		close(fd);
}

int	count_redirects(t_list_token *data)
{
	t_list_token *curr;
	int i = 0;

	curr = data;
	while (curr != NULL)
	{
		if (strcmp(curr->word, ">") == 0 || strcmp(curr->word, "<") == 0
			|| strcmp(curr->word, ">>") == 0 || strcmp(curr->word, "<<") == 0)
			i++;
		curr = curr->next;
	}
	return i + 1;
}
		///////// testing
void	handle_redirects(t_list_token *data, env_var *vars)
{
	t_list_token *curr;
	curr = data;
	// char **argv;
	(void)vars;
	int i = 0;
	int j = 0;

	i = count_redirects(data);

    while (j < i && curr != NULL) 
    {
        while (curr != NULL && (strcmp(curr->word, "<") != 0 && strcmp(curr->word, ">") != 0
			&& strcmp(curr->word, "<<") != 0 && strcmp(curr->word, ">>") != 0))
        {
            curr = curr->next;
        }
          if (curr != NULL)
		{
			curr->red = curr->word;
			printf("--------red: %s\n", curr->red);
			curr = curr->next; 
		}
		j++;
    }

}



//  while (j < i && curr != NULL) 
//     {
//         while (curr != NULL && (strcmp(curr->word, "<") != 0 && strcmp(curr->word, ">") != 0
// 			&& strcmp(curr->word, "<<") != 0 && strcmp(curr->word, ">>") != 0))
//         {
//             printf("curr->word = %s\n", curr->word);
//             curr = curr->next;
//         }
//         // printf("000000\n");
//         if (curr != NULL)
// 		{
// 			curr->red = curr->word;
// 			printf("--------red: %s\n", curr->red);
// 			curr = curr->next; 
// 		}
// 		j++;
//     }
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 16:21:50 by msacaliu          #+#    #+#             */
/*   Updated: 2024/05/20 15:15:11 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 1. echo with option -n

void	mini_echo(t_list_token *data)
{
	t_list_token *curr;

	curr = data;
	curr = curr->next;
	int	print_new_line = 1; 
	//check for -n function
	if(curr->word != NULL && strcmp(curr->word, "-n") == 0)
	{
	
		print_new_line = 0; //supress new_line when -n 
		curr = curr->next;
	}
	
	// print each arg with space
	while(curr != NULL)  /// problem here when i put quotes
	{
		printf("%s ", curr->word);
    	curr = curr->next;
	}
	 // print new_line if -n is not specified
	 if(print_new_line)
	 	printf("\n");
}

/// change directory
int mini_cd(t_list_token *data)
{
	t_list_token *curr;

	curr = data;
	curr = curr->next;
	
    if (curr->word == NULL)
	{  // No argument, use HOME directory
        if (chdir(getenv("HOME")) != 0)
		{
            perror("cd");
            return 1;
        }
    }
	else
	{  // Change directory to the provided path
        if (chdir(curr->word) != 0)
		{
            perror("cd");
            return 1;
        }
    }
    return 0;
}
 // view in wich directory you are
void	mini_pwd(void)
{
    char *cwd = getcwd(NULL, 0);  // Get current working directory
    if (cwd == NULL)
        perror("pwd");
    else
	{
        printf("%s\n", cwd);
        free(cwd);  // Free memory
    }
}

void	mini_exit(void)
{
	printf("exit\n");
    exit(0); 
}

void	min_env(t_list_token *data)
{
	t_list_token  *curr;
	char *value;

	curr = data->next;
	value = getenv(curr->word);
	if (value != NULL)
		printf("%s\n",value);
	else
		printf("%s: No such file or directory.\n",curr->word);
}

void mini_unset(t_list_token *data)
{
	t_list_token *curr;

	curr = data;
	curr = curr->next;
	if (curr->word == NULL) {
		printf("unset: requires an argument\n");
	} else
	{
		if (unsetenv(curr->word) != 0) {
			perror("unset");
		}
	}
}

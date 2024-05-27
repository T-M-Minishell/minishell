/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlupu <tlupu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 16:21:50 by msacaliu          #+#    #+#             */
/*   Updated: 2024/05/21 18:52:05 by tlupu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_for_quotes(char *str)
{
	int i;

	i = 0;
	if(str[0] == '"')
		i++;
	while(str[i] != '\0')
	{
		if(str[strlen(str)] == '"')
			break ;
		printf("%c",str[i++]);
	}
}



// 1. echo with option -n

void	mini_echo(t_list_token *data)
{
	t_list_token *curr;

	curr = data;
	if (curr->next == NULL)
		printf("\n");
//	check_for_quotes(curr->word);
	else
	{
		curr = curr->next;
		int	print_new_line = 1;
		//check for -n function
		while(curr->word != NULL && curr->word[0] == '-' && curr->word[1] == 'n')
		{
			if(strcmp(curr->word, "-n-") == 0)
				break;
			print_new_line = 0;
			curr = curr->next;
		}
		// print each arg with space
		while(curr != NULL)
		{
			if (curr->word[0] == '$')
			{
				char *value = getenv(curr->word + 1);
				if (value != NULL)
					printf("%s ", value);
				else
					printf("%s ", "");
			}
			else
				printf("%s ",curr->word);
			curr = curr->next;
		}
		// print new_line if -n is not specified
		if(print_new_line)
			printf("\n");
	}
}

/// change directory
int mini_cd(t_list_token *data)
{
	t_list_token *curr;

	curr = data;
	if (data->next != NULL)
	{
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

void	min_env(t_list_token *data, char **envp)
{
	t_list_token  *curr;
	char *value;

	if (data->next == NULL)
	{
		for (char **env = envp; *env != 0; env++)
		{
			char *thisEnv = *env;
			printf("%s\n", thisEnv);
		}
	}
	else
	{
		curr = data->next;
		value = getenv(curr->word);
		if (value != NULL)
			printf("%s\n", value);
		else
			printf("%s: No such file or directory.\n",curr->word);
	}
}

void mini_unset(t_list_token *data)
{
	t_list_token *curr;

	curr = data;
	if (data->next == NULL)
		return ;
	curr = curr->next;
	if (curr->word == NULL) {
		printf("unset: requires an argument\n");
	}
	else
	{
		if (unsetenv(curr->word) != 0) {
			perror("unset");
		}
	}
}

void	mini_export(t_list_token *data)
{
	t_list_token *curr;

	curr = data;
	if (curr->next != NULL)
	{
		t_dictionary *dictionary = malloc(sizeof(t_dictionary));
		create_env_variable(dictionary, curr->next->word);
		free(dictionary);
	}
	else
	{
		printf("export: not enough arguments\n");
	}
}


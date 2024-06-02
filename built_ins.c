/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 16:21:50 by msacaliu          #+#    #+#             */
/*   Updated: 2024/05/30 14:42:22 by msacaliu         ###   ########.fr       */
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

void	mini_echo(t_list_token *data) // to do for env variables
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

void min_env(t_list_token *data, env_var *env_vars)
{
	(void)data;
	int i = 0;

	while (env_vars->arr[i])
	{
		printf("%s\n", env_vars->arr[i]);
		i++;
	}

}

env_var *mini_unset(t_list_token *data, env_var *env_vars)  // to do
{
	t_list_token *curr;

	curr = data;
	if (data->next == NULL)
		return NULL;
	curr = curr->next;
	if (curr->word == NULL) {
		printf("unset: requires an argument\n");
	}
	else
		env_vars= delete_env_var(env_vars, curr->word);
	return env_vars;
}

void	mini_export(t_list_token *data)
{
	t_list_token *curr;

	curr = data;
	if (curr->next != NULL)
	{
		t_dictionary *dictionary = malloc(sizeof(t_dictionary));
//		create_env_variable(dictionary, curr->next->word);
		free(dictionary);
	}
	else
	{
		printf("export: not enough arguments\n");
	}

}
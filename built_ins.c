/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 16:21:50 by msacaliu          #+#    #+#             */
/*   Updated: 2024/06/22 14:00:53 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//CVb3d2023


// 1. echo with option -n

void    mini_echo(t_list_token *data, env_var *vars) // to do for env variables
{
    t_list_token *curr;

    curr = data;
	// printf("test-----\n");
    if (curr->next == NULL)
        ft_putstr("\n");
    //  check_for_quotes(curr->word);
    else
    {
        curr = curr->next;
        int print_new_line = 1;
        // check for -n function
        while (curr->word != NULL && curr->word[0] == '-'
            && curr->word[1] == 'n')
        {
            if (strcmp(curr->word, "-n-") == 0)
                break ;
            print_new_line = 0;
            curr = curr->next;
        }
        // print each arg with space
        while (curr != NULL)
        {
			if (strcmp(curr->word, "|") == 0)
					break;
            if (curr->word[0] == '$')
            {
                char *value = get_value_from_var((curr->word +1),vars); // + 1 for jumping the $ sign
                if (value != NULL)
                    ft_putstr(value);
                else
                    ft_putstr(" ");
            }
            else
                ft_putstr(curr->word);
            curr = curr->next;
        }
        // print new_line if -n is not specified
        if (print_new_line)
        	ft_putstr("\n");
    }
}
//change directory
int	mini_cd(t_list_token *data)
{
	t_list_token	*curr;

	curr = data;
	if (data->next != NULL)
	{
		curr = curr->next;
		if (curr->word == NULL)
		{ // No argument, use HOME directory
			if (chdir(getenv("HOME")) != 0)
			{
				perror("cd");
				return (1);
			}
		}
		else
		{ // Change directory to the provided path
			if (chdir(curr->word) != 0)
			{
				perror("cd");
				return (1);
			}
		}
	}
	return (0);
}
// view in wich directory you are
void	mini_pwd(void)
{
	char *cwd = getcwd(NULL, 0); // Get current working directory
	if (cwd == NULL)
		perror("pwd");
	else
	{
		ft_putstr(cwd);
		ft_putstr("\n");
		free(cwd); // Free memory
	}
}


void	mini_exit(t_list_token *data)
{
	int exit_status = 0;
	t_list_token *curr;

	curr = data;
	if (curr->next != NULL && curr->next->word != NULL) {
		exit_status = atoi(curr->next->word);
	}

	ft_putstr("exit");
	exit(exit_status);
}

void	mini_env(env_var *env_vars)
{
	int	i;

	i = 0;
	while (env_vars->arr[i])
	{
		ft_putstr(env_vars->arr[i]);
		ft_putstr("\n");
		i++;
	}
}

env_var	*mini_unset(t_list_token *data, env_var *env_vars) // to do
{
	t_list_token *curr;

	curr = data;
	if (data->next == NULL)
		return (NULL);
	curr = curr->next;
	if (curr->word == NULL)
		printf("unset: requires an argument\n");
	if(strchr(curr->word,'=')!= NULL)
		return env_vars;
	while (curr != NULL)
	{
		env_vars = delete_env_var(env_vars, curr->word);
		curr = curr->next;
	}
	return (env_vars);
}

void	mini_export(t_list_token *data, env_var **env_vars)
{
	t_list_token	*curr;
	// char			*equal_pos;
	// int				key_len;
	// char			*key;
	// char			*value;
	int				i;
	// char			*copy;

	
	curr = data;
	if (curr->next == NULL)
	{
		printf("export: not enough arguments\n");
		return ;
	}
	curr = curr->next;
	if (curr->word == NULL)
	{
		printf("export: not enough arguments\n");
		return ;
	}
	char *equal_pos = strchr(curr->word, '=');
	if (equal_pos == NULL)
	{
		printf("export: argument should be in the format key=value\n");
		return ;
	}
	int key_len = equal_pos - curr->word;
	char *key = malloc(key_len + 1);
	strncpy(key, curr->word, key_len);
	key[key_len] = '\0';
	char *value = strdup(equal_pos + 1);
	i = 0;
	while ((*env_vars)->arr[i] != NULL)
	{
		char *copy = get_key_from_word((*env_vars)->arr[i]);
		if (strcmp(key, copy) == 0)
		{
			free(copy);
			// free((*env_vars)->arr[i]);
			(*env_vars)->arr[i] = strdup(curr->word);
			free(key);
			free(value);
			return ;
		}
		free(copy);
		i++;
	}
	*env_vars = add_env_var(*env_vars, curr->word);
	free(key);
	free(value);
}
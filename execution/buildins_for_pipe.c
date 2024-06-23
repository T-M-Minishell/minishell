/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins_for_pipe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 11:48:10 by msacaliu          #+#    #+#             */
/*   Updated: 2024/06/23 14:54:05 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	mini_cd_pipe(char **command)
{
	
	if (command[1] != NULL)
	{
		if (command[1] == NULL)
		{ // No argument, use HOME directory
			if (chdir(getenv("HOME")) != 0)
			{
				perror("cd");
				return (1);
			}
		}
		else
		{ // Change directory to the provided path
			if (chdir(command[1]) != 0)
			{
				perror("cd");
				return (1);
			}
		}
	}
	return (0);
}

void	mini_exit_pipe(char **command)
{
	int exit_status = 0;

	if (command[1] != NULL)
	{
		exit_status = atoi(command[1]);
	}

	ft_putstr("exit");
	ft_putstr("\n");
	exit(exit_status);
}

env_var *mini_unset_pipe(char **commands, env_var *env_vars) {
    int i = 0;
	int j = 0;
	char *key;
	int flag;

	flag = 0;
    if (commands[i] == NULL)
        return env_vars;

    i++;
    if (commands[i] == NULL) {
        ft_putstr("unset: requires an argument\n");
        return env_vars;
    }

    if (strchr(commands[i], '=') != NULL)
	{
		 return env_vars;
	}
	while(env_vars->arr[j])
	{
		key = get_key_from_word(env_vars->arr[j]);
		if (strcmp(commands[i],key) == 0)
			flag = 1;
		free(key);
		j++;
	}
	if (flag == 1)
	{
		while (commands[i] != NULL)
		{
       		env_vars = delete_env_var(env_vars, commands[i]);
        	i++;
   		}
	}
    return env_vars;
}

void mini_echo_pipe(char **commands, env_var *vars)
{
    int i = 1;
    int print_new_line = 1;

    if (commands[i] == NULL)
	{
        ft_putstr("\n");
        return;
    }
    // Check for the -n flag
    while (commands[i] != NULL && commands[i][0] == '-' && commands[i][1] == 'n') {
        if (strcmp(commands[i], "-n-") == 0) break;
        print_new_line = 0;
        i++;
    }
    // Print each argument with a space
    while (commands[i] != NULL)
	{
        if (commands[i][0] == '$')
		{
            char *value = get_value_from_var(commands[i] + 1, vars); // +1 to skip the $
            if (value != NULL)
                ft_putstr(value);
			else
                ft_putstr(" ");
        }
		else
            ft_putstr(commands[i]);
        if (commands[i + 1] != NULL)
            ft_putstr(" ");
        i++;
    }
    // Print new line if -n is not specified
    // if (print_new_line)
    //     ft_putstr("\n");
}

env_var *mini_export_pipe(char **commands, env_var *env_vars)
{
    int i = 0;
    int j;

    if (commands[i] == NULL) {
        printf("export: not enough arguments\n");
        return env_vars;
    }

    while (commands[i] != NULL) {
        char *equal_pos = strchr(commands[i], '=');
        if (equal_pos == NULL) {
            i++;
            continue;
        }

        int key_len = equal_pos - commands[i];
        char *key = malloc(key_len + 1);
        if (!key) {
            printf("Memory allocation error\n");
            return env_vars;
        }
        strncpy(key, commands[i], key_len);
        key[key_len] = '\0';
        char *value = strdup(equal_pos + 1);
        if (!value) {
            printf("Memory allocation error\n");
            free(key);
            return env_vars;
        }

        j = 0;
        while (env_vars->arr[j] != NULL) {
            char *copy = get_key_from_word(env_vars->arr[j]);
            if (!copy) {
                printf("Memory allocation error\n");
                free(key);
                free(value);
                return env_vars;
            }
            if (strcmp(key, copy) == 0) {
                free(copy);
                free(env_vars->arr[j]);
                env_vars->arr[j] = strdup(commands[i]);
                if (!env_vars->arr[j]) {
                    printf("Memory allocation error\n");
                    free(key);
                    free(value);
                    return env_vars;
                }
                free(key);
                free(value);
                break;
            }
            free(copy);
            j++;
        }

        if (env_vars->arr[j] == NULL) {
            env_vars = add_env_var(env_vars, commands[i]);
        }

        free(key);
        free(value);
        i++;
    }

    return env_vars;
}
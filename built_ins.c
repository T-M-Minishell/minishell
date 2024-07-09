/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 16:21:50 by msacaliu          #+#    #+#             */
/*   Updated: 2024/07/02 15:48:37 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//CVb3d2023
//
//void update_env_pwd(env_var *vars)
//{
//	char *cwd;
//	int i;
//	char *key;
//	char *new_path;
//
//	i = 0;
//	cwd = getcwd(NULL, 0);
//	if (cwd == NULL)
//	{
//		perror("pwd");
//		return ;
//	}
//	new_pwd = malloc(strlen("PWD=") + strlen(cwd) + 1);
//	if (new_pwd == NULL) {
//		perror("malloc");
//		free(cwd);
//		return;
//	}
//	(void)new_path;
//	while (vars->arr[i] != NULL)
//	{
//		key = get_key_from_word(vars->arr[i]);
//		if(strcmp("PWD", key) == 0)
//			add_env_var(vars, )
//		i++;
//	}
//	free(cwd);
//}


void mini_echo(char **commands, env_var *vars)
{
    int i = 1; // Start from the first command after "echo"
    int print_newline = 1; // Default is to print a newline at the end
    char *value;

    if (commands[i] == NULL) {
        ft_putstr("\n");
        return;
    }
    // Check for -n flag
    while (commands[i] != NULL && commands[i][0] == '-' && commands[i][1] != '\0') {
        int j = 1;
        while (commands[i][j] == 'n') {
            j++;
        }
        if (commands[i][j] == '\0') {
            print_newline = 0; // Don't print newline
            i++;
        } else {
            break; // Stop if we encounter a non-`n` character
        }
    }

    // Print each argument
    while (commands[i] != NULL) {
        if (commands[i][0] == '$') {
            if (strcmp(commands[i], "$?") == 0) {
                ft_putstr(ft_itoa(vars->exit_status));
                ft_putstr(" ");
                vars->exit_status = 0;
            } else {
                value = get_value_from_var(commands[i] + 1, vars); // +1 to skip the $
                if (value != NULL) {
                    ft_putstr(value);
                    ft_putstr(" ");
                }
            }
        } else {
            ft_putstr(commands[i]);
            ft_putstr(" ");
        }
        i++;
    }
    if (print_newline)
        ft_putstr("\n");
    vars->exit_status = 0;
}

int mini_cd(char **commands, env_var *vars)
{

	(void)vars;
    if (commands[1] == NULL)
    { // No argument, use HOME directory
        if (chdir(getenv("HOME")) != 0)
        {
            perror("cd");
            return 1;
        }
    }
    else
    { // Change directory to the provided path
        if (chdir(commands[1]) != 0)
        {
            perror("cd");
            return 1;
        }
//		update_env_pwd(vars);
    }
    return 0;
}


void mini_pwd(void)
{
    char *cwd = getcwd(NULL, 0); // Get current working directory
    if (cwd == NULL)
    {
        perror("pwd");
    }
    else
    {
        ft_putstr(cwd);
        ft_putstr("\n");
        free(cwd); // Free memory
    }
}

void mini_exit(char **commands, int last_exit_status)
{
    int exit_status = last_exit_status;

    if (commands[1] != NULL)
    {
        if (commands[2] != NULL)
        {
            ft_putstr("exit\nminishell: exit: too many arguments\n");
            return;
        }
        exit_status = atoi(commands[1]);
    }
    ft_putstr("exit\n");
    exit(exit_status % 256);
}


void mini_env(env_var *env_vars)
{
    int i = 0;

    while (env_vars->arr[i])
    {
        if (strchr(env_vars->arr[i], '=') != NULL)
        {
            ft_putstr(env_vars->arr[i]);
            ft_putstr("\n");
        }
        i++;
    }
}
env_var *mini_unset(char **commands, env_var *env_vars)
{
    int i = 1;
    int flag;
    char *key;

    if (commands[1] == NULL)
    {
        printf("unset: requires an argument\n");
        env_vars->exit_status = 1;
        return env_vars;
    }

    while (commands[i] != NULL)
    {
        if (strchr(commands[i], '=') != NULL)
        {
            i++;
            continue;
        }

        flag = 0;
        int j = 0;
        while (env_vars->arr[j] != NULL)
        {
            key = get_key_from_word(env_vars->arr[j]);
            if (strcmp(commands[i], key) == 0)
            {
                flag = 1;
                free(key);
                break;
            }
            free(key);
            j++;
        }

        if (flag == 1)
        {
            env_vars = delete_env_var(env_vars, commands[i]);
        }

        i++;
    }

    env_vars->exit_status = 0;
    return env_vars;
}


env_var *mini_export(char **commands, env_var **env_vars)
{
    int i = 0;
    char *equal_pos, *key, *value;

     if (commands[1] == NULL) {
        while ((*env_vars)->arr[i] != NULL) {
            char *key_from_word = get_key_from_word((*env_vars)->arr[i]);
            if (strchr((*env_vars)->arr[i], '=') == NULL)
                printf("declare -x %s\n", key_from_word);
            else
                printf("declare -x %s=\"%s\"\n", key_from_word, strchr((*env_vars)->arr[i], '=') + 1);
            free(key_from_word); // Free the memory allocated by get_key_from_word
            i++;
        }
        (*env_vars)->exit_status = 0;
        return (*env_vars);
    }

    i = 1;
    while (commands[i] != NULL)
    {
        if (!check_if_alphanumeric(commands[i]))
        {
            printf("minishell: export: %s: not a valid identifier\n", commands[i]);
            (*env_vars)->exit_status = 1;
            return (*env_vars);
        }

        equal_pos = strchr(commands[i], '=');
        if (equal_pos == NULL) // No equal sign found
        {
            key = strdup(commands[i]);
            value = strdup("");
        }
        else
        {
            int key_len = equal_pos - commands[i];
            key = malloc(key_len + 1);
            strncpy(key, commands[i], key_len);
            key[key_len] = '\0';
            value = strdup(equal_pos + 1);
        }

        int j = 0;
        while ((*env_vars)->arr[j] != NULL)
        {
            char *copy = get_key_from_word((*env_vars)->arr[j]);
            if (strcmp(key, copy) == 0)
            {
                free(copy);
                free((*env_vars)->arr[j]);
                (*env_vars)->arr[j] = strdup(commands[i]);
                free(key);
                free(value);
                return (*env_vars);
            }
            free(copy);
            j++;
        }
        *env_vars = add_env_var(*env_vars, commands[i]);
        free(key);
        free(value);
        i++;
    }
    (*env_vars)->exit_status = 0;
    return (*env_vars);
}


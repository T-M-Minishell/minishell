/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 16:21:50 by msacaliu          #+#    #+#             */
/*   Updated: 2024/07/01 12:57:39 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//CVb3d2023


// void    mini_echo(t_list_token *data, env_var *vars) // still need the flag
// {
//     t_list_token *curr;

//     curr = data;
// 	char *value;
// 	// int print_new_line;
//     if (curr->next == NULL)
//         ft_putstr("\n");
//     //  check_for_quotes(curr->word);
//     else
//     {
//         curr = curr->next;
//         // print_new_line = 1;
//         // check for -n function
//         while (curr->word != NULL && curr->word[0] == '-'
//             && curr->word[1] == 'n')
//         {
//             if (strcmp(curr->word, "-n-") == 0)
//                 break ;
//             // ft_putstr("\n");
//             curr = curr->next;
//         }
//         // print each arg with space
// 		while (curr != NULL)
// 		{
// 			if (strcmp(curr->word, "|") == 0)
// 				break;
// 			if (curr->word[0] == '$')
// 			{
// 				if(strcmp(curr->word, "$?") == 0)
// 				{
// 					// printf("%d ", vars->exit_status);
//                     ft_putstr(ft_itoa(vars->exit_status));
//                     ft_putstr(" ");
// 					printf("%d\n", vars->exit_status); 
// 					vars->exit_status = 0;
// 				}
//                 else
//                 {
//                     printf("%s ", curr->word);	
//                     value = get_value_from_var((curr->word +1),vars); // + 1 for jumping the $ sign
//                     if (value != NULL)
//                     {
//                         ft_putstr(value);
//                         ft_putstr(" ");
//                     }

//                 }
//             }
//             else
//             {
//                 ft_putstr(curr->word);
//                 ft_putstr(" ");
//             }
//             curr = curr->next;
//         }
//         printf("\n");
//         // printf("echo test");
// 		// if (print_new_line == 1)
//         //  	ft_putstr("\n");
//     }
// }


//change directory
// int	mini_cd(t_list_token *data)
// {
// 	t_list_token	*curr;

// 	curr = data;
// 	if (data->next != NULL)
// 	{
// 		curr = curr->next;
// 		if (curr->word == NULL)
// 		{ // No argument, use HOME directory
// 			if (chdir(getenv("HOME")) != 0)
// 			{
// 				perror("cd");
// 				return (1);
// 			}
// 		}
// 		else
// 		{ // Change directory to the provided path
// 			if (chdir(curr->word) != 0)
// 			{
// 				perror("cd");
// 				return (1);
// 			}
// 		}
// 	}
// 	return (0);
// }
// view in wich directory you are
// void	mini_pwd(void)
// {
// 	char *cwd = getcwd(NULL, 0); // Get current working directory
// 	if (cwd == NULL)
// 		perror("pwd");
// 	else
// 	{
// 		ft_putstr(cwd);
// 		ft_putstr("\n");
// 		free(cwd); // Free memory
// 	}
// }


// void mini_exit(t_list_token *data, int last_exit_status)
// {
//     int exit_status = last_exit_status;
//     t_list_token *curr = data->next; 

//     if (curr != NULL) {
//         if (curr->next != NULL)
// 		{
//             ft_putstr("exit\nminishell: exit: too many arguments\n");
//             return;
//         }
//         exit_status = atoi(curr->word);
       
//     }
//     ft_putstr("exit\n");
//     exit(exit_status % 256);
// }

// void	mini_env(env_var *env_vars)
// {
// 	int	i;

// 	i = 0;
// 	while (env_vars->arr[i])
// 	{
//         if(strchr(env_vars->arr[i], '=') == NULL)
//             i++;
//         else
//         {
//             ft_putstr(env_vars->arr[i]);
// 		    ft_putstr("\n");
// 		    i++;
//         }
		
// 	}
// }


// env_var	*mini_unset(t_list_token *data, env_var *env_vars) // to do
// {
// 	t_list_token *curr;
// 	int i;
// 	int flag;
// 	char *key;
	
// 	i = 0;
// 	flag =0;
// 	curr = data;
// 	if (data->next == NULL)
// 		return (NULL);
// 	curr = curr->next;
// 	if (curr->word == NULL)
// 	{
// 		printf("unset: requires an argument\n");
// 		env_vars->exit_status = 1;
// 		return (NULL);
// 	}
		
// 	if(strchr(curr->word,'=')!= NULL)
// 		return env_vars;
// 	while (env_vars->arr[i])
// 	{
// 		key = get_key_from_word(env_vars->arr[i]);
// 		if(strcmp(curr->word, key) == 0)
// 			flag = 1;
// 		free(key); // Free the memory allocated for key 
// 		i++;
// 	}
// 	if(flag == 1)
// 	{
// 		while (curr != NULL)
// 		{
// 		// if(curr->word)
// 		env_vars = delete_env_var(env_vars, curr->word);
// 		curr = curr->next;
// 		}
// 	}
// 		env_vars->exit_status = 0;
// 	return (env_vars);
// }



// void    mini_export(t_list_token *data, env_var **env_vars)
// {
//    t_list_token *curr;
//     int i;

//     curr = data;
//     if (curr->next == NULL)
//     {
//         i = 0;
//         while ((*env_vars)->arr[i] != NULL)
//         {
//             if(strchr((*env_vars)->arr[i], '=') == NULL)
//                 printf("declare -x %s\n", get_key_from_word((*env_vars)->arr[i++]));
//             else
//             {
//                 printf("declare -x %s=\"%s\"\n", get_key_from_word((*env_vars)->arr[i]),strchr((*env_vars)->arr[i], '=') + 1);
//                 i++;
//             }
            
//         }
//         (*env_vars)->exit_status = 0;  
//         return;
//     }
//     curr = curr->next;
//     char *equal_pos = strchr(curr->word, '=');
//     char *key, *value;
//     if (equal_pos == NULL) // No equal sign found
//     {
//         key = strdup(curr->word);
//         value = strdup("");
//     }
//     else
//     {
//         int key_len = equal_pos - curr->word;
//         key = malloc(key_len + 1);
//         strncpy(key, curr->word, key_len);
//         key[key_len] = '\0';
//         value = strdup(equal_pos + 1);
//     }
//     i = 0;
//     while ((*env_vars)->arr[i] != NULL)
//     {
//         char *copy = get_key_from_word((*env_vars)->arr[i]);
//         if (strcmp(key, copy) == 0)
//         {
//             free(copy);
//             free((*env_vars)->arr[i]);
//             (*env_vars)->arr[i] = strdup(curr->word);
//             free(key);
//             free(value);
//             return;
//         }
//         free(copy);
//         i++;
//     }
//     *env_vars = add_env_var(*env_vars, curr->word);
//     (*env_vars)->exit_status = 0;
//     free(key);
//     free(value);
// }



/// ----------------new way-----------------------



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
    while (commands[i] != NULL && strcmp(commands[i], "-n") == 0) {
        print_newline = 0; // Don't print newline
        i++;
    }

    // Print each argument
    for (; commands[i] != NULL; i++) {
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
    }

    if (print_newline) {
        ft_putstr("\n");
    }
	vars->exit_status = 0;

}

int mini_cd(char **commands)
{
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
    int i, flag;
    char *key;

    if (commands[1] == NULL)
    {
        printf("unset: requires an argument\n");
        env_vars->exit_status = 1;
        return env_vars;
    }

    for (i = 1; commands[i] != NULL; i++)
    {
        if (strchr(commands[i], '=') != NULL)
        {
            continue;
        }

        flag = 0;
        for (int j = 0; env_vars->arr[j]; j++)
        {
            key = get_key_from_word(env_vars->arr[j]);
            if (strcmp(commands[i], key) == 0)
            {
                flag = 1;
                free(key);
                break;
            }
            free(key);
        }

        if (flag == 1)
        {
            env_vars = delete_env_var(env_vars, commands[i]);
        }
    }

    env_vars->exit_status = 0;
    return env_vars;
}


env_var *mini_export(char **commands, env_var **env_vars)
{
    int i;
    char *equal_pos, *key, *value;
	
    if (commands[1] == NULL)
    {
        for (i = 0; (*env_vars)->arr[i] != NULL; i++)
        {
            if (strchr((*env_vars)->arr[i], '=') == NULL)
            {
                printf("declare -x %s\n", get_key_from_word((*env_vars)->arr[i]));
            }
            else
            {
                printf("declare -x %s=\"%s\"\n", get_key_from_word((*env_vars)->arr[i]), strchr((*env_vars)->arr[i], '=') + 1);
            }
        }
        (*env_vars)->exit_status = 0;
        return (*env_vars);
    }

    for (i = 1; commands[i] != NULL; i++)
    {
		if(!check_if_alphanumeric(commands[1]))
		{
			printf("minishell : export : %s : not a valid identifier\n", commands[1]);
			(*env_vars)->exit_status = 1;
			return(*env_vars);
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
    }
    (*env_vars)->exit_status = 0;
	return (*env_vars);
}


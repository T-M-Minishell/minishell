/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 16:21:50 by msacaliu          #+#    #+#             */
/*   Updated: 2024/07/09 15:17:05 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mini_echo(char **commands, env_var *vars)
{
	int		i;
	int		print_newline;
	char	*value;
	int		j;

	i = 1;
	print_newline = 1;
	if (commands[i] == NULL)
	{
		ft_putstr("\n");
		return ;
	}
    // Check for -n flag
	while (commands[i] != NULL && commands[i][0] == '-'
			&& commands[i][1] != '\0')
	{
		j = 1;
		while (commands[i][j] == 'n')
			j++;
		if (commands[i][j] == '\0')
		{
			print_newline = 0;
			i++;
		}
		else
			break ;
	}
    // Print each argument
	while (commands[i] != NULL)
	{
		if (commands[i][0] == '$')
		{
			if (strcmp(commands[i], "$?") == 0)
			{
				ft_putstr(ft_itoa(vars->exit_status));
				ft_putstr(" ");
				vars->exit_status = 0;
			}
			else
			{
				value = get_value_from_var(commands[i] + 1, vars);
				if (value != NULL)
				{
					ft_putstr(value);
					ft_putstr(" ");
				}
			}
		}
		else
		{
			ft_putstr(commands[i]);
			ft_putstr(" ");
		}
		i++;
	}
	if (print_newline)
		ft_putstr("\n");
	vars->exit_status = 0;
}

int	mini_cd(char **commands, env_var *vars)
{
	(void)vars;
	if (commands[1] == NULL)
	{
		if (chdir(getenv("HOME")) != 0)
		{
			perror("cd");
			return (1);
		}
	}
	else
	{
		if (chdir(commands[1]) != 0)
		{
			perror("cd");
			return (1);
		}
//		update_env_pwd(vars);
	}
	return (0);
}

//getcwd --> get current directory
void	mini_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		perror("pwd");
	}
	else
	{
		ft_putstr(cwd);
		ft_putstr("\n");
		free(cwd);
	}
}

void	mini_exit(char **commands, int last_exit_status)
{
	int	exit_status;

	exit_status = last_exit_status;
	if (commands[1] != NULL)
	{
		if (commands[2] != NULL)
		{
			ft_putstr("exit\nminishell: exit: too many arguments\n");
			return ;
		}
		exit_status = atoi(commands[1]);
	}
	ft_putstr("exit\n");
	exit(exit_status % 256);
}

void	mini_env(env_var *env_vars)
{
	int	i;

	i = 0;
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

env_var	*mini_unset(char **commands, env_var *env_vars)
{
	int		i;
	int		flag;
	char	*key;
	int		j;

	i = 0;
	if (commands[1] == NULL)
	{
		printf("unset: requires an argument\n");
		env_vars->exit_status = 1;
		return (env_vars);
	}
	while (commands[i] != NULL)
	{
		if (strchr(commands[i], '=') != NULL)
		{
			i++;
			continue ;
		}
		flag = 0;
		j = -1;
		while (env_vars->arr[++j] != NULL)
		{
			key = get_key_from_word(env_vars->arr[j]);
			if (strcmp(commands[i], key) == 0)
			{
				flag = 1;
				free(key);
				break ;
			}
			free(key);
		}
		if (flag == 1)
			env_vars = delete_env_var(env_vars, commands[i]);
		i++;
	}
	env_vars->exit_status = 0;
	return (env_vars);
}

// void	print_env_vars(env_var *env_vars)
// {
// 	int		i;
// 	char	*key_from_word;

// 	i = 0;
// 	key_from_word = NULL;
// 	while (env_vars->arr[i] != NULL)
// 	{
// 		key_from_word = get_key_from_word(env_vars->arr[i]);
// 		if (strchr(env_vars->arr[i], '=') == NULL)
// 			printf("declare -x %s\n", key_from_word);
// 		else
// 			printf("declare -x %s=\"%s\"\n", key_from_word,
// 				strchr(env_vars->arr[i], '=') + 1);
// 		free(key_from_word);
// 		i++;
// 	}
// 	env_vars->exit_status = 0;
// }

// env_var	*handle_single_export(char *command, env_var *env_vars)
// {
// 	char	*equal_pos;
// 	char	*key;
// 	char	*value;
// 	int		key_len;
// 	char	*copy;

// 	copy = NULL;
// 	key = NULL;
// 	value = NULL;
// 	key_len = 0;
// 	equal_pos = strchr(command, '=');
// 	if (!check_if_alphanumeric(command))
// 	{
// 		printf("minishell: export: %s: not a valid identifier\n", command);
// 		env_vars->exit_status = 1;
// 		return (env_vars);
// 	}
// 	if (equal_pos == NULL)
// 	{
// 		key = strdup(command);
// 		value = strdup("");
// 	}
// 	else
// 	{
// 		key_len = equal_pos - command;
// 		key = malloc(key_len + 1);
// 		strncpy(key, command, key_len);
// 		key[key_len] = '\0';
// 		value = strdup(equal_pos + 1);
// 	}
// 	key_len = 0;
// 	while (env_vars->arr[key_len] != NULL)
// 	{
// 		copy = get_key_from_word(env_vars->arr[key_len]);
// 		if (strcmp(key, copy) == 0)
// 		{
// 			free(copy);
// 			free(env_vars->arr[key_len]);
// 			env_vars->arr[key_len] = strdup(command);
// 			free(key);
// 			free(value);
// 			return (env_vars);
// 		}
// 		free(copy);
// 		key_len++;
// 	}
// 	env_vars = add_env_var(env_vars, command);
// 	free(key);
// 	free(value);
// 	return (env_vars);
// }

// env_var	*mini_export(char **commands, env_var **env_vars)
// {
// 	int	i;

// 	i = 1;
// 	if (commands[1] == NULL)
// 	{
// 		print_env_vars(*env_vars);
// 		return (*env_vars);
// 	}
// 	while (commands[i] != NULL)
// 	{
// 		*env_vars = handle_single_export(commands[i], *env_vars);
// 		if ((*env_vars)->exit_status == 1)
// 			return (*env_vars);
// 		i++;
// 	}
// 	(*env_vars)->exit_status = 0;
// 	return (*env_vars);
// }

env_var	*mini_export(char **commands, env_var **env_vars)
{
	int		i;
	char	*equal_pos;
	char	*key;
	char	*value;
	char	*key_from_word;
	int		key_len;
	int		j;
	char 	*copy;

	i = 0;
	if (commands[1] == NULL)
	{
		while ((*env_vars)->arr[i] != NULL)
		{
			key_from_word = get_key_from_word((*env_vars)->arr[i]);
			if (strchr((*env_vars)->arr[i], '=') == NULL)
				printf("declare -x %s\n", key_from_word);
			else
				printf("declare -x %s=\"%s\"\n", key_from_word,
					strchr((*env_vars)->arr[i], '=') + 1);
			free(key_from_word);
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
			printf("minishell: export: %s: not a valid identifier\n",
				commands[i]);
			(*env_vars)->exit_status = 1;
			return (*env_vars);
		}
		equal_pos = strchr(commands[i], '=');
		if (equal_pos == NULL)
		{
			key = strdup(commands[i]);
			value = strdup("");
		}
		else
		{
			key_len = equal_pos - commands[i];
			key = malloc(key_len + 1);
			strncpy(key, commands[i], key_len);
			key[key_len] = '\0';
			value = strdup(equal_pos + 1);
		}
		j = 0;
		while ((*env_vars)->arr[j] != NULL)
		{
            copy = get_key_from_word((*env_vars)->arr[j]);
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

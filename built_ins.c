/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 16:21:50 by msacaliu          #+#    #+#             */
/*   Updated: 2024/05/19 17:13:07 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 1. echo with option -n

void	mini_echo(char **args)
{
	int	i;
	int	print_new_line = 1; 
	i = 1; //start from 1 to skip the command "echo"
	
	//check for -n function
	if(args[i] != NULL && strcmp(args[i], "-n") == 0)
	{
		i++;
		print_new_line = 0; //supress new_line when -n 
	}
	
	// print each arg with space
	while(args[i] != NULL)  /// problem here whn i put quotes
	{
   		if (*args[i] != '\'' && *args[i] != '\"')
        	printf("%s ", args[i]);
    	i++;
	}
	 // print new_line if -n is not specified
	 if(print_new_line)
	 	printf("\n");
}

int mini_cd(char **args)
{
    if (args[1] == NULL)
	{  // No argument, use HOME directory
        if (chdir(getenv("HOME")) != 0)
		{
            perror("cd");
            return 1;
        }
    }
	else
	{  // Change directory to the provided path
        if (chdir(args[1]) != 0)
		{
            perror("cd");
            return 1;
        }
    }
    return 0;
}

void mini_pwd(void)
{
    char *cwd = getcwd(NULL, 0);  // Get current working directory
    if (cwd == NULL)
        perror("pwd");
    else
	{
        printf("%s\n", cwd);
        free(cwd);  // Free memory allocated by getcwd
    }
}

void mini_exit(void)
{
	printf("exit\n");
    exit(0); 
}
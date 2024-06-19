/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:34:38 by msacaliu          #+#    #+#             */
/*   Updated: 2024/06/19 19:08:49 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

char *find_path(t_list_commands *cmd)
{
    t_list_commands *command = cmd;   
    // (void)command;
    char *path;


    
    // printf("arr[0]--%s\n",command->arr[0]);
    if(strcmp(command->arr[0], "echo") == 0)
        path ="/bin/echo";
    else if(strcmp(command->arr[0], "pwd") == 0)
        path ="/bin/pwd";
    else if(strcmp(command->arr[0], "clear") == 0)
        path ="/bin/clear";
    else if(strcmp(command->arr[0], "rm") == 0)
        path = "/bin/rm";
    else if(strcmp(command->arr[0], "mv") == 0)
        path = "/bin/mv";
    else if(strcmp(command->arr[0], "mkdir") == 0)
        path = "/bin/mkdir";
    else if(strcmp(command->arr[0], "ls") == 0)
        path = "/bin/ls";
    else if(strcmp(command->arr[0], "wc") == 0)
        path = "/usr/bin/wc";
    
    else
        path = NULL;
    return (path);
}




// void execute_command(char **argv, char *envp[])
// {   
    
//     char *path = find_path(
  
//     if (execve("/bin/echo", argv, envp) == -1) {
//         perror("execve");
//         exit(EXIT_FAILURE); // If execve fails, exit child process with an error code
//     }
// }

int count_nb_of_pipes(t_list_token *data)
{
    int nb;

    nb = 0;
    t_list_token *curr = data;

    while(curr != NULL)
    {
        if(strcmp(curr->word, "|") == 0)
            nb++;
        curr = curr->next;
    }
    return nb;
}

char    **convert_tokens_to_argv(t_list_token *data)
{
    int count = 0;
    t_list_token* current = data;

    // Step 1: Count the tokens
    while (current != NULL && strcmp(current->word,"|" )!= 0)
    {
        count++;
        current = current->next;
    }
    // Step 2: Allocate memory for argv
    char  **argv = malloc((count + 1) * sizeof(char*)); // +1 for NULL terminator
    if (argv == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    // Step 3: Fill argv
    current = data;
    for (int i = 0; i < count; i++)
    {
        if(strcmp(current->word,"|" )== 0)
            break;
        argv[i] = strdup(current->word); // Duplicate the string to avoid potential issues
        if (argv[i] == NULL) {
        perror("strdup");
        exit(EXIT_FAILURE);
        }
        current = current->next;
    }
    // Step 4: Terminate argv with NULL
    argv[count] = NULL;
    return argv;
}


// // / ----------copilot-------

// void implementing_pipe(t_list_commands *cmd, env_var *env_vars) {
//     int num_cmds = 0;
//     for (t_list_commands *current = cmd; current != NULL; current = current->next) {
//         num_cmds++;
//     }

//     // Allocate pipes
//     int (*pipes)[2] = malloc(sizeof(int[2]) * (num_cmds - 1));
//     for (int i = 0; i < num_cmds - 1; i++) {
//         if (pipe(pipes[i]) == -1) {
//             perror("pipe");
//             exit(EXIT_FAILURE);
//         }
//     }

//     int i = 0;
//     for (t_list_commands *current = cmd; current != NULL; current = current->next, i++) {
//         int pid = fork();
//         if (pid < 0) {
//             perror("fork");
//             exit(EXIT_FAILURE);
//         } else if (pid == 0) { // Child process
//             if (i > 0) { // Not the first command
//                 dup2(pipes[i - 1][0], STDIN_FILENO);
//             }
//             if (i < num_cmds - 1) { // Not the last command
//                 dup2(pipes[i][1], STDOUT_FILENO);
//             }
//             // Close all pipes in the child process
//             for (int j = 0; j < num_cmds - 1; j++) {
//                 close(pipes[j][0]);
//                 close(pipes[j][1]);
//             }
//             char *path = find_path(current);
//             execve(path, current->arr, env_vars->arr);
//             perror("execve");
//             exit(EXIT_FAILURE);
//         }
//     }

//     // Close all pipes in the parent process
//     for (int j = 0; j < num_cmds - 1; j++) {
//         close(pipes[j][0]);
//         close(pipes[j][1]);
//     }

//     // Wait for all child processes to finish
//     for (int j = 0; j < num_cmds; j++) {
//         wait(NULL);
//     }

//     free(pipes); // Free the dynamically allocated memory for pipes
// }

// ---------- mine---------

void    implementing_pipe(t_list_commands *cmd, env_var *env_vars)
{
    t_list_commands *cmommand;
    int fd[2];

    cmommand = cmd;
    if (pipe(fd) == -1)
    {
        printf("pipe err\n");
        exit(1);
    }
    
    int pid1 = fork();
    if(pid1 < 0)
    {
        printf("pid err\n");
        exit(1);
    }
    if(pid1 == 0)
    {
        char *path = find_path(cmommand);
        dup2(fd[1],STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
        execve(path, cmommand->arr, env_vars->arr);
    }
    cmommand = cmommand->next;
    int pid2 = fork();
    if (pid2 == 0) { // child process 2
        char *path = find_path(cmommand);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		execve(path, cmommand->arr, env_vars->arr);
	}
    close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL,0);
	waitpid(pid2, NULL,0);
    
    
}


void handle_pipe(t_list_token *data, env_var **env_vars)
{
    // (void)env_vars;
    
    t_list_commands *cmd_head = NULL, *cmd_tail = NULL;
    t_list_token *current = data;

    while (current != NULL)
    {
        // Allocate memory for a new command node
        t_list_commands *new_cmd = malloc(sizeof(t_list_commands));
        if (new_cmd == NULL) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }

        // Use convert_tokens_to_argv to fill new_cmd->arr
        new_cmd->arr = convert_tokens_to_argv(current);
        new_cmd->next = NULL;

        // Append the new command node to the list
        if (cmd_head == NULL)
        {
        cmd_head = new_cmd;
        cmd_tail = new_cmd;
        }
        else
        {
        cmd_tail->next = new_cmd;
        cmd_tail = new_cmd;
        }
        // Move current to the next token after the pipe
        while (current != NULL && strcmp(current->word, "|") != 0)
            current = current->next;
        // Skip the pipe token
        if (current != NULL && strcmp(current->word, "|") == 0)
            current = current->next;
    }

    // Debug print to verify the commands in each node
   implementing_pipe(cmd_head, *env_vars);
}




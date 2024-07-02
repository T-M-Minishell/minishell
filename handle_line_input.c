/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_line_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlupu <tlupu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:00:08 by msacaliu          #+#    #+#             */
/*   Updated: 2024/06/26 17:34:36 by tlupu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void handle_redirects(t_list_token *data) {
//     t_list_token *curr = data;
//     t_word_info_redirect *cmd_nodes;
//     int i, fd, j, length;
//     char **output_file_arr;

//     curr = data;
//     length = 0;
//     cmd_nodes = node_creator(curr);
//     if (!cmd_nodes) {
//         return;
//     }
//     while (curr != NULL) {
//         length++;
//         curr = curr->next;
//     }
//     output_file_arr = (char **)malloc(sizeof(char *) * (length + 1));
//     if (!output_file_arr) {
//         return;
//     }
//     i = 0;
//     j = 0;
//     while (cmd_nodes->arr[i] != NULL) {
//         output_file_arr[j] = cmd_nodes->arr[i];
//         i++;
//         j++;
//     }
//     output_file_arr[j] = NULL;

//     for (i = 0; cmd_nodes->arr[i] != NULL; i++) {
//         if (strcmp(cmd_nodes->arr[i], ">") == 0 && cmd_nodes->arr[i + 1] != NULL) {
//             fd = open(cmd_nodes->arr[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
//             if (fd < 0) {
//                 printf("Error opening file\n");
//                 continue; // Continue to the next command if file opening fails
//             }
//             if (dup2(fd, STDOUT_FILENO) == -1) {
//                 printf("Error duplicating file descriptor\n");
//                 close(fd);
//                 continue; // Continue to the next command if dup2 fails
//             }
//             close(fd); // Close the file descriptor as it's no longer needed
//             i++; // Skip the filename that was just redirected to
//         }
//     }

//     // Optionally, print the command before redirection
//     for (j = 0; output_file_arr[j] != NULL && strcmp(output_file_arr[j], ">") != 0; j++) {
//         printf("%s ", output_file_arr[j]);
//     }
//     printf("\n");

//     free(output_file_arr); // Free allocated memory
// }

// #include <fcntl.h>
// #include <stdio.h>
// #include <string.h>
// #include <unistd.h>
// #include <stdlib.h>

// // Assuming t_list_token and t_word_info_redirect are defined elsewhere
// // along with the REDIRECT enum or define

// void handle_redirects(t_list_token *data) {
//     t_list_token *curr = data;
//     t_word_info_redirect *cmd_nodes;
//     int fd = -1;
//     int stdout_copy = dup(STDOUT_FILENO);
//     int stderr_copy = dup(STDERR_FILENO);

//     cmd_nodes = node_creator(curr); // Assuming this function prepares the command nodes correctly
//     if (!cmd_nodes) {
//         return;
//     }

//     for (int i = 0; cmd_nodes->arr[i] != NULL; i++) {
//         if (strcmp(cmd_nodes->arr[i], ">") == 0 && cmd_nodes->arr[i + 1] != NULL) {
//             fd = open(cmd_nodes->arr[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
//             if (fd >= 0) dup2(fd, STDOUT_FILENO);
//         } else if (strcmp(cmd_nodes->arr[i], ">>") == 0 && cmd_nodes->arr[i + 1] != NULL) {
//             fd = open(cmd_nodes->arr[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
//             if (fd >= 0) dup2(fd, STDOUT_FILENO);
//         } else if (strcmp(cmd_nodes->arr[i], "2>") == 0 && cmd_nodes->arr[i + 1] != NULL) {
//             fd = open(cmd_nodes->arr[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
//             if (fd >= 0) dup2(fd, STDERR_FILENO);
//         } else if (strcmp(cmd_nodes->arr[i], "2>>") == 0 && cmd_nodes->arr[i + 1] != NULL) {
//             fd = open(cmd_nodes->arr[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
//             if (fd >= 0) dup2(fd, STDERR_FILENO);
//         }
//         if (fd >= 0) {
//             close(fd);
//             fd = -1;
//         }
//     }

//     // Execute the command here (not shown)

//     // Restore stdout and stderr
//     dup2(stdout_copy, STDOUT_FILENO);
//     dup2(stderr_copy, STDERR_FILENO);
//     close(stdout_copy);
//     close(stderr_copy);
// }
void free_cmd_node(t_word_info_redirect *head)
{
	t_word_info_redirect *temp;

	if (head != NULL)
	{
		// Free each string in the arr
		int i = 0;
		if (head->arr[i] != NULL)
		{

			while (head->arr[i] != NULL)
			{
				free(head->arr[i]);
				i++;
			}
			// Free the arr itself
			free(head->arr);
			// Move to the next node and free the current node
			temp = head;
			free(temp);
		}
	}
}

t_word_info_redirect *node_creator(t_list_token *data)
{
	t_list_token *curr;
	t_word_info_redirect *commands;
	int length;
	int i;

	curr = data;
	commands = (t_word_info_redirect *)malloc(sizeof(t_word_info_redirect));
	length = 0;
	commands->arr = NULL;
	while (curr != NULL)
	{
		if (curr->type == REDIRECT)
		{
			length++;
			break;
		}
		length++;
		curr = curr->next;
	}
	curr = data;
	commands->arr = (char **)malloc(sizeof(char *) * (length + 1));
	if (commands->arr == NULL)
	{
		printf("mem allocation failed in new redirect node[1]\n");
		return (NULL);
	}
	i = 0;
	while (curr != NULL)
	{
		if (curr->type == REDIRECT)
		{
			commands->token = REDIRECT;
			continue;
		}
		commands->token = WORD;
		commands->arr[i++] = strdup(curr->word);
		curr = curr->next;
	}
	commands->arr[i] = NULL;
	return (commands);
}

// void handle_redirects(t_list_token *data)
// {
// 	t_list_token *curr;
// 	t_word_info_redirect *cmd_nodes;
// 	int i;
// 	int fd;
// 	char **output_file_arr;
// 	int j;
// 	int length;
// 	int fd_std_output;

// 	output_file_arr = NULL;
// 	fd = -1;
// 	fd_std_output = -1;
// 	curr = data;
// 	length = 0;
// 	cmd_nodes = node_creator(curr);
// 	if (!cmd_nodes)
// 		return;
// 	while (curr != NULL)
// 	{
// 		if (curr->type == REDIRECT)
// 		{
// 			length++;
// 			break;
// 		}
// 		length++;
// 		curr = curr->next;
// 	}
// 	output_file_arr = (char **)malloc(sizeof(char *) * (length + 1));
// 	if (!output_file_arr)
// 	{
// 		return;
// 	}
// 	j = 0;
// 	i = 0;
// 	while (cmd_nodes->arr[i] != NULL)
// 	{
// 		output_file_arr[j] = strdup(cmd_nodes->arr[i]);
// 		if (output_file_arr[j] == NULL)
// 		{
// 			printf("mem allocation failed in new redirect node[1]\n");
// 			return;
// 		}
// 		if (strcmp(cmd_nodes->arr[i], ">") == 0)
// 		{
// 			break;
// 		}
// 		i++;
// 		j++;
// 	}
// 	output_file_arr[j] = NULL;
// 	i = 0;
// 	while (cmd_nodes->arr[i] != NULL)
// 	{
// 		if (strcmp(cmd_nodes->arr[i], ">") == 0 && cmd_nodes->arr[i + 1] != NULL)
// 		{
// 			fd_std_output = dup(STDOUT_FILENO);
// 			if (fd_std_output == -1)
// 			{
// 				printf("Error duplicating file descriptor[fdout]\n");
// 				return;
// 			}
// 			fd = open(cmd_nodes->arr[i + 1], O_WRONLY | O_CREAT | O_TRUNC,
// 					  0644);
// 			if (fd < 0)
// 			{
// 				printf("Error oppening file\n");
// 				return;
// 			}
// 			dup2(fd, STDOUT_FILENO);
// 			if (fd < 0)
// 			{
// 				printf("Error duplicating file descriptor\n");
// 				close(fd);
// 				return;
// 			}
// 			close(fd);
// 			j = 0;
// 			while (output_file_arr[j] != NULL && strcmp(output_file_arr[j], ">") != 0)
// 			{
// 				printf("%s ", output_file_arr[j]);
// 				j++;
// 			}
// 			printf("\n");
// 			break;
// 		}
// 		i++;
// 	}
// 	dup2(fd_std_output, STDOUT_FILENO);
// 	close(fd_std_output);
// 	i = 0;
// 	while (output_file_arr[i] != NULL)
// 	{
// 		free(output_file_arr[i]);
// 		i++;
// 	}
// 	free(output_file_arr);
// 	free_cmd_node(cmd_nodes);
// 	// print_node(cmd_node);
// 	return;
// }

void handle_redirects(t_list_token *data)
{
	t_list_token *curr;
	t_word_info_redirect *cmd_nodes;
	int i;
	int fd;
	// char **output_file_arr;
	// int j;
	// int length;
	int fd_std_output;

	curr = data;
	// aici -> functie care sa verifce daca este posibil sa existe token cu redirect <- aici
	while (curr != NULL)
	{
		cmd_nodes = node_creator(curr);
		if (!cmd_nodes)
			return;
		cmd_nodes = cmd_nodes->next;
		curr = curr->next;
	}
	curr = data;
	i = 0;
	fd = -1;
	while (curr != NULL)
	{
		if (curr->type == REDIRECT && curr->next != NULL)
		{
			fd_std_output = dup(STDOUT_FILENO);
			if (fd_std_output < 0)
			{
				printf("Prob[n]n\n");
				return;
			}
			fd = open(curr->next->word, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd < 0)
			{
				printf("Prob[n]n\n");
				return;
			}
			dup2(fd, STDOUT_FILENO);
			if (fd < 0)
			{
				printf("Prob[n]n\n");
				return;
			}
			close(fd);
			while (cmd_nodes != NULL)
			{
				if (cmd_nodes->token == REDIRECT)
				{
					continue;
				}
				else
				{
					printf("%s ", cmd_nodes->arr[i++]);
				}
				cmd_nodes = cmd_nodes->next;
			}
		}
			break;
	}
	dup2(fd_std_output, STDOUT_FILENO);
	close(fd_std_output);
	return;
}

void handle_tokens_in_prompt(t_list_token *data, char **envp,
							 env_var **env_vars)
{
	t_list_token *curr;

	curr = data;
	(void)envp;
	// printf("%s\n", curr->word);
	if (curr->word != NULL)
	{
		if (strchr(curr->word, '='))
			*env_vars = add_env_var(*env_vars, curr->word);
		if (strcmp(curr->word, "echo") == 0)
			mini_echo(curr, *env_vars);
		if (strcmp(curr->word, "cd") == 0)
			mini_cd(curr);
		if (strcmp(curr->word, "pwd") == 0)
			mini_pwd();
		if (strcmp(curr->word, "exit") == 0)
			mini_exit(curr);
		if (strcmp(curr->word, "export") == 0)
			mini_export(curr, env_vars);
		if (strcmp(curr->word, "unset") == 0)
			*env_vars = mini_unset(curr, *env_vars);
		if (strcmp(curr->word, "env") == 0)
			min_env(curr, *env_vars);
		else
		{
			//			printf("%s\n",curr->word);
			handle_not_existent_builtins(curr, env_vars);
		}
	}
}

void handle_line(t_input *input, t_list_token *data, char **envp,
				 env_var **env_vars)
{
	t_token_type token;
	char **arr;
	int i;
	char *line_start;

	line_start = input->line;
	if (input->line == NULL)
	{
		printf("exit\n");
		exit(1);
	}
	if (input->line[0] == '\0')
		return;
	while (*line_start == ' ')
		line_start++;
	if (*line_start == '\0')
		return;
	arr = custom_split((char *)(input->line + (line_start - input->line)), ' ');
	if (arr == NULL)
		return;
	i = 0;
	while (arr[i] != NULL)
	{
		token = check_token(arr[i]);
		if (token == QUOTE)
		{
			prepare_for_tokenization_quote(arr[i], &data, token);
			free(arr[i]);
		}
		else if (token == WORD)
		{
			prepare_for_tokenization_word(arr[i], &data, token);
			free(arr[i]);
		}
		else if (token == PIPE)
		{
			prepare_for_tokenization_word(arr[i], &data, token);
			free(arr[i]);
		}
		else if (token == REDIRECT)
		{
			prepare_for_tokenization_word(arr[i], &data, token);
			free(arr[i]);
		}
		i++;
	}
	free(arr);
	handle_redirects(data);
	handle_tokens_in_prompt(data, envp, env_vars);
	free_nodes(data);
	// print_node(data);
	// handle_not_existent_builtins(data);
}

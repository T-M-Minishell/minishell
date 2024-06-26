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

t_word_info_redirect	*node_creator(t_list_token *data)
{
	t_list_token			*curr;
	t_word_info_redirect	*cmd_node;
	t_redir_cmds			commands;
	int						length;
	int						i;

	curr = data;
	length = 0;
	commands.arr = NULL;
	commands.next = NULL;
	cmd_node = NULL;
	while (curr != NULL)
	{
		if (curr->type == REDIRECT)
		{
			length++;
			break ;
		}
		length++;
		curr = curr->next;
	}
	curr = data;
	commands.arr = (char **)malloc(sizeof(char *) * (length + 1));
	if (commands.arr == NULL)
	{
		printf("mem allocation failed in new redirect node[1]\n");
		return (NULL);
	}
	i = 0;
	while (curr != NULL)
	{
		commands.arr[i++] = strdup(curr->word);
		if (curr->type == REDIRECT)
		{
			curr = curr->next;
			if ((curr->type != REDIRECT))
			{
				commands.arr[i++] = strdup(curr->word);
			}
			break ;
		}
		curr = curr->next;
	}
	commands.arr[i] = NULL;
	cmd_node = (t_word_info_redirect *)malloc(sizeof(t_word_info_redirect));
	if (!cmd_node)
	{
		printf("mem allocation failed in new redirect node[2]\n");
		return (NULL);
	}
	cmd_node->arr = commands.arr;
	return (cmd_node);
}

void	handle_redirects(t_list_token *data)
{
	t_list_token			*curr;
	t_word_info_redirect	*cmd_nodes;
	int						i;
	int						fd;
	char					**output_file_arr;
	int						j;
	int						length;

	output_file_arr = NULL;
	fd = -1;
	curr = data;
	length = 0;
	cmd_nodes = node_creator(curr);
	if (!cmd_nodes)
	{
		return ;
	}
	while (curr != NULL)
	{
		if (curr->type == REDIRECT)
		{
			length++;
			break ;
		}
		length++;
		curr = curr->next;
	}
	output_file_arr = (char **)malloc(sizeof(char *) * (length + 1));
	if (!output_file_arr)
	{
		return;
	}
	j = 0;
	i = 0;
	while (cmd_nodes->arr[i] != NULL)
	{
		output_file_arr[j] = cmd_nodes->arr[i];
		if (strcmp(cmd_nodes->arr[i], ">") == 0)
		{
			break ;
		}
		i++;
		j++;
	}
	output_file_arr[j] = NULL;
	i = 0;
	while (cmd_nodes->arr[i] != NULL)
	{
		if (strcmp(cmd_nodes->arr[i], ">") == 0 && cmd_nodes->arr[i
			+ 1] != NULL)
		{
			fd = open(cmd_nodes->arr[i + 1], O_WRONLY | O_CREAT | O_TRUNC,
					0644);
			if (fd < 0)
			{
				printf("Error oppening file\n");
				break;
			}
			dup2(fd, STDOUT_FILENO);
			if (fd != -1)
			{
				j = 0;
				while (output_file_arr[j] != NULL && strcmp(output_file_arr[j], ">") != 0)
				{
					printf("%s ", output_file_arr[j]);
					j++;
				}
				printf("\n");
				close(fd);
				break;
			}
		}
		i++;
	}
	// print_node(cmd_node);
	return ;
}

void	handle_tokens_in_prompt(t_list_token *data, char **envp,
		env_var **env_vars)
{
	t_list_token	*curr;

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

void	handle_line(t_input *input, t_list_token *data, char **envp,
		env_var **env_vars)
{
	t_token_type	token;
	char			**arr;
	int				i;
	char			*line_start;

	line_start = input->line;
	if (input->line == NULL)
	{
		printf("exit\n");
		exit(1);
	}
	if (input->line[0] == '\0')
		return ;
	while (*line_start == ' ')
		line_start++;
	if (*line_start == '\0')
		return ;
	arr = custom_split((char *)(input->line + (line_start - input->line)), ' ');
	if (arr == NULL)
		return ;
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

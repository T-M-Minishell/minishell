/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 15:17:35 by msacaliu          #+#    #+#             */
/*   Updated: 2024/07/03 17:43:27 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int count_redirects(t_list_token *data) {
	int count = 0;
	t_list_token *curr = data;

	while (curr != NULL) {
		if (strcmp(curr->word, "<") == 0 || strcmp(curr->word, ">") == 0 ||
			strcmp(curr->word, "<<") == 0 || strcmp(curr->word, ">>") == 0) {
			count++;
		}
		curr = curr->next;
	}
	return count;
}


char **convert_tokens_to_argv_red(t_list_token *curr) {

	int count;
	int i;
	t_list_token *temp;

	temp = curr;
	count = 0;
	// Count the number of tokens until a redirection token is found
	while (temp != NULL && strcmp(temp->word, "<") != 0 && strcmp(temp->word, ">") != 0 &&
		   strcmp(temp->word, "<<") != 0 && strcmp(temp->word, ">>") != 0) {
		count++;
		temp = temp->next;
	}
	// Allocate memory for the command array
	char **argv = malloc((count + 1) * sizeof(char *));
	if (argv == NULL) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	// Copy the tokens into the command array
	i = 0;
	while(i < count)
	{
		argv[i++] = curr->word;
		curr = curr->next;
	}
	argv[count] = NULL;
	return argv;
}

void setup_redirections(char *input_file, char *output_file, int append)
{
	if (input_file != NULL) {
		int fd_in = open(input_file, O_RDONLY);
		if (fd_in < 0) {
			perror("open input file");
			exit(EXIT_FAILURE);
		}
		if (dup2(fd_in, STDIN_FILENO) < 0)
		{
			perror("dup2 input file");
			exit(EXIT_FAILURE);
		}
		close(fd_in);
	}
	if (output_file != NULL) {
		int fd_out;
		if (append == 1)
			fd_out = open(output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd_out = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd_out < 0) {
			perror("open output file");
			exit(EXIT_FAILURE);
		}
		if (dup2(fd_out, STDOUT_FILENO) < 0)
		{
			perror("dup2 output file");
			exit(EXIT_FAILURE);
		}
		close(fd_out);
	}
}

void execute_command_red(t_list_commands_red *cmd, env_var *vars)
{
	char *path;
	int append;

	append = 0;
	int pid = fork();
	if (pid == 0) { // Child process
		// Setup redirections based on cmd->red and cmd->file
		char *input_file = NULL;
		char *output_file = NULL;
		if (strcmp(cmd->red, "<") == 0)
			input_file = cmd->file;
		else if (strcmp(cmd->red, ">") == 0 || strcmp(cmd->red, ">>") == 0)
		{
			output_file = cmd->file;
			if(strcmp(cmd->red, ">>") == 0)
				append = 1;
		}
		setup_redirections(input_file, output_file, append);
		path = get_path(cmd->arr[0], vars); // need to check for path failure
		execve(path, cmd->arr, vars->arr);
		perror("execve");
		exit(EXIT_FAILURE);
	} else if (pid < 0) {
		perror("fork");
	} else
	{
		wait(NULL);// need to get exit status
	}
}

void handle_redirects(t_list_token *data, env_var *vars)
{
	t_list_commands_red *cmd_head = NULL;
	t_list_commands_red *cmd_tail = NULL;
	t_list_token *current = data;

	while (current != NULL) {
		t_list_commands_red *new_cmd = malloc(sizeof(t_list_commands_red));
		if (new_cmd == NULL) {
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		// Initialize the new command node
		new_cmd->arr = convert_tokens_to_argv_red(current);
		new_cmd->red = NULL;
		new_cmd->file = NULL;
		new_cmd->next = NULL;
		// Move the current pointer to the redirection token
		while (current != NULL && strcmp(current->word, "<") != 0 && strcmp(current->word, ">") != 0 &&
			   strcmp(current->word, "<<") != 0 && strcmp(current->word, ">>") != 0) {
			current = current->next;
		}
		// If there's a redirection, set the redirection type and file
		if (current != NULL && (strcmp(current->word, "<") == 0 || strcmp(current->word, ">") == 0 ||
								strcmp(current->word, "<<") == 0 || strcmp(current->word, ">>") == 0)) {
			new_cmd->red = current->word;
			// get the name of the file after redirect
			if (current->next != NULL) {
				new_cmd->file = current->next->word;
				current = current->next->next; // Move past the file token
			} else
			{
				new_cmd->file = NULL;
				current = current->next;
			}
		}
		else
			current = NULL;
		// Append the new command to the list
		if (cmd_head == NULL) {
			cmd_head = new_cmd;
			cmd_tail = new_cmd;
		} else {
			cmd_tail->next = new_cmd;
			cmd_tail = new_cmd;
		}
	}
	// Execute the commands
	t_list_commands_red *cmd_curr = cmd_head;
	while (cmd_curr != NULL)
	{
		execute_command_red(cmd_curr, vars);
		cmd_curr = cmd_curr->next;
	}
	// Free the command list
	cmd_curr = cmd_head;
	while (cmd_curr != NULL) {
		t_list_commands_red *temp = cmd_curr;
		cmd_curr = cmd_curr->next;
		free(temp->arr);
		free(temp);
	}
}


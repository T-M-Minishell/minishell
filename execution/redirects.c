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

void input_file(char *input_file) {
	int fd_in = open(input_file, O_RDONLY);
	if (fd_in < 0) {
		perror("open input file");
		exit(EXIT_FAILURE);
	}
	if (dup2(fd_in, STDIN_FILENO) < 0) {
		perror("dup2 input file");
		exit(EXIT_FAILURE);
	}
	close(fd_in);
}

void output_file(char *red, char *output_file, int is_last) {
	int fd_out;
	int flags;

	flags = O_WRONLY | O_CREAT |  O_TRUNC;
	if(is_last)
		flags = O_WRONLY | O_CREAT | O_APPEND ;
	if (strcmp(red, ">>") == 0 || strcmp(red, ">") == 0) {
		fd_out = open(output_file, flags, 0644);
		if (fd_out < 0) {
			perror("open output file");
			exit(EXIT_FAILURE);
		}

		if (dup2(fd_out, STDOUT_FILENO) < 0) {
			perror("dup2 output file");
			exit(EXIT_FAILURE);
		}

		close(fd_out);
	}
}

void write_to_file(int fd, char *buff)
{
	int i;

	i = ft_strlen(buff);
	write(fd, buff, i);
	write(fd, "\n", 1);
}

int	open_file(char *name, int mode)
{
	if (access(name,F_OK))
		return (open(name, O_CREAT | O_RDWR, 0666));
	else
	{
		if(mode == 1)
			return (open(name, O_WRONLY | O_TRUNC, 0666));
		else if (mode == 2)
			return (open(name, O_WRONLY | O_APPEND, 0666));
	}
	return (-1);
}

void handle_heredoc(char *delimiter)
{
	int temp_fd;
	char *buff;

	temp_fd = open_file("temp_file", 1);
	if (temp_fd == -1)
	{
		close(temp_fd);
		perror("here_doc");
		return ;
	}
	while(1)
	{
		buff = readline("heredoc>");
		if(!buff)
			return ;
		if(strcmp(buff, delimiter) != 0)
			write_to_file(temp_fd, buff);
		else
		{
			close(temp_fd);
			printf("error2 \n");
			return ;
		}
	}

}

void	fd_handeler(t_list_commands_red *current_cmd,t_list_commands_red *last_cmd)
{
	printf("enter ft_handler\n");
	while (current_cmd != NULL) {
		if (strcmp(current_cmd->red, "<") == 0) {
			input_file(current_cmd->file);
		}
		else if (strcmp(current_cmd->red, "<<") == 0) {
			printf("enter statement\n");
			handle_heredoc(current_cmd->file);
		}
		 else if ((strcmp(current_cmd->red, ">") == 0 || strcmp(current_cmd->red, ">>") == 0) && current_cmd == last_cmd) {
			output_file(current_cmd->red, current_cmd->file, 1); // Only redirect STDOUT for the last output file
		} else if ((strcmp(current_cmd->red, ">") == 0 || strcmp(current_cmd->red, ">>") == 0) && current_cmd != last_cmd) {
			output_file(current_cmd->red, current_cmd->file, 0); // Open and close the file to ensure it's created
		}
		current_cmd = current_cmd->next;
	}
}

void execute_command_red(t_list_commands_red *cmd, env_var *vars) {
	char *path;

	int pid = fork();
	if (pid == 0) { // Child process
		t_list_commands_red *current_cmd = cmd;
		t_list_commands_red *last_cmd = NULL;
		// Find the last output redirection command
		while (current_cmd != NULL) {
			if (strcmp(current_cmd->red, ">") == 0 || strcmp(current_cmd->red, ">>") == 0)
				last_cmd = current_cmd;
			current_cmd = current_cmd->next;
		}
		// Reset to start of list
		current_cmd = cmd;
		fd_handeler(current_cmd,last_cmd);
		// Execute the command
		path = get_path(cmd->arr[0], vars); // Assume get_path is a function that retrieves the command's path
		execve(path, cmd->arr, vars->arr);
		printf("test after execve\n");
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else {
		wait(NULL); // Parent process waits for the child process to complete
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


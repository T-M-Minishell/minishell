/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:34:38 by msacaliu          #+#    #+#             */
/*   Updated: 2024/07/01 17:20:43 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int count_nb_of_pipes(t_list_token *data)
{
	int nb;

	nb = 0;
	t_list_token *curr = data;

	while (curr != NULL) {
		if (strcmp(curr->word, "|") == 0)
			nb++;
		curr = curr->next;
	}
	return nb;
}

char **convert_tokens_to_argv(t_list_token *data) {
	int count = 0;
	t_list_token *current = data;

	// Step 1: Count the tokens
	while (current != NULL && strcmp(current->word, "|") != 0) {
		count++;
		current = current->next;
	}
	// Step 2: Allocate memory for argv
	char **argv = malloc((count + 1) * sizeof(char *)); // +1 for NULL terminator
	if (argv == NULL) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	// Step 3: Fill argv
	current = data;
	for (int i = 0; i < count; i++) {
		if (strcmp(current->word, "|") == 0)
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


int count_commands(t_list_commands *cmd) {
	int num_cmds = 0;
	t_list_commands *current = cmd;
	while (current != NULL) {
		num_cmds++;
		current = current->next;
	}
	return num_cmds;
}

int (*allocate_pipes(int num_cmds))[2] {
	if (num_cmds < 2)
		return NULL;
	int (*pipes)[2] = malloc(sizeof(int[2]) * (num_cmds - 1));
	if (pipes == NULL) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	return pipes;
}

void create_pipes(int (*pipes)[2], int num_cmds) {
	int i = 0;
	while (i < num_cmds - 1) {
		if (pipe(pipes[i]) == -1) {
			perror("pipe");
			free(pipes);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}


void cleanup_pipes_and_wait(int (*pipes)[2], int num_cmds) {
	int j = 0;
	while (j < num_cmds - 1) {
		close(pipes[j][0]);
		close(pipes[j][1]);
		j++;
	}

	j = 0;
	while (j < num_cmds) {
		wait(NULL);
		j++;
	}

	free(pipes);
}

env_var *implementing_pipe(t_list_commands *cmd, env_var *env_vars, t_list_token *data) {
	env_vars->num_cmds = count_commands(cmd);
	(void) data; // Suppress unused variable warning

	if (env_vars->num_cmds < 1) return env_vars;

	int (*pipes)[2] = allocate_pipes(env_vars->num_cmds);
	if (pipes != NULL) create_pipes(pipes, env_vars->num_cmds);

	env_vars = execute_commands(cmd, pipes, env_vars);
	if (pipes != NULL) cleanup_pipes_and_wait(pipes, env_vars->num_cmds);

	return env_vars;
}


void free_command_list(t_list_commands *cmd_head) {
	while (cmd_head != NULL) {
		t_list_commands *temp = cmd_head;
		cmd_head = cmd_head->next;

		for (int i = 0; temp->arr[i] != NULL; i++) {
			free(temp->arr[i]); // Free each string in arr
		}
		free(temp->arr);
		free(temp);
	}
}

env_var *handle_pipe(t_list_token *data, env_var *env_vars) {
	t_list_commands *cmd_head = NULL;
	t_list_commands *cmd_tail = NULL;
	t_list_token *current = data;

	while (current != NULL) {
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
		if (cmd_head == NULL) {
			cmd_head = new_cmd;
			cmd_tail = new_cmd;
		} else {
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
	env_vars = implementing_pipe(cmd_head, env_vars, data);
	free_command_list(cmd_head);
	return env_vars;
}

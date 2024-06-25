/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:34:38 by msacaliu          #+#    #+#             */
/*   Updated: 2024/06/24 16:04:26 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

char *find_path(t_list_commands *cmd) {
	t_list_commands *command;
	char *path;

	command = cmd;

	if (strcmp(command->arr[0], "pwd") == 0) // mayb not need here
		path = "/bin/pwd";
	else if (strcmp(command->arr[0], "clear") == 0)
		path = "/bin/clear";
	else if (strcmp(command->arr[0], "rm") == 0)
		path = "/bin/rm";
	else if (strcmp(command->arr[0], "mv") == 0)
		path = "/bin/mv";
	else if (strcmp(command->arr[0], "mkdir") == 0)
		path = "/bin/mkdir";
	else if (strcmp(command->arr[0], "ls") == 0)
		path = "/bin/ls";
	else if (strcmp(command->arr[0], "touch") == 0)
		path = "/bin/touch";
	else if (strcmp(command->arr[0], "cat") == 0)
		path = "/bin/cat";
	else if (strcmp(command->arr[0], "wc") == 0)
		path = "/usr/bin/wc";
	else if (strcmp(command->arr[0], "grep") == 0)
		path = "/bin/grep";
	else if (strcmp(command->arr[0], "expr") == 0)
		path = "/usr/bin/expr";
	else
		path = NULL;
	return (path);
}


int count_nb_of_pipes(t_list_token *data) {
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
/////----------------EXECUTION----------------------

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

env_var *execute_commands(t_list_commands *cmd, int num_cmds, int (*pipes)[2], env_var *env_vars) {
	t_list_commands *current = cmd;
	int i = 0;
	int pid;
	int j;
	env_var *vars = env_vars;
	int status = 0;
	int exit_status = 0;

	while (i < num_cmds) {
		if (check_if_builtin(current->arr[0])) {
			if (execute_builtins_with_no_output(current->arr) == 1) {
				current = current->next;
				num_cmds--;
				continue;
			}
			if (check_for_env_commands(current->arr)) {
				vars = exec_env_var_fct(current->arr, vars);
				current = current->next;
				num_cmds--;
				continue;
			}
		}

		pid = fork();
		if (pid < 0) {
			perror("fork");
			free(pipes);
			exit(EXIT_FAILURE);
		} else if (pid == 0) { // child process
			if (i > 0)
				dup2(pipes[i - 1][0], STDIN_FILENO);
			if (i < num_cmds - 1)
				dup2(pipes[i][1], STDOUT_FILENO);

			for (j = 0; j < num_cmds - 1; j++) {
				close(pipes[j][0]);
				close(pipes[j][1]);
			}

			if (check_if_builtin(current->arr[0])) {
				if (execute_builtins_with_output(current->arr, vars) == 1)
					_exit(EXIT_SUCCESS);
			} else {
				char *path = find_path(current);
				execve(path, current->arr, vars->arr);
				perror("execve");
				_exit(127);
			}
		} else { // parent process
			if (i > 0)
				close(pipes[i - 1][0]);
			if (i < num_cmds - 1)
				close(pipes[i][1]);
			if (strcmp(current->arr[0], "cat") != 0)
				waitpid(pid,&status,0);
			if (WIFEXITED(status)) {
                exit_status = WEXITSTATUS(status);
                if (exit_status != 0) {
                    vars->exit_status = exit_status;
                }
            } else if (WIFSIGNALED(status))
                vars->exit_status = WTERMSIG(status);
		}
		current = current->next;
		i++;
	}
	return vars;
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
	int num_cmds = count_commands(cmd);
	(void) data; // Suppress unused variable warning

	if (num_cmds < 1) return env_vars;

	int (*pipes)[2] = allocate_pipes(num_cmds);
	if (pipes != NULL) create_pipes(pipes, num_cmds);

	env_vars = execute_commands(cmd, num_cmds, pipes, env_vars);
	if (pipes != NULL) cleanup_pipes_and_wait(pipes, num_cmds);

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




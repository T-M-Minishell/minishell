/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 15:17:35 by msacaliu          #+#    #+#             */
/*   Updated: 2024/07/09 17:55:53 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_redirects(t_list_token *data)
{
	int				count;
	t_list_token	*curr;

	count = 0;
	curr = data;
	while (curr != NULL)
	{
		if (strcmp(curr->word, "<") == 0 || strcmp(curr->word, ">") == 0 ||
			strcmp(curr->word, "<<") == 0 || strcmp(curr->word, ">>") == 0)
			count++;
		curr = curr->next;
	}
	return (count);
}

char	**convert_tokens_to_argv_red(t_list_token *curr)
{
	int				count;
	int				i;
	t_list_token	*temp;
	char			**argv;

	temp = curr;
	count = 0;
	while (temp != NULL && strcmp(temp->word, "<") != 0
		&& strcmp(temp->word, ">") != 0
		&& strcmp(temp->word, "<<") != 0 && strcmp(temp->word, ">>") != 0)
	{
		count++;
		temp = temp->next;
	}
	argv = malloc((count + 1) * sizeof(char *));
	if (argv == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < count)
	{
		argv[i++] = curr->word;
		curr = curr->next;
	}
	argv[count] = NULL;
	return (argv);
}

void	input_file(char *input_file)
{
	int	fd_in;

	fd_in = open(input_file, O_RDONLY);
	if (fd_in < 0)
	{
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

void	output_file(char *red, char *output_file, int is_last)
{
	int	fd_out;
	int	flags;

	flags = O_WRONLY | O_CREAT | O_TRUNC;
	if (is_last)
	{
		flags = O_WRONLY | O_CREAT;
		if (strcmp(red, ">>") == 0 )
			flags = O_WRONLY | O_CREAT | O_APPEND;
	}
	if (strcmp(red, ">>") == 0 || strcmp(red, ">") == 0)
	{
		fd_out = open(output_file, flags, 0644);
		if (fd_out < 0)
		{
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

void	input_file_from_temp(void)
{
	int	fd_in;

	fd_in = open("temp_file", O_RDONLY);
	if (fd_in < 0)
	{
		perror("open temp_file");
		exit(EXIT_FAILURE);
	}
	if (dup2(fd_in, STDIN_FILENO) < 0)
	{
		perror("dup2 temp_file");
		exit(EXIT_FAILURE);
	}
	close(fd_in);
}

void	handle_heredoc(char *delimiter)
{
	int		temp_fd;
	char	*buff;

	temp_fd = open("temp_file", O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (temp_fd == -1)
	{
		perror("open temp_file");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		buff = readline("heredoc> ");
		if (!buff)
			break ;
		if (strcmp(buff, delimiter) == 0)
		{
			free(buff);
			break ;
		}
		write(temp_fd, buff, strlen(buff));
		write(temp_fd, "\n", 1);
		free(buff);
	}
	close(temp_fd);
}

void	fd_handeler(t_list_commands_red *current_cmd,t_list_commands_red *last_cmd)
{
	while (current_cmd != NULL)
	{
		if (strcmp(current_cmd->red, "<") == 0)
			input_file(current_cmd->file);
		else if (strcmp(current_cmd->red, "<<") == 0)
		{
			handle_heredoc(current_cmd->file);
			input_file_from_temp();
		}
		else if ((strcmp(current_cmd->red, ">") == 0
				|| strcmp(current_cmd->red, ">>") == 0)
			&& current_cmd == last_cmd)
		{
			output_file(current_cmd->red, current_cmd->file, 1);
		}
		else if ((strcmp(current_cmd->red, ">") == 0
				|| strcmp(current_cmd->red, ">>") == 0)
			&& current_cmd != last_cmd)
		{
			output_file(current_cmd->red, current_cmd->file, 0);
		}
		current_cmd = current_cmd->next;
	}
}

void	execute_command_red(t_list_commands_red *cmd, t_env_var *vars)
{
	char				*path;
	int					status;
	int					pid;
	t_list_commands_red	*current_cmd;
	t_list_commands_red	*last_cmd;

	status = 0;
	pid = fork();
	if (pid == 0)
	{
		current_cmd = cmd;
		last_cmd = NULL;
		while (current_cmd != NULL)
		{
			if (strcmp(current_cmd->red, ">") == 0
				|| strcmp(current_cmd->red, ">>") == 0)
				last_cmd = current_cmd;
			current_cmd = current_cmd->next;
		}
		current_cmd = cmd;
		fd_handeler(current_cmd, last_cmd);
		if (current_cmd->arr[0] == NULL)
			exit(127);
		path = get_path(current_cmd->arr[0], vars);
		if (!path)
		{
			printf("%s: command not found\n", cmd->arr[0]);
			free(path);
			_exit(127);
		}
		execve(path, cmd->arr, vars->arr);
		free(path);
		perror("execve");
		exit(127);
	}
	else
	{
		waitpid(pid, &status, 0);
		unlink("temp_file");
		if (WIFEXITED(status))
			vars->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			vars->exit_status = WTERMSIG(status);
	}
}

void	handle_redirects(t_list_token *data, t_env_var *vars)
{
	t_list_commands_red	*cmd_head;
	t_list_commands_red	*cmd_tail;
	t_list_token		*current;
	t_list_commands_red	*new_cmd;
	t_list_commands_red	*cmd_curr;
	t_list_commands_red	*temp;

	cmd_head = NULL;
	cmd_tail = NULL;
	current = data;
	while (current != NULL && strcmp(current->word, "|") != 0)
	{
		new_cmd = malloc(sizeof(t_list_commands_red));
		if (new_cmd == NULL)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		new_cmd->arr = convert_tokens_to_argv_red(current);
		new_cmd->red = NULL;
		new_cmd->file = NULL;
		new_cmd->next = NULL;
		while (current != NULL && strcmp(current->word, "<") != 0
			&& strcmp(current->word, ">") != 0
			&& strcmp(current->word, "<<") != 0
			&& strcmp(current->word, ">>") != 0)
		{
			current = current->next;
		}
		if (current != NULL && (strcmp(current->word, "<") == 0
				|| strcmp(current->word, ">") == 0
				|| strcmp(current->word, "<<") == 0
				|| strcmp(current->word, ">>") == 0))
		{
			new_cmd->red = current->word;
			if (current->next != NULL)
			{
				new_cmd->file = current->next->word;
				current = current->next->next;
			}
			else
			{
				new_cmd->file = NULL;
				current = current->next;
			}
		}
		else
			current = NULL;
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
	}
	cmd_curr = cmd_head;
	while (cmd_curr != NULL)
	{
		execute_command_red(cmd_curr, vars);
		cmd_curr = cmd_curr->next;
	}
	cmd_curr = cmd_head;
	while (cmd_curr != NULL)
	{
		temp = cmd_curr;
		cmd_curr = cmd_curr->next;
		free(temp->arr);
		free(temp);
	}
}

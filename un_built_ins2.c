/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   un_built_ins2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 20:37:01 by tlupu             #+#    #+#             */
/*   Updated: 2024/06/09 14:33:24 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void mini_cat(t_list_token *data)
{
	int fd;
	ssize_t bytes;
	char buf[BUF_SIZE];
	t_list_token	*curr;

	curr = data->next;
	if(!curr)
		return ;
	if (curr->word == NULL || strcmp(curr->word, "-") == 0)
		fd = STDIN_FILENO;
	else
	{
		fd = open(curr->word, O_RDONLY);
		if (fd == -1)
		{
			perror("open");
			return;
		}
	}

	while ((bytes = read(fd, buf, BUF_SIZE)) > 0)
	{
		if (write(STDOUT_FILENO, buf, bytes) != bytes)
		{
			perror("write");
			close(fd);
			return;
		}
	}
	printf("\n");
	if (bytes == -1)
		perror("read");
	if (fd != STDIN_FILENO)
		close(fd);
}


void mini_touch(t_list_token *data, env_var *vars)
{
	int fd;
	(void)vars;
	t_list_token *curr;

	curr = data->next;
	if(!curr)
	{
		printf("Try 'touch --help' for more information.\n");
		return;
	}
	if (curr->word == NULL)
	{
		fprintf(stderr, "mini_touch: missing file operand\n");
		return;
	}
	fd = open(curr->word, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("open");
		return;
	}
	close(fd);
}

void min_mv(t_list_token *data)
{
	int src_fd, dest_fd;
	ssize_t bytes;
	char buf[BUF_SIZE];
	t_list_token *curr;
	char *src;
	char *dest;

	curr = data->next;
	if(!curr)
	{
		printf("Try 'mv --help' for more information.\n");
		return;
	}
	src = curr->word;
	if(curr->next)
		dest = curr->next->word;
	else
	{
		printf("Try 'mv --help' for more information.\n");
		return ;
	}
	if (src == NULL || dest == NULL)
	{
		printf("mv: missing file operand\n");
		return;
	}
	src_fd = open(src, O_RDONLY);
	if (src_fd == -1)
	{
		perror("open");
		return;
	}
	dest_fd = open(dest, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (dest_fd == -1)
	{
		perror("open");
		close(src_fd);
		return;
	}
	while ((bytes = read(src_fd, buf, BUF_SIZE)) > 0)
	{
		if (write(dest_fd, buf, bytes) != bytes)
		{
			perror("write");
			close(src_fd);
			close(dest_fd);
			return;
		}
	}
	if (bytes == -1)
		perror("read");
	close(src_fd);
	close(dest_fd);
	if (unlink(src) == -1)
		perror("unlink");
}

//void mini_wc(t_list_token *data, int lines, int words, int chars)
//{
//	int fd;
//	size_t bytes;
//	char buf[BUF_SIZE];
//	int newline_count = 0;
//	int word_count = 0;
//	int byte_count = 0;
//	int in_word = 0;
//
//	if (str == NULL || strcmp(str, "-") == 0)
//		fd = STDIN_FILENO;
//	else
//	{
//		fd = open(str, O_RDONLY);
//		if (fd == -1) {
//			perror("open");
//			return;
//		}
//	}
//	while ((bytes = read(fd, buf, BUF_SIZE)) > 0)
//	{
//		for (size_t i = 0; i < bytes; i++)
//		{
//			if (buf[i] == '\n')
//				newline_count++;
//			if (isspace(buf[i]))
//				in_word = 0;
//			else if (!in_word)
//			{
//				word_count++;
//				in_word = 1;
//			}
//		}
//		byte_count += bytes;
//	}
//	if (bytes == -1)
//		perror("read");
//	if (fd != STDIN_FILENO)
//		close(fd);
//	if (lines)
//		printf("%d ", newline_count);
//	if (words)
//		printf("%d ", word_count);
//	if (chars)
//		printf("%d ", byte_count);
//	printf("%s\n", str);
//}
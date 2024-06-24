/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   un_built_ins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 20:22:13 by tlupu             #+#    #+#             */
/*   Updated: 2024/06/24 19:29:47 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>

void print_long_format(struct dirent *dir) {
	struct stat file_stat;
	struct passwd *pw;
	struct group *gr;
	char time_buf[80];
	struct tm lt;

	if (stat(dir->d_name, &file_stat) == -1)
	{
		perror("stat");
		return;
	}
	// File type and permissions
	printf((S_ISDIR(file_stat.st_mode)) ? "d" : "-");
	printf((file_stat.st_mode & S_IRUSR) ? "r" : "-");
	printf((file_stat.st_mode & S_IWUSR) ? "w" : "-");
	printf((file_stat.st_mode & S_IXUSR) ? "x" : "-");
	printf((file_stat.st_mode & S_IRGRP) ? "r" : "-");
	printf((file_stat.st_mode & S_IWGRP) ? "w" : "-");
	printf((file_stat.st_mode & S_IXGRP) ? "x" : "-");
	printf((file_stat.st_mode & S_IROTH) ? "r" : "-");
	printf((file_stat.st_mode & S_IWOTH) ? "w" : "-");
	printf((file_stat.st_mode & S_IXOTH) ? "x" : "-");
	// Number of hard links
	printf(" %ld", (long) file_stat.st_nlink);
	// Owner name
	pw = getpwuid(file_stat.st_uid);
	printf(" %s", pw ? pw->pw_name : "UNKNOWN");
	// Group name
	gr = getgrgid(file_stat.st_gid);
	printf(" %s", gr ? gr->gr_name : "UNKNOWN");
	// File size
	printf(" %5ld", (long) file_stat.st_size);
	// Last modification time
	localtime_r(&file_stat.st_mtime, &lt);
	strftime(time_buf, sizeof(time_buf), "%b %d %H:%M", &lt);
	printf(" %s", time_buf);

	// File name
	printf(" %s\n", dir->d_name);
}

void mini_ls(int show_all, int long_format) {
	DIR *d;
	struct dirent *dir;

	d = opendir(".");
	if (d) {
		while ((dir = readdir(d)) != NULL)
		{
			// Skip hidden files if -a is not set
			if (!show_all && dir->d_name[0] == '.')

				continue;
			if (long_format)
				print_long_format(dir);
			else
				printf("%s\n", dir->d_name);
		}
		closedir(d);
	}
	else
		perror("opendir");
}

void    mini_mkdir(t_list_token *data,env_var *vars)
{
	pid_t       pid;
	char        *path;
	t_list_token *curr;

	curr = data->next;
	if(!curr)
	{
		printf("Try 'mkdir --help' for more information.\n");
		return;
	}
	char *arr[] = {"/bin/mkdir", curr->word, NULL};

	path = "/bin/mkdir";
	pid = fork();
	if (pid < 0)
	{
		perror("ERROR WITH PID\n");
		return ;
	}
	else if (pid == 0)
		execve(path, arr, vars->arr);
	else
		wait(NULL);
}
void mini_rm(t_list_token *data, env_var *vars)
{
    pid_t pid;
    char *path = "/bin/rm";
    t_list_token *curr = data->next; // Skip the command itself to get to the arguments

    // Skip any empty arguments (spaces)
    while (curr != NULL && strcmp(curr->word, "") == 0) {
        curr = curr->next;
    }

    // Check if there's actually something to remove
    if (!curr)
	{
        printf("Try 'rm --help' for more information.\n");
        return;
    }

    // Prepare the arguments for execve
    char *arr[] = {path, "-rf", curr->word, NULL}; // Assuming you want to always use -rf

    pid = fork();
    if (pid < 0) {
        perror("ERROR WITH PID\n");
        return;
    } else if (pid == 0) {
        execve(path, arr, vars->arr);
        exit(EXIT_FAILURE); // If execve returns, it failed
    } else {
        wait(NULL); // Wait for the child process to finish
    }
}


void    mini_clean(env_var *vars)
{
	pid_t       pid;
	char        *path;

	char *arr[] = {"/bin/clear", NULL};

	path = "/bin/clear";
	pid = fork();
	if (pid < 0)
	{
		perror("ERROR WITH PID\n");
		return ;
	}
	else if (pid == 0)
		execve(path, arr, vars->arr);
	else
		wait(NULL);
}

void init_ls(t_list_token *curr)
{
	int show_all = 0;
	int long_format = 0;
	t_list_token *arg = curr->next;
	while (arg != NULL) {
		if (strcmp(arg->word, "-a") == 0 || strcmp(arg->word, "-la") == 0) {
			show_all = 1;
		}
		if (strcmp(arg->word, "-l") == 0 || strcmp(arg->word, "-la") == 0) {
			long_format = 1;
		}
		arg = arg->next;
	}
	mini_ls(show_all, long_format);
}

void    handle_not_existent_builtins(t_list_token *data, env_var **vars)
{
	t_list_token    *curr;
	(void)vars;
	curr = data;

	if (curr->word != NULL)
	{
		if (strcmp(curr->word, "ls") == 0)
			init_ls(curr);
		if (strcmp(curr->word, "mkdir") == 0)
			mini_mkdir(curr, *vars);
		if (strcmp(curr->word, "rm") == 0)
			mini_rm(curr, *vars);
		if (strcmp(curr->word, "clear") == 0)
			mini_clean(*vars);
		if (strcmp(curr->word, "cat") == 0)
			mini_cat(curr);
		if (strcmp(curr->word, "touch") == 0)
			mini_touch(curr, *vars); ///
		if (strcmp(curr->word, "mv") == 0)
			min_mv(curr);
		if (strcmp(curr->word, "wc") == 0)
		  	mini_wc(curr,1,1,1);
		// if (strcmp(curr->word, "expr") == 0)
		//   	mini_expr(curr, *vars);
	}
}

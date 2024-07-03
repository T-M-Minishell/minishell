#include "../minishell.h"


// int main(void)
// {
// 	int pid = fork();
// 	if (pid == -1)
// 	{
// 		return(1);
// 	}
// 	if(pid == 0)
// 	{
// 		int file = open("pingresults.txt",O_WRONLY | O_CREAT,0777);
// 		if(file == -1)
// 			return(2);
// 		int file2 = dup2(file,STDOUT_FILENO);
// 		printf("test: %d\n",file2);
// 		close(file);
// 		int err = execlp("ping", "ping", "-c", "1", "google.com",NULL);
// 		if(err == -1)
// 		{
// 			printf("error err\n");
// 			return(2);
// 		}
// 	}
// 	return (0);
// }

// void	redirect_input(char *input)
// {
// 	int fd = open(input, O_RDONLY);
// 	if(fd < 0)
// 	{
// 		perror("open");
// 		return ;
// 	}
// 	int fd2 = dup2(fd, STDIN_FILENO);
// 	if(fd2 < 0)
// 	{
// 		perror("dup2");
// 		close(fd2);
// 		return ;
// 	}
// 	close(fd);
// }


void	redirect_output(char *command, char *output)
{
	int fd = open(output,O_WRONLY | O_CREAT, 0777);
	if(fd == -1)
	{
		perror("error fd\n");
		return ;
	}
	int fd2 = dup2(fd,STDOUT_FILENO);

	if(fd2 == -1)
	{
		perror("fd2 error\n");
		return ;
	}
	printf("%s\n",command);
		close(fd);
}

void	append_output(char *command, char *output)
{
	int fd = open(output,O_WRONLY | O_CREAT | O_APPEND, 0777);
	if(fd == -1)
	{
		perror("error fd\n");
		return ;
	}
	int fd2 = dup2(fd,STDOUT_FILENO);

	if(fd2 == -1)
	{
		perror("fd2 error\n");
		return ;
	}
	printf("%s\n",command);
		close(fd);
}




int main(int argc, char *argv[])
{
	// char buffer[1024];
	// redirect_input(argv[1]);
    // ssize_t bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
    // if (bytes_read > 0)
    // {
    //     buffer[bytes_read] = '\0'; // Null-terminate the string
    //     printf("Read from redirected input:\n%s\n", buffer);
    // }
    // else
    // {
    //     perror("read");
    // }
	// redirect_output(argv[1], argv[2]);
	append_output(argv[1], argv[2]);

	
	return(0);
}



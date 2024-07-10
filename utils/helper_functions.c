/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 19:19:12 by msacaliu          #+#    #+#             */
/*   Updated: 2024/07/10 21:37:51 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_exec_args(char *path, char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		free(argv[i++]);
	free(argv);
	free (path);
}

t_env_var	*remove_env_var(char *command, t_env_var *env_vars)
{
	int		flag;
	char	*key;
	int		j;

	flag = 0;
	j = -1;
	while (env_vars->arr[++j] != NULL)
	{
		key = get_key_from_word(env_vars->arr[j]);
		if (strcmp(command, key) == 0)
		{
			flag = 1;
			free(key);
			break ;
		}
		free(key);
	}
	if (flag == 1)
		env_vars = delete_env_var(env_vars, command);
	return (env_vars);
}

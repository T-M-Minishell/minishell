/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env_variables.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 18:06:50 by msacaliu          #+#    #+#             */
/*   Updated: 2024/05/22 18:06:51 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


//bool check_if_alphanumeric(char *str)
//{
//	for (int i = 0; str[i]; i++)
//	{
//		if (!isalnum((unsigned char)str[i]) && str[i] != '=')
//		{
//			return false;
//		}
//	}
//	return true;
//}
//

env_var	*get_env_vars(char** envp)
{
	int	i;
	int	j;
	char *key;
	char *value;

	i = 0;
	j = 0;

	while (envp[i] != NULL)
		i++;
	env_var	*env_vars = malloc((i + 1) * sizeof(env_var));  // Allocate an extra element
	if (env_vars == NULL)
		return (NULL);
	while (j < i)
	{
		key = envp[j];
		value = strchr(envp[j],'=');
		if (value != NULL)
		{
			*value = '\0';
			value++;
		}
		env_vars[j].key = strdup(key);
		env_vars[j].value = strdup(value);
		if (value != NULL)
			*(value - 1) = '=';  // Restore the '='
		j++;
	}
	env_vars[i].key = NULL;  // Null terminate the array
	env_vars[i].value = NULL;  // Null terminate the array
	return env_vars;
}


env_var* add_env_var(env_var* old_env_vars, char *word)
{
	int i = 0;
	while (old_env_vars[i].key != NULL)
		i++;

	// Allocate a new array with an extra element
	env_var* new_env_vars = malloc((i + 2) * sizeof(env_var));
	if (new_env_vars == NULL)
		return NULL; // Handle memory allocation failure

	// Copy old elements to the new array
	for (int j = 0; j < i; j++) {
		new_env_vars[j].key = strdup(old_env_vars[j].key);
		new_env_vars[j].value = strdup(old_env_vars[j].value);
	}
	// Free the old array
	for (int j = 0; j < i; j++) {
		free(old_env_vars[j].key);
		free(old_env_vars[j].value);
	}
	free(old_env_vars);

	// Add the new element
	char *equals_pos = strchr(word, '=');
	if (equals_pos != NULL) {
		*equals_pos = '\0';  // Temporarily terminate the key string
		char *key = word;
		char *value = equals_pos + 1;  // Move past the '='

		new_env_vars[i].key = strdup(key);
		new_env_vars[i].value = strdup(value);

		*equals_pos = '=';  // Restore the '='
	}
	// Null terminate the array
	new_env_vars[i + 1].key = NULL;
	new_env_vars[i + 1].value = NULL;

	return new_env_vars;
}
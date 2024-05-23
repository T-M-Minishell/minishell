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

void create_env_variable(t_dictionary *variable, char *str)
{
	int i;
	int j;

	j = 0;
	i = -1;
	while (str[++i] != '=')
		variable->key[i] = str[i];
	variable->key[i] = '\0';
	i++;
	while (str[i] != '\0')
		variable->value[j++] = str[i++];
	variable->value[j] = '\0';
	setenv(variable->key, variable->value, 1);
}

void	create_var(t_list_token *data)
{
	t_dictionary *dictionary = malloc(sizeof(t_dictionary));
	create_env_variable(dictionary, data->word);
}


//int main(void) {
//	t_dictionary *dictionary = malloc(sizeof(t_dictionary));
//	create_env_variable(dictionary, "Tpula=vasile");
//	printf("%s\n", dictionary->key);
//	printf("%s\n", dictionary->value);
//
//	free(dictionary);
//
//	return 0;
//}
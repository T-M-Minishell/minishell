/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:11:28 by msacaliu          #+#    #+#             */
/*   Updated: 2024/05/27 14:11:29 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int ft_strcmp_mod(char *str1, char *str2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while(str1[i] != '\0')
	{
		while(str1[i] == ' ')
			i++;
		if(str1[i] != str2[j])
			return(-1);
		i++;
		j++;
	}
	return(0);
}

char	*ft_strdup(char *s1)
{
	int		i;
	char	*new_string;

	i = 0;
	new_string = (char *) malloc((strlen(s1)+1));
	if (!new_string)
		return (NULL);
	while (s1[i] != '\0')
	{
		new_string[i] = s1[i];
		i++;
	}
	new_string[i] = '\0';
	return (new_string);
}
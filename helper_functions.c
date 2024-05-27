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
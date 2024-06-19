/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlupu <tlupu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 15:03:22 by tlupu             #+#    #+#             */
/*   Updated: 2024/06/19 12:15:53 by tlupu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list_token	*ft_lstlast(t_list_token *lst)
{
	t_list_token	*current;

	current = lst;
	while (current != NULL)
	{
		if (current->next == NULL)
			break ;
		current = current->next;
	}
	return (current);
}

char	*ft_strdup(const char *s1)
{
	int		i;
	int		j;
	char	*s2;

	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		i++;
	}
	s2 = (char *)malloc((i + 1) * sizeof(char));
	if (s2 == NULL)
	{
		return (NULL);
	}
	while (j <= i)
	{
		s2[j] = s1[j];
		j++;
	}
	return (s2);
}

void	print_node(t_list_token *node)
{
	if (node == NULL)
	{
		printf("Node is NULL\n");
		return ;
	}
	printf("Node content:\n");
	printf("Index: %d\n", node->index);
	printf("Type: %d\n", node->type);
	printf("List node elements are: %s\n", node->word ? node->word : "(null)");
	// Print other fields as needed
}

void free_list(t_list_token *head)
{
	t_list_token *tmp;

	while (head != NULL) {
		tmp = head;
		head = head->next;
		if (tmp->word)
			free(tmp->word);
		free(tmp);
	}
}
+
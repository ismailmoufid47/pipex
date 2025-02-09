/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-mou <isel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 21:52:09 by isel-mou          #+#    #+#             */
/*   Updated: 2025/02/08 20:17:01 by isel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	count_substrings_cmd(char *str, char c)
{
	int		count;
	int		i;
	char	quote;

	count = ((i = 0), (quote = 0), 0);
	while (str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i])
		{
			count++;
			while (str[i] && (str[i] != c || quote))
			{
				if (!quote && (str[i] == '\'' || str[i] == '\"'))
					quote = str[i++];
				else if (quote && str[i] == quote)
					quote = ((i++), 0);
				else
					i++;
			}
		}
	}
	return (count);
}

void	fill_substring_cmd(char *str, char c, char *tab, int *i)
{
	int	k;
	int	quote;

	k = 0;
	quote = 0;
	while (str[*i] && (str[*i] != c || quote))
	{
		if (!quote && (str[*i] == '\'' || str[*i] == '\"'))
			quote = str[(*i)++];
		else if (quote && str[*i] == quote)
		{
			quote = 0;
			(*i)++;
		}
		else
			tab[k++] = str[(*i)++];
	}
	tab[k] = '\0';
}

char	**fill_table_cmd(char *str, char c, int substr_count)
{
	char	**tab;
	int		i;
	int		j;

	tab = ((i = 0), (j = 0), malloc(sizeof(char *) * (substr_count + 1)));
	if (!tab)
		return (NULL);
	while (str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i])
		{
			tab[j] = malloc(sizeof(char) * (ft_strlen(str) + 1));
			if (!tab[j])
				return (free_table(tab, j));
			fill_substring_cmd(str, c, tab[j], &i);
			j++;
		}
	}
	tab[j] = NULL;
	return (tab);
}

char	**ft_split_cmd(char *str, char c)
{
	int	substr_count;

	substr_count = count_substrings_cmd(str, c);
	return (fill_table_cmd(str, c, substr_count));
}

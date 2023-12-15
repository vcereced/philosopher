/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 19:35:29 by vcereced          #+#    #+#             */
/*   Updated: 2023/06/21 13:38:40 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	msg_error(char *str)
{
	write(2, str, ft_strlen(str));
	return (1);
}

int	check_arg(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc < 5 || argc > 6)
	{
		msg_error("Nº arg wrong");
		return (1);
	}
	if (ft_atoi(argv[1]) > 200 || ft_atoi(argv[1]) <= 0)
		return (msg_error("nº philos wrong"));
	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < 48 || argv[i][j] > 57)
			{
				return (msg_error("NaN arg"));
			}
			j++;
		}
		i++;
	}
	return (0);
}

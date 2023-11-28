/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeharahikaru <maeharahikaru@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 03:37:27 by maeharahika       #+#    #+#             */
/*   Updated: 2023/11/27 03:34:21 by maeharahika      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	num_check(char *s)
{
	size_t	i;
	long	num;

	i = 0;
	num = 0;
	while (s[i])
	{
		if (s[i] < '0' || '9' < s[i])
			return (EXIT_FAILURE);
		num = (num * 10) + (s[i] - '0');
		if (num > INT_MAX)
			return (EXIT_FAILURE);
		i += 1;
	}
	return (EXIT_SUCCESS);
}

static int	check_arg(int argc, char **argv)
{
	int	i;

	if (argc < 5 || 6 < argc)
		return (EXIT_FAILURE);
	i = 1;
	while (argv[i])
	{
		if (num_check(argv[i]) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		i += 1;
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_table	tbl;

	if (check_arg(argc, argv) == EXIT_FAILURE)
	{
		printf("Error: Wrong arguments.\n");
		return (EXIT_FAILURE);
	}
	if (init_handler(&tbl, argc, argv) == EXIT_FAILURE)
	{
		printf("initialization of philosophers failed.\n");
		printf("number of philosophers must be 0 < n.\n");
		printf("time to eat and time to sleep must be 0ms < n.\n");
		return (EXIT_FAILURE);
	}
	thread_handler(&tbl);
	final_handler(&tbl);
	return (EXIT_SUCCESS);
}

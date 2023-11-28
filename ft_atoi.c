/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeharahikaru <maeharahikaru@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 03:37:58 by maeharahika       #+#    #+#             */
/*   Updated: 2023/11/24 03:48:32 by maeharahika      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static const char	*ft_prefix_atoi(const char *s, bool *is_minus)
{
	while (*s == '\t' || *s == '\n' || *s == '\v' || \
			*s == '\f' || *s == '\r' || *s == ' ')
		s++;
	if (*s == '-')
		*is_minus = true;
	if (*s == '-' || *s == '+')
		s++;
	return (s);
}

static long	get_digit_atoi(char c)
{
	if ('0' <= c && c <= '9')
		return (c - '0');
	else
		return (0);
}

static long	ft_check_overflow_atoi(bool is_minus, long num, int base, char c)
{
	long	digit;

	if (!is_minus && num > LONG_MAX / base)
		return (LONG_MAX);
	if (is_minus && num > LONG_MAX / base)
		return (LONG_MIN);
	num = num * base;
	digit = get_digit_atoi(c);
	if (!is_minus && num > LONG_MAX - digit)
		return (LONG_MAX);
	if (is_minus && num - 1 > LONG_MAX - digit)
		return (LONG_MIN);
	num = num + digit;
	return (num);
}

long	ft_strtol(const char *str, int base_num)
{
	bool		is_minus;
	long		num;
	long		vetted_num;
	const char	*s;
	int			base;

	base = base_num;
	is_minus = false;
	s = ft_prefix_atoi(str, &is_minus);
	num = 0;
	while (*s <= '9' && '0' <= *s)
	{
		vetted_num = ft_check_overflow_atoi(is_minus, num, base, *s);
		if (vetted_num == LONG_MAX || vetted_num == LONG_MIN)
			return (vetted_num);
		else
			num = vetted_num;
		s++;
	}
	if (is_minus == true)
		return (num * -1);
	else
		return (num);
}

int	ft_atoi(const char *str)
{
	return ((int)ft_strtol(str, 10));
}

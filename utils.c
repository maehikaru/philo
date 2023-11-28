/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeharahikaru <maeharahikaru@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 03:37:50 by maeharahika       #+#    #+#             */
/*   Updated: 2023/11/27 04:15:37 by maeharahika      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_cur_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000); //tv_sec は秒、tv_usec はマイクロ秒を表しています。tv_usec は 1 マイクロ秒 = 0.000001 秒を表しています。
}

void	ft_xprintf(int idx, char *str, t_table *tbl)
{
	int	now_ms;

	pthread_mutex_lock(&tbl->stop_lock);
	now_ms = get_cur_ms() - tbl->start_ms;
	if (tbl->to_stop != DEATH)
		printf("%d %d %s\n", now_ms, idx, str);
	pthread_mutex_unlock(&tbl->stop_lock);
}

void	ft_xusleep(int ms)
{
	long long	now;

	now = get_cur_ms();
	while (get_cur_ms() - now < ms)
		usleep(ms / 10);
}

int	ft_xatoi(const char *str, bool *to_exit)
{
	int	tmp;

	tmp = ft_atoi(str);
	if (tmp <= 0)
		*to_exit = true;
	return (tmp);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeharahikaru <maeharahikaru@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 03:38:22 by maeharahika       #+#    #+#             */
/*   Updated: 2023/11/27 04:51:51 by maeharahika      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//この関数は、フィロソファーの死亡処理を行います。もし、プログラムが終了状態 (FINISHED) でない場合にフィロソファーが死亡した場合、死亡メッセージを出力し、プログラムの終了状態を DEATH に設定します。

void	death_handler(t_table *tbl, int i)
{
	pthread_mutex_lock(&tbl->stop_lock);
	if (tbl->to_stop != FINISHED)
	{
		pthread_mutex_unlock(&tbl->stop_lock);
		ft_xprintf(tbl->philos[i].idx, "died", tbl);
		pthread_mutex_lock(&tbl->stop_lock);
		tbl->to_stop = DEATH;
		pthread_mutex_unlock(&tbl->stop_lock);
	}
	pthread_mutex_unlock(&tbl->stop_lock);
}

//この関数は、指定された時間が経過するまで待機し、各フィロソファーの最後の食事からの経過時間を監視します。
//もし、あるフィロソファーの最後の食事からの経過時間が tbl->time_die 以上であれば、フィロソファーの死亡処理を行います。

void	thread_monitor(t_table *tbl)
{
	int	i;

	while (1)
	{
		i = 0;
		ft_xusleep(tbl->time_die + 1);
		while (i < tbl->n_philos)
		{
			pthread_mutex_lock(&tbl->waiter);
			if ((int)(get_cur_ms() - tbl->start_ms) \
					- tbl->philos[i].last_eat >= tbl->time_die)
			{
				pthread_mutex_unlock(&tbl->waiter);
				death_handler(tbl, i);
				return ;
			}
			pthread_mutex_unlock(&tbl->waiter);
			i++;
		}
	}
}

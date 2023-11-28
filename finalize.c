/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finalize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeharahikaru <maeharahikaru@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 03:38:29 by maeharahika       #+#    #+#             */
/*   Updated: 2023/11/27 04:55:18 by maeharahika      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mutex_destroy_and_free(t_table *tbl)
{
	int	i;

	pthread_mutex_destroy(&tbl->stop_lock);
	pthread_mutex_destroy(&tbl->waiter);
	i = 0;
	while (i < tbl->n_philos)
	{
		pthread_mutex_destroy(&tbl->forks[i]);
		i++;
	}
	free(tbl->forks);
	free(tbl->philos);
}

//この関数は、philos 配列に格納されているスレッドの終了を待機します。各スレッドの識別子は philos[i].tid で取得されます。pthread_join 関数を使用して、各スレッドの終了を待機します。

void	threads_join(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->tbl->n_philos)
	{
		pthread_join(philos[i].tid, NULL); //この関数を使用することで、メインスレッドが他のスレッドの終了を待機し、スレッド間の同期を行うことができます。
		i++;
	}
}

void	final_handler(t_table *tbl)
{
	threads_join(tbl->philos);
	mutex_destroy_and_free(tbl);
}
